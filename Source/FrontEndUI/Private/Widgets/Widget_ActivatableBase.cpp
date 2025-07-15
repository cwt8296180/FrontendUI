// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_ActivatableBase.h"

#include "Controllers/FrontEndPlayerController.h"

AFrontEndPlayerController* UWidget_ActivatableBase::GetOwningFrontEndPlayerController()
{
    //�����ҿ������Ƿ���Ч
    if (!CachedOwningFrontendPC.IsValid())
    {
        //ǿ����ת����ȡʵ��������ҿ�����
        CachedOwningFrontendPC = GetOwningPlayer<AFrontEndPlayerController>();
    }
    //�����ҿ�������Ч���򷵻�ʵ��������ҿ����������򷵻�null��
    return CachedOwningFrontendPC.IsValid()? CachedOwningFrontendPC.Get():nullptr;
}
