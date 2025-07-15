// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"
#include "AsyncAction_PushSoftWidget.generated.h"

class UWidget_ActivatableBase;
/*
 * DECLARE：声明
 * DYNAMIC：动态委托（支持序列化、蓝图）
 * MULTICAST：多播委托（允许多个绑定）
 * DELEGATE：委托
 * OneParam：带一个参数
 * 具体参数：
 * FOnPushSoftWidgetDelegate: 委托类型名（自定义）
 * UWidget_ActivatableBase*: 参数类型（指向UWidget_ActivatableBase对象的指针）
 * PushedWidget: 参数名称
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UWidget_ActivatableBase*,PushedWidget);
/*
 * 异步操作类
 * 用于异步加载和推入软引用Widget
 */
UCLASS()
class FRONTENDUI_API UAsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/*
	* 静态工厂方法：创建并初始化异步推入Widget操作节点
	* @param WorldContextobject：世界上下文对象，用于获取世界和子系统
	* @param OwningPlayerController：拥有此操作的玩家控制器
	* @param InSoftWidgetClass：要加载的软引用Widget类
	* @param InWidgetStackTag：目标UI栈的游戏标签标识
	* @param bFocusOnNewlyPushedWidget：是否自动聚焦新添加的Widget(键盘控制UI或者手柄控制UI)
	* @return 返回创建好的异步操作节点
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Hidepin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Push Soft Widget To Stack"))
	static UAsyncAction_PushSoftWidget* PushSoftWidget(const UObject*WorldContextobject,
	APlayerController* OWningPlayerController,TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
	UPARAM(meta = (Categories = "Frontend.WidgetStack"))FGameplayTag InWidgetStackTag,bool bFoncusOnNewlyPushedWidget = true);

	/*
	* 从父类继承 激活异步操作，用于异步工作和显示界面
	*/
	virtual void Activate() override;

	/*
	* 在推送操作之前已创建的组件
	*/
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreatedBeforePush;
	/*
	* 在推送之后
	*/
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate AfterPush;

private:
	/*
	* 缓存所属关卡内容
	*/
	TWeakObjectPtr<UWorld> CachedOwningWorld;
	/*
	* 缓存所属关卡玩家控制器
	*/
	TWeakObjectPtr<APlayerController> CachedOwningPC;
	/*
	* 缓存需要显示到屏幕的软引用界面组件
	*/
	TSoftClassPtr<UWidget_ActivatableBase>CachedSoftWidgetClass;
	/*
	* 缓存需要显示到屏幕的Gameplay标签
	*/
	FGameplayTag CachedWidgetStackTag;
    /*
	* 缓存是否需要聚焦新添加的界面组件
	*/
	bool bCachedFoncusOnNewlyPushedWidget = false;
};
