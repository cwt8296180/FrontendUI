// Fill out your copyright notice in the Description page of Project Settings.


#include "FrontendGameplayTags.h"


namespace FrontendGameplayTags
{
//容器层
	//创建并注册游戏标签Frontend.WidgetStack.Modal，模态对话框层
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Frontend_WidgetStack_Modal,"Frontend.WidgetStack.Modal","模态对话框层标签");
	//创建并注册游戏标签Frontend.WidgetStack.GameMenu，游戏菜单层
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Frontend_WidgetStack_GameMenu, "Frontend.WidgetStack.GameMenu","游戏菜单层标签");
	//创建并注册游戏标签Frontend.WidgetStack.GameHud，游戏HUD层
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Frontend_WidgetStack_GameHud, "Frontend.WidgetStack.GameHud", "游戏HUD层标签");
	//创建并注册游戏标签Frontend.WidgetStack.Frontend，前端界面层
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Frontend_WidgetStack_Frontend, "Frontend.WidgetStack.Frontend", "前端界面层标签 - 用于消息通知和主界面的显示");
//显示界面层
	//创建并注册游戏标签Frontend.Widget.PressAnyKeyScreen，“任意按键”界面
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Frontend_Widget_PressAnyKeyScreen, "Frontend.Widget.PressAnyKeyScreen", "显示“任意按键”界面");
	//创建并注册游戏标签FFrontend.Widget.MainMenuScreen，主菜单界面
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Frontend_Widget_MainMenuScreen, "Frontend.Widget.MainMenuScreen", "显示主菜单界面");
	//创建并注册游戏标签FFrontend.Widget.ConfirmScreen，消息菜单界面
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Frontend_Widget_ConfirmScreen, "Frontend.Widget.ConfirmScreen", "消息菜单界面"); 
	//创建并注册游戏标签FFrontend.Widget.StoryScreen，故事菜单界面
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Frontend_Widget_StoryScreen, "Frontend.Widget.StoryScreen", "故事菜单界面");
	//创建并注册游戏标签FFrontend.Widget.OptionsScreen，选项菜单界面
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Frontend_Widget_OptionsScreen, "Frontend.Widget.OptionsScreen", "选项菜单界面");
	
}