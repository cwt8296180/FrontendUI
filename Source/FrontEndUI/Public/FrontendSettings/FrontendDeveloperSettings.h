// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "FrontendDeveloperSettings.generated.h"




/*
 * 数据库配置信息
 */
USTRUCT(BlueprintType)
struct FMysqlConnectConfigInfo
{
	GENERATED_BODY()
	/*
	 * 数据库名称
	 */
	UPROPERTY(Config, EditAnywhere, Category = "Mysql", meta = (DisplayName = "数据库名称"))
	FString IP;
	/*
	 * 端口号
	 */
	UPROPERTY(Config, EditAnywhere, Category = "Mysql", meta = (DisplayName = "端口号"))
	FString Port;
	/*
	 * 用户名
	 */
	UPROPERTY(Config, EditAnywhere, Category = "Mysql", meta = (DisplayName = "用户名"))
	FString UserName;
	/*
	 * 密码
	 */
	UPROPERTY(Config, EditAnywhere, Category = "Mysql", meta = (DisplayName = "密码"))
	FString Password;

	FMysqlConnectConfigInfo()
	{
		IP = TEXT("127.0.0.1");
        Port = TEXT("3306");
        UserName = TEXT("root");
		Password = TEXT("123456");
	}

};

class UWidget_ActivatableBase;
/**
 * 项目设置->配置项
 */
UCLASS(Config = Game,defaultconfig, meta = (DisplayName = "Frontend UI Setting"))
class FRONTENDUI_API UFrontendDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	/*
	* 将配置项放到项目设置里的那个分类里
	*/
	virtual FName GetCategoryName() const override;

	/*
	* Gameplay标签和界面映射
	*/
	UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (ForceInlineRow, Categories = "Frontend.Widget"))
	TMap<FGameplayTag,TSoftClassPtr<UWidget_ActivatableBase>> FrontendWidgetMap;

	/*
	* 数据库连接配置
	*/
	UPROPERTY(Config, EditAnywhere, Category = "Mysql")
	FMysqlConnectConfigInfo  MysqlConnectConfigInfo;
	/*
	* 作用说明和数据库表名映射
	*/
	UPROPERTY(Config, EditAnywhere, Category = "Mysql")
	TMap<FString, FString>  MysqlTableName;
};
