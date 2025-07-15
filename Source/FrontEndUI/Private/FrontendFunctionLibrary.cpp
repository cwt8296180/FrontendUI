// Fill out your copyright notice in the Description page of Project Settings.


#include "FrontendFunctionLibrary.h"

#include "FrontendSettings/FrontendDeveloperSettings.h"

TSoftClassPtr<UWidget_ActivatableBase> UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(UPARAM(meta = (Categories = "Frontend.Widget"))FGameplayTag InWidgetTag)
{
    // 获取前端开发者设置（UFrontendDeveloperSettings 的默认 CDO 对象）
    // 使用虚幻引擎的 GetDefault<> 模板函数获取项目设置对象
    const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
    // 使用checkf宏进行开发阶段断言验证：
    // 1. 检查设置对象中的FrontendWidgetMap是否包含输入的标签
    // 2. 如果不存在，断言失败并输出包含标签名的错误信息
    checkf(FrontendDeveloperSettings->FrontendWidgetMap.Contains(InWidgetTag), 
        TEXT("Could not find the corresponding widget under the tag %s"), *InWidgetTag.ToString())
        // 返回与输入标签关联的小部件类软引用：
        // 1. 使用FindRef安全查找（避免二次查找）
        // 2. 返回类型为 TSoftClassPtr<UWidget_ActivatableBase> 
        //    这是虚幻引擎的软引用指针，异步安全加载小部件蓝图类
    return FrontendDeveloperSettings->FrontendWidgetMap.FindRef(InWidgetTag);
}

FMysqlConnectConfigInfo UFrontendFunctionLibrary::GetMysqlConnectConfigInfo(TMap<FString, FString>& OutMysqlTableName)
{
    // 获取前端开发者设置（UFrontendDeveloperSettings 的默认 CDO 对象）
    // 使用虚幻引擎的 GetDefault<> 模板函数获取项目设置对象
    const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
    // 使用checkf宏进行开发阶段断言验证：
    // 1. 检查设置对象中的FrontendWidgetMap是否包含输入的标签
    // 2. 如果不存在，断言失败并输出包含标签名的错误信息
    OutMysqlTableName = FrontendDeveloperSettings->MysqlTableName;
    return FrontendDeveloperSettings->MysqlConnectConfigInfo;
}

