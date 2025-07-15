// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_ActivatableBase.h"

#include "Controllers/FrontEndPlayerController.h"

AFrontEndPlayerController* UWidget_ActivatableBase::GetOwningFrontEndPlayerController()
{
    //检查玩家控制器是否有效
    if (!CachedOwningFrontendPC.IsValid())
    {
        //强类型转换获取实例化的玩家控制器
        CachedOwningFrontendPC = GetOwningPlayer<AFrontEndPlayerController>();
    }
    //如果玩家控制器有效，则返回实例化的玩家控制器，否则返回null。
    return CachedOwningFrontendPC.IsValid()? CachedOwningFrontendPC.Get():nullptr;
}
