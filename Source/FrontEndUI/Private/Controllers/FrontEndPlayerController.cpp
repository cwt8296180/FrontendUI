// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/FrontEndPlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "Camera/CameraActor.h"

void AFrontEndPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	//�������Default����ǩ�����������
	TArray<AActor*> FoundCameras;
	//���þ�̬������ȡ����Default����ǩ�����������
	UGameplayStatics::GetAllActorsOfClassWithTag(this,ACameraActor::StaticClass(),FName("Default"), FoundCameras);
	//���鲻Ϊ��
	if (!FoundCameras.IsEmpty())
    {
		//�����ӽ�
        SetViewTarget(FoundCameras[0]);
    }
}
