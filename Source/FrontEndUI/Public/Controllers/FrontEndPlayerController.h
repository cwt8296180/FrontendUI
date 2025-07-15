// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrontEndPlayerController.generated.h"

/*
 * 玩家控制器类
 */
UCLASS()
class FRONTENDUI_API AFrontEndPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	/**
	 * 当角色被玩家控制器控制时调用，继承父类方法
	 */
	virtual void OnPossess(APawn* aPawn) override;
};
