// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontendTypes/FrontendEnumTyes.h"
#include "FrontendUISubsystem.generated.h"

class UWidget_PrimaryLayout;
struct FGameplayTag;
class UWidget_ActivatableBase;
class UFrontendCommonButtonBase;
enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

/*
 * 创建动态委托（等同于蓝图中的事件分发器）
 * DECLARE：声明
 * DYNAMIC：动态委托（支持序列化、蓝图）
 * MULTICAST：多播委托（允许多个绑定）
 * DELEGATE：委托
 * TwoParams：带两个参数
 * 具体参数：
 * FOnButtonDescriptionTextUpdatedDelegate: 委托类型名（自定义）
 * UFrontendCommonButtonBase*: 第一个参数类型（指向UFrontendCommonButtonBase*对象的指针）
 * PushedWidget: 第一个参数名称
 * FText：第二个参数类型
 * DescriptionText：第二个参数名称
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate, UFrontendCommonButtonBase* ,BroadcastingButton, FText, DescriptionText);
/**
 * 界面子系统类
 */
UCLASS()
class FRONTENDUI_API UFrontendUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	/*
	* 静态方法：通过世界上下文对象获取前端 UI 子系统实例
	* @param WorldContextObject：传入的世界上下文对象（如 Widget, Actor 等）
	* @return 返回的前端UI子系统实例
	*/
	static UFrontendUISubsystem* Get(const UObject* WorldContextObject);
	/*
	* 是否创建该子系统（重写自USubsystem）
	* @param Outer：
	* @return 返回true，表示应该创建这个子系统的实例。返回false，表示不创建这个基础类
	*/
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	/*
	* 注册已创建的主布局控件到前端UI子系统
	* @param InCreatedWidget：已创建的主布局控件
	*/
	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget);
	/*
	* 异步加载软引用的控件并推送到指定UI容器里
	* @param InWidgetStackTag：标识目标容器
	* @param InSoftWidgetClass：要加载的Widget类（软引用）
	* @param AysncPushStateCallBack：异步状态回调
	*/
	void PushSoftWidgetToStackAynsc(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
	TFunction<void(EAsyncPushWidgetState,UWidget_ActivatableBase*)> AysncPushStateCallBack);
	/*
	* 异步将消息界面推送到模态容器中
	* @param InScreenType：消息界面的类型
	* @param InScreenTitle：消息界面的标题内容
	* @param InScreenMsg：消息界面的消息内容
	* @param ButtonClickedCallback：按钮点击后的回调函数
	*/
	void PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType,const FText& InScreenTitle, const FText& InScreenMsg,
		TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback);

	/*
	* 声明动态委托
	*/
	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;
private:
	/*
	* 储存控件容器
	*/
	UPROPERTY(Transient)
	UWidget_PrimaryLayout* CreatedPrimaryLayout;
};
