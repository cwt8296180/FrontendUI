// Fill out your copyright notice in the Description page of Project Settings.


#include "FrontendSettings/FrontendDeveloperSettings.h"

FName UFrontendDeveloperSettings::GetCategoryName() const
{
	//������Ŀ������FName("Project")
	//������Ϸ������FName("Game")
	return FName("Game");
}
