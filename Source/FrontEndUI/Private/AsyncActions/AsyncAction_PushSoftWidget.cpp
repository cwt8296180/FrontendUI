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
	//软引用有效性验证：确保传入的软引用不为空
	//如果检查失败，在开发版本中会触发断言并输出错误信息
	checkf(!InSoftWidgetClass.IsNull(),TEXT("PushSoftWidgetToStack was passed a null soft widget class"));
	//检查全局引擎对象是否存在（基础运行环境验证）
	if (GEngine)
	{
		//通过上下文对象获取有效的世界实例
		//    EGetWorldErrorMode::LogAndReturnNull: 失败时记录错误日志并返回空指针
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextobject,EGetWorldErrorMode::LogAndReturnNull))
		{
			//创建异步操作节点对象（UObject的实例）
			UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();
			//缓存世界指针（弱引用防止生命周期问题）
			Node->CachedOwningWorld = World;
			//缓存玩家控制器
			Node->CachedOwningPC = OWningPlayerController;
			//缓存软引用控件类
			Node->CachedSoftWidgetClass = InSoftWidgetClass;
			//缓存UI栈标签
			Node->CachedWidgetStackTag = InWidgetStackTag;
			//缓存自动聚焦设置
			Node->bCachedFoncusOnNewlyPushedWidget = bFoncusOnNewlyPushedWidget;
			//将节点注册到游戏实例系统，确保生命周期正确管理（游戏实例销毁时自动销毁节点）
			Node->RegisterWithGameInstance(World);
			//返回创建并配置好的异步操作节点
			return Node;
		}
	}
	//如果任何条件不满足（GEngine无效或无法获取有效世界），返回空指针
	return nullptr;
}

void UAsyncAction_PushSoftWidget::Activate()
{
	//通过缓存的关卡对象指针，获取前端UI子系统实例
	UFrontendUISubsystem* UFrontendUISubsystem = UFrontendUISubsystem::Get(CachedOwningWorld.Get());
	//调用创建的UI子系统的异步加载软引用的Widget并推送到GameplayTags指定的容器层级里
	UFrontendUISubsystem->PushSoftWidgetToStackAynsc
	(
		// 缓存GameplayTags指定的容器层级
		CachedWidgetStackTag,
		// 缓存的软引用Widget类
		CachedSoftWidgetClass,
		//定义异步状态回调Lambda函数
		[this](EAsyncPushWidgetState InPushState,UWidget_ActivatableBase* PushedWidget)
	  {
	//根据不同的推入状态进行处理
		switch (InPushState)
		{
			// 状态1: 控件已创建但尚未推入指定的容器层级
			case EAsyncPushWidgetState::OnCreatedBeforePush:
				//从缓存的关卡玩家控制器设置控件的拥有者
				PushedWidget->SetOwningPlayer(CachedOwningPC.Get());
				//广播"控件创建前"事件（此时控件已创建但未激活）
				OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
			break;
				// 状态2: 控件已完全推入指定的容器层级
				case EAsyncPushWidgetState::AfterPush:
					//广播"控件推入后"事件（此时控件已完全激活）
					AfterPush.Broadcast(PushedWidget);
					//检查是否需要自动聚焦新控件
					if (bCachedFoncusOnNewlyPushedWidget)
					{
						//尝试获取控件的首选聚焦目标（如按钮、输入框等）
						if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
						{
							//设置焦点到目标控件（激活UI导航）
							WidgetToFocus->SetFocus();
						}
					}
					// 标记异步操作节点为可销毁状态（重要清理步骤）
					SetReadyToDestroy();
			break;
		default:
			break;
		}
	  }
	);
}
