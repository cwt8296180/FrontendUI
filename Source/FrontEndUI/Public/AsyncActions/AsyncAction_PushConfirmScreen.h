// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FrontendTypes/FrontendEnumTyes.h"
#include "AsyncAction_PushConfirmScreen.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmScreenButtonClickedDelegate,EConfirmScreenButtonType, ClickedButtonType);
/**
 * 
 */
UCLASS()
class FRONTENDUI_API UAsyncAction_PushConfirmScreen : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/*
	 * 创建消息界面异步操作
	 * @param WorldContextObject 提供世界上下文的UObject
	 * @param ScreenType 消息界面的枚举类型（如警告/确认等）
	 * @param InScreenTitle 本地化支持的消息界面标题文本
	 * @param InScreenMessage 本地化支持的消息界面消息文本
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Hidepin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Show Confirmation Screen"))
	static UAsyncAction_PushConfirmScreen* PushConfirmScreen(const UObject* WorldContextObject,EConfirmScreenType ScreenType,
		FText InScreenTitle,FText InScreenMessage);

	/*
	* 从父类继承 激活异步操作，用于异步工作和显示消息界面
	*/
	virtual void Activate() override;
	/*
	* 点击消息界面的按钮后，会触发此委托
	*/
	UPROPERTY(BlueprintAssignable)
	FOnConfirmScreenButtonClickedDelegate OnButtonClicked;
private:
	/*
	* 缓存当前游戏世界指针
	*/
	TWeakObjectPtr<UWorld> CachedOwingWorld;
	/*
	* 缓存消息界面类型
	*/
	EConfirmScreenType CachedSceenType;
	/*
	* 缓存消息界面标题文本
	*/
	FText CachedScreenTitle;
	/*
	* 缓存消息界面消息文本
	*/
	FText CachedScreenMessage;
};
