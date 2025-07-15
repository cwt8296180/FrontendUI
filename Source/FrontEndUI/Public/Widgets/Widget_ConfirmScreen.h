// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "FrontendTypes/FrontendEnumTyes.h"
#include "Widget_ConfirmScreen.generated.h"


class UCommonTextBlock;
class UDynamicEntryBox;
/*
 * 消息显示界面按钮信息结构体
 */
USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
	GENERATED_BODY()
	/*
	 * 消息显示界面显示类型枚举
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConfirmScreenButtonType ConfirmScreenButtonType = EConfirmScreenButtonType::Unknown;
	/*
	* 要显示的按钮文本
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ButtonTextToDisplay;
};
/*
 * 消息显示界面类
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UConfirmScreenInfoObject : public UObject
{
	GENERATED_BODY()

public:
	/*
	 * 创建OK屏幕信息对象
	 * @param InScreenTitle 显示界面标题
	 * @param InScreenMsg 显示界面消息
	 */
	static UConfirmScreenInfoObject* CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMsg);
	/*
	 * 创建YesNo屏幕信息对象
	 * @param InScreenTitle 显示界面标题
	 * @param InScreenMsg 显示界面消息
	 */
	static UConfirmScreenInfoObject* CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMsg);
    /*
	 * 创建OKCancel屏幕信息对象
	 * @param InScreenTitle 显示界面标题
	 * @param InScreenMsg 显示界面消息
	 */
	static UConfirmScreenInfoObject* CreateOKCancelScreen(const FText& InScreenTitle, const FText& InScreenMsg);

	/*
	 * 临时储存消息显示界面标题
	 */
	UPROPERTY(Transient)
	FText ScreenTitle;
	/*
	 * 临时储存消息显示界面消息
	 */
	UPROPERTY(Transient)
	FText ScreenMessage;
	/*
	 * 临时储存消息显示界面按钮信息结构体数组
	 */
	UPROPERTY(Transient)
	TArray<FConfirmScreenButtonInfo> AvailableScreenButtons;
};
/*
 * 消息显示界面
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_ConfirmScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

public:
	/*
	 * 创建将外部类调用函数，当界面被构造且还没有显示时调用
	 * 初始化消息界面
	 * @param InScreenInfoObject 包含界面标题、消息和按钮配置的信息对象
	 * @param ClickedButtonCallback 按钮点击后的回调函数，参数是按钮类型
	 */
	void InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject,
		TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback);
private:
	/*
	 * 标题文本组件
	 */
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Title;
	/*
	 * 消息文本组件
	 */
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Message;
    /*
     * 动态条目框（按钮）容器组件
     */
	UPROPERTY(meta = (BindWidget))
	UDynamicEntryBox* DynamicEntryBox_Buttons;
};
