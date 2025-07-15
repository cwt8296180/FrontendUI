// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "FrontendTabListWidgetBase.generated.h"


class UFrontendCommonButtonBase;
/**
 * 选项卡列表基类
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UFrontendTabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()
private:
	/**
	 * 调试编辑器标签预览计数
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Tab List Setting", meta = (AllowPrivateAccess = "true", ClampMin = "1", ClampMax = "10"))
	int32 DebeugEditorPreviewTabCount = 3;
	/**
	 * 插入选项卡列表中的控件
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Tab List Setting", meta = (AllowPrivateAccess = "true", ClampMin = "1", ClampMax = "10"))
	TSubclassOf<UFrontendCommonButtonBase> TabButtonEntryWidgetClass;
};
