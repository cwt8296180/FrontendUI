// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "FrontendCommonButtonBase.generated.h"

class	UCommonTextBlock;
/**
 * Common按键基类
 * 和传统按键相比，有以下改进点：
 * 集中化的样式资源（按钮样式）（按钮文本样式）
 * 可以同过自定义输入触发（通过数据表配置输入数据）
 * 支持自定义输入模式（键盘，手柄等）（绑定后更新平台特定的图标）
 * Abstract:表示这个类是一个抽象基类，不能创建实例（对象）
 * BlueprintType:表示该类可以作为蓝图中的类型使用
 * meta = (DisableNativeTick)​:DisableNativeTick表示禁用这个类在C++端的Tick,不会影响蓝图中的事件Tick
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UFrontendCommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()


public:
	/*
	* ​设置按钮显示文本
	* @param InText:按钮显示文本
	*/
	UFUNCTION(BlueprintCallable)
	void SetButtonText(const FText& InText);
private:
	/*
	* 虚幻引擎原生预构建函数（在UMG组件构建前自动调用）
	*/
	virtual void NativePreConstruct() override;
	/*
	* 虚幻引擎原生预构建函数（在文本样式发生变化时自动调用）
	*/
	virtual void NativeOnCurrentTextStyleChanged() override;
	/*
	* 虚幻引擎原生预构建函数（在按钮悬停时自动调用）
	*/
	virtual void NativeOnHovered() override;
    /*
	* 虚幻引擎原生预构建函数（在按钮取消悬停时自动调用）
	*/
	virtual void NativeOnUnhovered() override;
	/*
	* 虚幻引擎原生预构建函数（在按钮按下时自动调用）
	*/
	virtual void NativeOnPressed() override;
	/*
	* 虚幻引擎原生预构建函数（按钮释放时自动调用）
	*/
	virtual void NativeOnReleased() override;

	//*****   绑定控件   *****//

/*
* ​Common UI 插件提供的文本控件类，继承自标准 UTextBlock。
* 与 UTextBlock 相比，它支持更多高级功能：
* 样式主题（Stylesheets）管理
* 平台自适应字体（如不同分辨率）
* 动态游戏状态响应（例如禁用状态自动变灰）
*/
	UPROPERTY( meta = (BindWidgetOptional))
	UCommonTextBlock* CommonTextBlock_ButtonText;
	/*
	* ​按钮显示文本
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDisplayText;
	/*
	* ​用户：按钮文本需大写形式显示
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	bool bUserUpperCaseForButtonText = false;
	/*
	* ​按钮描述文本
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDescriptionText;
};
