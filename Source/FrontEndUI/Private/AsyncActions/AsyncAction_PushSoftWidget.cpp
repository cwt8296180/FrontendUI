// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_PushSoftWidget.h"
#include "Subsystems/FrontendUISubsystem.h"
#include "Widgets/Widget_ActivatableBase.h"

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextobject, 
APlayerController* OWningPlayerController, 
TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
UPARAM(meta = (Categories = "Frontend.WidgetStack"))FGameplayTag InWidgetStackTag,
bool bFoncusOnNewlyPushedWidget)
{
	//��������Ч����֤��ȷ������������ò�Ϊ��
	//������ʧ�ܣ��ڿ����汾�лᴥ�����Բ����������Ϣ
	checkf(!InSoftWidgetClass.IsNull(),TEXT("PushSoftWidgetToStack was passed a null soft widget class"));
	//���ȫ����������Ƿ���ڣ��������л�����֤��
	if (GEngine)
	{
		//ͨ�������Ķ����ȡ��Ч������ʵ��
		//    EGetWorldErrorMode::LogAndReturnNull: ʧ��ʱ��¼������־�����ؿ�ָ��
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextobject,EGetWorldErrorMode::LogAndReturnNull))
		{
			//�����첽�����ڵ����UObject��ʵ����
			UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();
			//��������ָ�루�����÷�ֹ�����������⣩
			Node->CachedOwningWorld = World;
			//������ҿ�����
			Node->CachedOwningPC = OWningPlayerController;
			//���������ÿؼ���
			Node->CachedSoftWidgetClass = InSoftWidgetClass;
			//����UIջ��ǩ
			Node->CachedWidgetStackTag = InWidgetStackTag;
			//�����Զ��۽�����
			Node->bCachedFoncusOnNewlyPushedWidget = bFoncusOnNewlyPushedWidget;
			//���ڵ�ע�ᵽ��Ϸʵ��ϵͳ��ȷ������������ȷ������Ϸʵ������ʱ�Զ����ٽڵ㣩
			Node->RegisterWithGameInstance(World);
			//���ش��������úõ��첽�����ڵ�
			return Node;
		}
	}
	//����κ����������㣨GEngine��Ч���޷���ȡ��Ч���磩�����ؿ�ָ��
	return nullptr;
}

void UAsyncAction_PushSoftWidget::Activate()
{
	//ͨ������Ĺؿ�����ָ�룬��ȡǰ��UI��ϵͳʵ��
	UFrontendUISubsystem* UFrontendUISubsystem = UFrontendUISubsystem::Get(CachedOwningWorld.Get());
	//���ô�����UI��ϵͳ���첽���������õ�Widget�����͵�GameplayTagsָ���������㼶��
	UFrontendUISubsystem->PushSoftWidgetToStackAynsc
	(
		// ����GameplayTagsָ���������㼶
		CachedWidgetStackTag,
		// �����������Widget��
		CachedSoftWidgetClass,
		//�����첽״̬�ص�Lambda����
		[this](EAsyncPushWidgetState InPushState,UWidget_ActivatableBase* PushedWidget)
	  {
	//���ݲ�ͬ������״̬���д���
		switch (InPushState)
		{
			// ״̬1: �ؼ��Ѵ�������δ����ָ���������㼶
			case EAsyncPushWidgetState::OnCreatedBeforePush:
				//�ӻ���Ĺؿ���ҿ��������ÿؼ���ӵ����
				PushedWidget->SetOwningPlayer(CachedOwningPC.Get());
				//�㲥"�ؼ�����ǰ"�¼�����ʱ�ؼ��Ѵ�����δ���
				OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
			break;
				// ״̬2: �ؼ�����ȫ����ָ���������㼶
				case EAsyncPushWidgetState::AfterPush:
					//�㲥"�ؼ������"�¼�����ʱ�ؼ�����ȫ���
					AfterPush.Broadcast(PushedWidget);
					//����Ƿ���Ҫ�Զ��۽��¿ؼ�
					if (bCachedFoncusOnNewlyPushedWidget)
					{
						//���Ի�ȡ�ؼ�����ѡ�۽�Ŀ�꣨�簴ť�������ȣ�
						if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
						{
							//���ý��㵽Ŀ��ؼ�������UI������
							WidgetToFocus->SetFocus();
						}
					}
					// ����첽�����ڵ�Ϊ������״̬����Ҫ�����裩
					SetReadyToDestroy();
			break;
		default:
			break;
		}
	  }
	);
}
