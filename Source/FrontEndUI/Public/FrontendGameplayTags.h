// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"//Gameplay标签头文件

// Gameplay标签命名空间
namespace FrontendGameplayTags
{
//容器层级标签
	//对话框层
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Modal);
	//游戏菜单层
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameMenu);
	//游戏HUD层
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameHud);
	//前端界面层
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Frontend);
//界面标签
	//“任意按键”界面
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_PressAnyKeyScreen);
	//主菜单界面
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_MainMenuScreen);
	//消息菜单界面
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_ConfirmScreen);
	//故事菜单界面
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_StoryScreen);
	//选项菜单界面
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_OptionsScreen);
}