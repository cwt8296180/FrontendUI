// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/OptionsScreens/Widget_OptionsScreen.h"
#include "Input/CommonUIInputTypes.h"
#include "ICommonInputModule.h"
#include "FrontendDebugHelper.h"

void UWidget_OptionsScreen::NativeOnInitialized()
{
	// 调用父类(UUserWidget)的初始化逻辑
	Super::NativeOnInitialized();
	// 检查是否设置了有效的重置操作（在蓝图中配置）
	if (!ResetAction.IsNull())
	{
		// 注册UI输入动作绑定（核心功能：将用户输入连接到函数）
		ResetActionHandle = RegisterUIActionBinding
		(
			// 构造绑定参数结构
			FBindUIActionArgs
			(
				// 输入动作标识
				ResetAction,
				// 是否为持久绑定（全局响应）
				true,
				// 创建委托绑定到成员函数
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered)
			)
		);
		// ResetActionHandle 是注册句柄，用于后续取消注册
	}
	// 注册默认返回操作
	RegisterUIActionBinding
	(
		FBindUIActionArgs
		(
			// 从CommonInput设置中获取预定义的返回动作（如Esc键/B按钮）
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			// 同样设置为持久绑定
			true,
			// 绑定到返回功能函数
			FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTriggered)
		)
	);
}

void UWidget_OptionsScreen::OnResetBoundActionTriggered()
{
	Debug::Print(TEXT("Reset bound action triggered"));
}

void UWidget_OptionsScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}
