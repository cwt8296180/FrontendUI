// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_PushConfirmScreen.h"
#include "Subsystems/FrontendUISubsystem.h"

UAsyncAction_PushConfirmScreen* UAsyncAction_PushConfirmScreen::PushConfirmScreen(const UObject* WorldContextObject, 
	EConfirmScreenType ScreenType, FText InScreenTitle, FText InScreenMessage)
{
	// 检查全局引擎实例是否存在（确保引擎已初始化）
	if (GEngine)
	{
		if (UWorld * World =GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			// 通过上下文对象安全获取UWorld指针：
			// - EGetWorldErrorMode::LogAndReturnNull 表示获取失败时记录错误并返回nullptr
			UAsyncAction_PushConfirmScreen* Node =  NewObject<UAsyncAction_PushConfirmScreen>();
			// 缓存当前游戏世界指针
			Node->CachedOwingWorld    = World;
			// 缓存传入的消息界面类型
			Node->CachedSceenType     = ScreenType;
			// 缓存消息界面标题文本（使用FText支持本地化）
			Node->CachedScreenTitle   = InScreenTitle;
			// 缓存消息界面消息文本（使用FText支持本地化）
			Node->CachedScreenMessage = InScreenMessage;
			// 将异步操作注册到游戏实例：
			// - 防止世界切换时被错误回收
			// - 管理异步操作的生命周期
			Node->RegisterWithGameInstance(World);
			// 返回配置好的异步操作对象
			return Node;
		}
	}
	
	return nullptr;
}

void UAsyncAction_PushConfirmScreen::Activate()
{
	// 获取前端UI子系统（FrontendUISubsystem）的实例，使用缓存的World指针
	// CachedOwingWorld是一个TWeakObjectPtr<UWorld>，我们使用Get()方法获取其UWorld指针
	// 调用子系统的函数将消息界面推送到GameplayTags里的对话框层
	UFrontendUISubsystem::Get(CachedOwingWorld.Get())->PushConfirmScreenToModalStackAsync
		// 传递缓存的消息界面类型
		(CachedSceenType, 
		// 传递缓存的消息界面标题文本
		CachedScreenTitle,
		// 传递缓存的消息界面消息文本
		CachedScreenMessage, 
		// 定义一个lambda函数作为回调，当用户点击按钮时被调用
		[this](EConfirmScreenButtonType ClickedButtonType)
		{
			// 当用户点击按钮后，广播按钮点击事件
			// 将点击的按钮类型（ClickedButtonType）广播给所有绑定到这个委托的对象
			OnButtonClicked.Broadcast(ClickedButtonType);
			// 标记此异步对象为“准备销毁”，以便垃圾回收系统可以回收它
			SetReadyToDestroy();
		}
	);
}
