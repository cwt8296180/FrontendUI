// Fill out your copyright notice in the Description page of Project Settings.


#include "FrontendSettings/FrontendDeveloperSettings.h"

FName UFrontendDeveloperSettings::GetCategoryName() const
{
	//放在项目分类里FName("Project")
	//放在游戏分类里FName("Game")
	return FName("Game");
}
