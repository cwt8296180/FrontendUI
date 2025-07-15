// Fill out your copyright notice in the Description page of Project Settings.

#include "Subsystems/FrontendUISubsystem.h"
#include "Engine/AssetManager.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widgets/Widget_ConfirmScreen.h"
#include "FrontendGameplayTags.h"
#include "FrontendFunctionLibrary.h"
#include "FrontendDebugHelper.h"



UFrontendUISubsystem* UFrontendUISubsystem::Get(const UObject* WorldContextObject)
{
    // ���ȫ����������Ƿ���Ч������ƽ̨ͨ�ã�
    if (GEngine)
    {
        // �������Ķ����ȡ�������������
        // ����1����������������Ķ����� Widget, Actor �ȣ�
        // ����2��������ģʽ - Assert ��ʾ��Чʱ�ᴥ������
       UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
       // ͨ����Ϸʵ����ȡ��ϵͳ��
       // 1. World->GetGameInstance() ��ȡ��ǰ�������Ϸʵ��
       // 2. UGameInstance::GetSubsystem<T> ģ�巽����ѯ��ϵͳ
       return  UGameInstance::GetSubsystem<UFrontendUISubsystem>(World->GetGameInstance());
    }
    // ��� GEngine �����ã���༭������ǰ�������ؿ�ָ��
    return nullptr;
}

bool UFrontendUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    // ����ⲿ������Ϸʵ�����Ƿ���ר�÷�����ʵ�� CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance()
    // ֻ����ܷ�ת����Ϸʵ��
    if (CastChecked<UGameInstance>(Outer))
    {
        // �������ר�÷�������������ֱ�ӷ���false����������ϵͳ��
        // ��������ר�÷������������������߼���
        // ׼��һ���������ڴ��������
        TArray<UClass*>FoundClasses;
        // ��ȡ��ǰ�ࣨUFrontendUISubsystem��������������
        GetDerivedClasses(GetClass(), FoundClasses);
        // �ж��Ƿ�����������ڣ�
        // ���û�������ࣨFoundClassesΪ�գ�������true����ʾӦ�ô��������ϵͳ��ʵ����
        // ����������࣬�򷵻�false����ʾ��������������ࣨ������������ȥ��������
        return FoundClasses.IsEmpty();
    }

  return false;
  
}

void UFrontendUISubsystem::RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget)
{
    // 1. ��ȫ��飺ȷ������Ŀؼ�ָ������Ч�ģ��ǿգ�
    //    ��� InCreatedWidget Ϊ��ָ�룬�ڿ����汾�лᴥ�������жϳ���ִ��
    check(InCreatedWidget);
    // 2. �洢���ã�������������ֿؼ���ֵ����ϵͳ�ĳ�Ա���� CreatedPrimaryLayout
    //    �ò����Ḳ��֮ǰ�洢���κ������ֿؼ�������У�
    CreatedPrimaryLayout = InCreatedWidget;
}

void UFrontendUISubsystem::PushSoftWidgetToStackAynsc(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AysncPushStateCallback)
{
    // ȷ����������Ч
    check(!InSoftWidgetClass.IsNull());
    // �����첽������Դ
    UAssetManager::Get().GetStreamableManager().RequestAsyncLoad
    (
        // ��������ת��Ϊ��Դ·��
        InSoftWidgetClass.ToSoftObjectPath(),
        // ����������ɺ�Ļص�
        FStreamableDelegate::CreateLambda 
        (
        [InSoftWidgetClass, this, InWidgetStackTag, AysncPushStateCallback]()
        {
             // ��ȡ�Ѽ��ص�Widget��
             UClass* LoadedWidgetClass =  InSoftWidgetClass.Get();
             // ��֤���ؽ���������ִ���
             check(LoadedWidgetClass && CreatedPrimaryLayout);
             // ͨ����ǩ����Ŀ��UIջ����
            UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);
            // �������д��������Widgetʵ��
            UWidget_ActivatableBase* CreatedWidget = FoundWidgetStack->AddWidget<UWidget_ActivatableBase>
            (
            // �Ѽ��ص�Widget��
            LoadedWidgetClass,
                // ������ɵ���δ��ӵ�ջʱ�Ļص�
                [AysncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance)
                {
                    // ֪ͨ�ص���Widget�Ѵ�������δ��ջ
                    AysncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush,&CreatedWidgetInstance);
                }
            );
            // ֪ͨ�ص���Widget����ȫ��ӵ�ջ��
            AysncPushStateCallback(EAsyncPushWidgetState::AfterPush,CreatedWidget);
        }
        )
    );
}

void UFrontendUISubsystem::PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
    // �������ö����ָ�룬��ʼΪnullptr
    UConfirmScreenInfoObject* CreatedInfoObject =nullptr;
    // ���ݴ������Ϣ�������ʹ�����ͬ�����ö���
    switch (InScreenType)
    {
    case EConfirmScreenType::OK:
        // ����OK���ͣ�����ť����Ϣ��������
        CreatedInfoObject = UConfirmScreenInfoObject::CreateOKScreen(InScreenTitle,InScreenMsg);
        break;
    case EConfirmScreenType::YesNo:
        // ����Yes/No���ͣ�˫��ť����Ϣ��������
        CreatedInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle,InScreenMsg);
        break;
    case EConfirmScreenType::YesNoCancel:
        // ����OK/Cancel���ͣ�˫��ť����Ϣ��������
        CreatedInfoObject = UConfirmScreenInfoObject::CreateOKCancelScreen(InScreenTitle,InScreenMsg);
        break;
    case EConfirmScreenType::Unknown:
        break;
    default:
        break;
    }
    // ��ȫ��飺ȷ�����ö���ɹ�����
    check(CreatedInfoObject);
    // �첽���������ÿؼ���UI��ջ
    PushSoftWidgetToStackAynsc
    (
        // Ŀ���ջ��ǩ��ģ̬��ջ��
        FrontendGameplayTags::Frontend_WidgetStack_Modal,
        // ͨ����ǩ��ȡȷ����Ϣ����Ŀؼ��ࣨ�����ã�
        UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(FrontendGameplayTags::Frontend_Widget_ConfirmScreen),
        // ����״̬�Ļص�����
        [CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
        {
            // ���ؼ��Ѵ�������δ�����ջǰ��״̬����
            if (InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
            {
                // ���ؼ�ת��Ϊ������������Ϣ��������
                UWidget_ConfirmScreen* CreatedConfirmScreen = CastChecked<UWidget_ConfirmScreen>(PushedWidget);
                // ��ʼ����Ϣ����ؼ�
                CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject,ButtonClickedCallback);
            }
        }
    );
}
