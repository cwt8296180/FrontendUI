// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widget_OptionsScreen.generated.h"

/**
 * 选项界面类
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UWidget_OptionsScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()
protected:
	/**
	 * 当控件首次在游戏中初始化时调用（UE控件生命周期的一部分）
	 */
	virtual void NativeOnInitialized() override;
private:
	/**
	 * 当重置动作触发时执行的函数
	 */
	void OnResetBoundActionTriggered();
	/**
	 * 当返回动作触发时执行的函数
	 */
	void OnBackBoundActionTriggered();
	/**
	 * 重置当前选定按钮配置
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;
	/**
	 * 重置UI动作绑定
	 */
	FUIActionBindingHandle ResetActionHandle;
};
