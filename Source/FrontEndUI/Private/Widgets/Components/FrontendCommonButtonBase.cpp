// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Subsystems/FrontendUISubsystem.h"


#include "FrontendDebugHelper.h"

void UFrontendCommonButtonBase::SetButtonText(const FText& InText)
{
	// 检查条件：1) 文本控件指针有效 2) 传入文本非空
	if (CommonTextBlock_ButtonText&& !InText.IsEmpty())
	{
		// 根据bUserUpperCaseForButtonText标志决定文本格式：
		// true: 转为全大写 (用于统一菜单风格)
		// false: 保持原格式        
		CommonTextBlock_ButtonText->SetText(bUserUpperCaseForButtonText?InText.ToUpper(): InText);
	}
}

void UFrontendCommonButtonBase::NativePreConstruct()
{
	// 调用父类实现保证基础功能正确执行
	Super::NativePreConstruct();
	// 使用按钮的默认显示文本(ButtonDisplayText属性)初始化文本控件
	// 注：ButtonDisplayText通常在蓝图或实例中设置
	SetButtonText(ButtonDisplayText);
	// 注：此函数在以下时机自动调用：
	// 1. 控件首次创建时
	// 2. 设计器属性修改后
}

void UFrontendCommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	// 首先调用父类实现，确保基础功能执行
	Super::NativeOnCurrentTextStyleChanged();
	// 检查文本控件引用是否有效
	if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
	{
		// 将新样式应用到文本控件(获取当前文本样式)
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
	// 注：此函数在以下时机自动调用：
	// 1. 按钮悬停时
	// 2. 取消悬停时
	// 3. 按钮按下时
	// 4. 按钮抬起时
}

void UFrontendCommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();
	// 检查按钮的描述文本是否非空
	if (!ButtonDescriptionText.IsEmpty())
	{
		// 获取前端UI子系统，并广播描述文本更新事件：
		// Get(this) - 通过当前对象上下文获取子系统实例
		// Broadcast(this, ButtonDescriptionText) - 发送事件：
		// this: 当前按钮实例（作为事件源）
		// ButtonDescriptionText: 当前设置的描述文本
		UFrontendUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, ButtonDescriptionText);
	}
	//在按钮悬停时自动调用
}

void UFrontendCommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();
	// 获取前端UI子系统，并广播描述文本更新事件：
	// Get(this) - 通过当前对象上下文获取子系统实例
	// Broadcast(this, ButtonDescriptionText) - 发送事件：
	// this: 当前按钮实例（作为事件源）
	// FText::GetEmpty(): 设置描述文本为空
	UFrontendUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, FText::GetEmpty());
	//在按钮取消悬停时自动调用
}

void UFrontendCommonButtonBase::NativeOnPressed()
{
	Super::NativeOnPressed();
	//在按钮按下时自动调用
}

void UFrontendCommonButtonBase::NativeOnReleased()
{
	Super::NativeOnReleased();
	//按钮释放时自动调用
}

