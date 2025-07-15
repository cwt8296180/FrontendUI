// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Widget_PrimaryLayout.generated.h"

class UCommonActivatableWidgetContainerBase;
/**
 * 创建UMG的容器只创建一次，内容在创建UMG的基础类里写（不可实例化的UMG抽象基类）
 * Abstract:表示这个类是一个抽象基类，不能创建实例（对象）
 * BlueprintType:表示该类可以作为蓝图中的类型使用
 * meta = (DisableNativeTick)​:DisableNativeTick表示禁用这个类在C++端的Tick,不会影响蓝图中的事件Tick
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_PrimaryLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	/*
	* 查找与给定标签相关联的控件栈（widget stack）
	* @param InTag：一个FGameplayTag类型的常量引用，作为查找的键
	* @return 指向UCommonActivatableWidgetContainerBase的指针
	*/
	UCommonActivatableWidgetContainerBase*FindWidgetStackByTag(const FGameplayTag& InTag) const;

protected:
	/*
	* 注册一个新的界面容器
	* @param InStackTag:表示UI栈层级的游戏标签 使用UPARAM(meta = (Categories = "Frontend.WidgetStack"))来过滤游戏标签选项
	* @param InStack:要注册的UI容器引用
	*/
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetStack(UPARAM(meta = (Categories = "Frontend.WidgetStack"))FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack);
private:
	/*
	* 临时性UI管理系统
	* FGameplayTag类型，代表一个游戏标签
	* UCommonActivatableWidgetContainerBase类型，代表一个可以包含多个可激活UI控件的容器
	*/
	UPROPERTY(Transient)
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> RegisteredWidgetStackMap;
};
