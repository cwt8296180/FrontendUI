// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "FrontendFunctionLibrary.generated.h"


class UWidget_ActivatableBase;
struct FMysqlConnectConfigInfo;
/**
 * 蓝图函数库类
 */
UCLASS()
class FRONTENDUI_API UFrontendFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*
	* 获取项目设置->配置项里的数据,获取界面
	* @param InWidgetTag：一个FGameplayTag类型的常量引用，作为查找的键
	* @return 返回弱引用的界面类 
	*/
	UFUNCTION(BlueprintPure,Category ="Frontend Function Library")
	static TSoftClassPtr<UWidget_ActivatableBase> GetFrontendSoftWidgetClassByTag( UPARAM(meta = (Categories = "Frontend.Widget"))FGameplayTag InWidgetTag);

	/*
	* 获取项目设置->配置项里的数据,数据库连接配置
	* @return 返回数据库连接配置数据
	*/
	UFUNCTION(BlueprintPure, Category = "Frontend Function Library")
	static FMysqlConnectConfigInfo GetMysqlConnectConfigInfo(TMap<FString, FString>& OutMysqlTableName);
};
