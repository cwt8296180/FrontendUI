// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widget_ActivatableBase.generated.h"

class AFrontEndPlayerController;
/**
 * 创建UMG的基础类(不可实例化的UMG抽象基类)
 * Abstract:表示这个类是一个抽象基类，不能创建实例（对象）
 * BlueprintType:表示该类可以作为蓝图中的类型使用
 * meta = (DisableNativeTick)​:DisableNativeTick表示禁用这个类在C++端的Tick,不会影响蓝图中的事件Tick
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_ActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	/*
	* 获取玩家控制器
	*/
	AFrontEndPlayerController* GetOwningFrontEndPlayerController();
private:
	/*
	* 玩家控制器的弱引用
	*/
	TWeakObjectPtr<AFrontEndPlayerController> CachedOwningFrontendPC;
};
