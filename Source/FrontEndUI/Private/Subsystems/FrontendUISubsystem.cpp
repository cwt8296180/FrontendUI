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
    // 检查全局引擎对象是否有效（所有平台通用）
    if (GEngine)
    {
        // 从上下文对象获取关联的世界对象：
        // 参数1：传入的世界上下文对象（如 Widget, Actor 等）
        // 参数2：错误处理模式 - Assert 表示无效时会触发断言
       UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
       // 通过游戏实例获取子系统：
       // 1. World->GetGameInstance() 获取当前世界的游戏实例
       // 2. UGameInstance::GetSubsystem<T> 模板方法查询子系统
       return  UGameInstance::GetSubsystem<UFrontendUISubsystem>(World->GetGameInstance());
    }
    // 如果 GEngine 不可用（如编辑器启动前），返回空指针
    return nullptr;
}

bool UFrontendUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    // 检查外部对象（游戏实例）是否是专用服务器实例 CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance()
    // 只检查能否转换游戏实例
    if (CastChecked<UGameInstance>(Outer))
    {
        // 如果不是专用服务器，本函数直接返回false，不创建子系统。
        // 但这里是专用服务器，则继续下面的逻辑：
        // 准备一个数组用于存放派生类
        TArray<UClass*>FoundClasses;
        // 获取当前类（UFrontendUISubsystem）的所有派生类
        GetDerivedClasses(GetClass(), FoundClasses);
        // 判断是否有派生类存在：
        // 如果没有派生类（FoundClasses为空），返回true，表示应该创建这个子系统的实例。
        // 如果有派生类，则返回false，表示不创建这个基础类（而是让派生类去创建）。
        return FoundClasses.IsEmpty();
    }

  return false;
  
}

void UFrontendUISubsystem::RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget)
{
    // 1. 安全检查：确保传入的控件指针是有效的（非空）
    //    如果 InCreatedWidget 为空指针，在开发版本中会触发断言中断程序执行
    check(InCreatedWidget);
    // 2. 存储引用：将传入的主布局控件赋值给子系统的成员变量 CreatedPrimaryLayout
    //    该操作会覆盖之前存储的任何主布局控件（如果有）
    CreatedPrimaryLayout = InCreatedWidget;
}

void UFrontendUISubsystem::PushSoftWidgetToStackAynsc(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AysncPushStateCallback)
{
    // 确保软引用有效
    check(!InSoftWidgetClass.IsNull());
    // 请求异步加载资源
    UAssetManager::Get().GetStreamableManager().RequestAsyncLoad
    (
        // 将软引用转换为资源路径
        InSoftWidgetClass.ToSoftObjectPath(),
        // 创建加载完成后的回调
        FStreamableDelegate::CreateLambda 
        (
        [InSoftWidgetClass, this, InWidgetStackTag, AysncPushStateCallback]()
        {
             // 获取已加载的Widget类
             UClass* LoadedWidgetClass =  InSoftWidgetClass.Get();
             // 验证加载结果和主布局存在
             check(LoadedWidgetClass && CreatedPrimaryLayout);
             // 通过标签查找目标UI栈容器
            UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);
            // 在容器中创建并添加Widget实例
            UWidget_ActivatableBase* CreatedWidget = FoundWidgetStack->AddWidget<UWidget_ActivatableBase>
            (
            // 已加载的Widget类
            LoadedWidgetClass,
                // 创建完成但尚未添加到栈时的回调
                [AysncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance)
                {
                    // 通知回调：Widget已创建但尚未入栈
                    AysncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush,&CreatedWidgetInstance);
                }
            );
            // 通知回调：Widget已完全添加到栈中
            AysncPushStateCallback(EAsyncPushWidgetState::AfterPush,CreatedWidget);
        }
        )
    );
}

void UFrontendUISubsystem::PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
    // 创建配置对象的指针，初始为nullptr
    UConfirmScreenInfoObject* CreatedInfoObject =nullptr;
    // 根据传入的消息界面类型创建不同的配置对象
    switch (InScreenType)
    {
    case EConfirmScreenType::OK:
        // 创建OK类型（单按钮）消息界面配置
        CreatedInfoObject = UConfirmScreenInfoObject::CreateOKScreen(InScreenTitle,InScreenMsg);
        break;
    case EConfirmScreenType::YesNo:
        // 创建Yes/No类型（双按钮）消息界面配置
        CreatedInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle,InScreenMsg);
        break;
    case EConfirmScreenType::YesNoCancel:
        // 创建OK/Cancel类型（双按钮）消息界面配置
        CreatedInfoObject = UConfirmScreenInfoObject::CreateOKCancelScreen(InScreenTitle,InScreenMsg);
        break;
    case EConfirmScreenType::Unknown:
        break;
    default:
        break;
    }
    // 安全检查：确认配置对象成功创建
    check(CreatedInfoObject);
    // 异步推送软引用控件到UI堆栈
    PushSoftWidgetToStackAynsc
    (
        // 目标堆栈标签（模态堆栈）
        FrontendGameplayTags::Frontend_WidgetStack_Modal,
        // 通过标签获取确认消息界面的控件类（软引用）
        UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(FrontendGameplayTags::Frontend_Widget_ConfirmScreen),
        // 推送状态的回调函数
        [CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
        {
            // 当控件已创建但还未推入堆栈前的状态处理
            if (InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
            {
                // 将控件转换为我们期望的消息界面类型
                UWidget_ConfirmScreen* CreatedConfirmScreen = CastChecked<UWidget_ConfirmScreen>(PushedWidget);
                // 初始化消息界面控件
                CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject,ButtonClickedCallback);
            }
        }
    );
}
