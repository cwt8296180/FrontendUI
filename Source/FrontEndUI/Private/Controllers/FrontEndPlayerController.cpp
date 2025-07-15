// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/FrontEndPlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "Camera/CameraActor.h"

void AFrontEndPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	//储存带（Default）标签的所有摄像机
	TArray<AActor*> FoundCameras;
	//调用静态函数获取带（Default）标签的所有摄像机
	UGameplayStatics::GetAllActorsOfClassWithTag(this,ACameraActor::StaticClass(),FName("Default"), FoundCameras);
	//数组不为空
	if (!FoundCameras.IsEmpty())
    {
		//设置视角
        SetViewTarget(FoundCameras[0]);
    }
}
