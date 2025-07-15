// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_PushConfirmScreen.h"
#include "Subsystems/FrontendUISubsystem.h"

UAsyncAction_PushConfirmScreen* UAsyncAction_PushConfirmScreen::PushConfirmScreen(const UObject* WorldContextObject, 
	EConfirmScreenType ScreenType, FText InScreenTitle, FText InScreenMessage)
{
	// ���ȫ������ʵ���Ƿ���ڣ�ȷ�������ѳ�ʼ����
	if (GEngine)
	{
		if (UWorld * World =GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			// ͨ�������Ķ���ȫ��ȡUWorldָ�룺
			// - EGetWorldErrorMode::LogAndReturnNull ��ʾ��ȡʧ��ʱ��¼���󲢷���nullptr
			UAsyncAction_PushConfirmScreen* Node =  NewObject<UAsyncAction_PushConfirmScreen>();
			// ���浱ǰ��Ϸ����ָ��
			Node->CachedOwingWorld    = World;
			// ���洫�����Ϣ��������
			Node->CachedSceenType     = ScreenType;
			// ������Ϣ��������ı���ʹ��FText֧�ֱ��ػ���
			Node->CachedScreenTitle   = InScreenTitle;
			// ������Ϣ������Ϣ�ı���ʹ��FText֧�ֱ��ػ���
			Node->CachedScreenMessage = InScreenMessage;
			// ���첽����ע�ᵽ��Ϸʵ����
			// - ��ֹ�����л�ʱ���������
			// - �����첽��������������
			Node->RegisterWithGameInstance(World);
			// �������úõ��첽��������
			return Node;
		}
	}
	
	return nullptr;
}

void UAsyncAction_PushConfirmScreen::Activate()
{
	// ��ȡǰ��UI��ϵͳ��FrontendUISubsystem����ʵ����ʹ�û����Worldָ��
	// CachedOwingWorld��һ��TWeakObjectPtr<UWorld>������ʹ��Get()������ȡ��UWorldָ��
	// ������ϵͳ�ĺ�������Ϣ�������͵�GameplayTags��ĶԻ����
	UFrontendUISubsystem::Get(CachedOwingWorld.Get())->PushConfirmScreenToModalStackAsync
		// ���ݻ������Ϣ��������
		(CachedSceenType, 
		// ���ݻ������Ϣ��������ı�
		CachedScreenTitle,
		// ���ݻ������Ϣ������Ϣ�ı�
		CachedScreenMessage, 
		// ����һ��lambda������Ϊ�ص������û������ťʱ������
		[this](EConfirmScreenButtonType ClickedButtonType)
		{
			// ���û������ť�󣬹㲥��ť����¼�
			// ������İ�ť���ͣ�ClickedButtonType���㲥�����а󶨵����ί�еĶ���
			OnButtonClicked.Broadcast(ClickedButtonType);
			// ��Ǵ��첽����Ϊ��׼�����١����Ա���������ϵͳ���Ի�����
			SetReadyToDestroy();
		}
	);
}
