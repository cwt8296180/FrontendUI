// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_ConfirmScreen.h"
#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "ICommonInputModule.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	// 创建一个新的 UConfirmScreenInfoObject 对象，使用 NewObject 方法（在UE中动态创建UObject）
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	// 将传入的界面标题设置给新创建对象的 ScreenTitle 属性
	InfoObject->ScreenTitle = InScreenTitle;
	// 将传入的界面消息设置给新创建对象的 ScreenMessage 属性
    InfoObject->ScreenMessage = InScreenMsg;
	// 创建一个按钮信息结构体 FConfirmScreenButtonInfo 的实例 OKButtonInfo
	FConfirmScreenButtonInfo OKButtonInfo;
	// 设置该按钮的类型为 EConfirmScreenButtonType::Closed，通常表示按下此按钮会关闭界面
	OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Closed;
	// 设置按钮显示的文本为“OK”（使用 FText::FromString 将字符串转换为 FText）
	OKButtonInfo.ButtonTextToDisplay = FText::FromString("OK");
	// 将配置好的按钮信息添加到 InfoObject 的按钮列表（AvailableScreenButtons）中
	InfoObject->AvailableScreenButtons.Add(OKButtonInfo);
	// 返回创建并配置好的信息对象
	return InfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	// 创建一个新的 UConfirmScreenInfoObject 对象，使用 NewObject 方法（在UE中动态创建UObject）
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	// 将传入的界面标题设置给新创建对象的 ScreenTitle 属性
	InfoObject->ScreenTitle = InScreenTitle;
	// 将传入的界面消息设置给新创建对象的 ScreenMessage 属性
	InfoObject->ScreenMessage = InScreenMsg;
	// 创建 YES 按钮配置结构体
	FConfirmScreenButtonInfo YesButtonInfo;
	// 设置 YES 按钮类型为"Yes"（用户同意的操作）
	YesButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	// 设置 YES 按钮显示文本为"Yes"
	YesButtonInfo.ButtonTextToDisplay = FText::FromString("Yes");
	// 创建 NO 按钮配置结构体
	FConfirmScreenButtonInfo NoButtonInfo;
	// 设置 NO 按钮类型为"No"（用户拒绝的操作）
	NoButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	// 设置 NO 按钮显示文本为"No"
	NoButtonInfo.ButtonTextToDisplay = FText::FromString("No");
	// 将配置好的 YES 按钮添加到按钮列表中
	InfoObject->AvailableScreenButtons.Add(YesButtonInfo);
	// 将配置好的 NO 按钮添加到按钮列表中
    InfoObject->AvailableScreenButtons.Add(NoButtonInfo);
	// 返回创建完成的确认屏幕信息对象
	return InfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKCancelScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	// 创建一个新的 UConfirmScreenInfoObject 对象，使用 NewObject 方法（在UE中动态创建UObject）
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	// 将传入的界面标题设置给新创建对象的 ScreenTitle 属性
	InfoObject->ScreenTitle = InScreenTitle;
	// 将传入的界面消息设置给新创建对象的 ScreenMessage 属性
	InfoObject->ScreenMessage = InScreenMsg;
	// 创建 Ok 按钮配置结构体
	FConfirmScreenButtonInfo OkButtonInfo;
	// 设置 Ok 按钮类型为"确认"（用户同意的操作）
	OkButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	// 设置 Ok 按钮显示文本为"确定"
	OkButtonInfo.ButtonTextToDisplay = FText::FromString("Ok");
	// 创建 Cancel 按钮配置结构体
	FConfirmScreenButtonInfo CancelButtonInfo;
	// 设置 Cancel 按钮类型为"Cancel"（用户拒绝的操作）
	CancelButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	// 设置 Cancel 按钮显示文本为"Cancel"
	CancelButtonInfo.ButtonTextToDisplay = FText::FromString("Cancel");
	// 将配置好的 Ok 按钮添加到按钮列表中
	InfoObject->AvailableScreenButtons.Add(OkButtonInfo);
	// 将配置好的 取消 按钮添加到按钮列表中
	InfoObject->AvailableScreenButtons.Add(CancelButtonInfo);
	// 返回创建完成的确认屏幕信息对象
	return InfoObject;
}

void UWidget_ConfirmScreen::InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject, 
	TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
	// 检查传入的信息对象和关键控件指针是否有效（非空）
	check(InScreenInfoObject && CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);
	// 设置标题文本
	CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
	// 设置消息文本
	CommonTextBlock_Message->SetText(InScreenInfoObject->ScreenMessage);
	//检查动态条目框是否有内容
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		//清除所有内容，指定只需清除UFrontendCommonButtonBase类型
		DynamicEntryBox_Buttons->Reset<UFrontendCommonButtonBase>
		(
			// 重置按钮容器，遍历每个条目并清除其点击事件绑定
			[](UFrontendCommonButtonBase& ExistingButton)
			{
				// 清除现有按钮的点击事件绑定
				ExistingButton.OnClicked().Clear();
			}
		);
	}
	// 确保按钮配置数组不为空
	check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty());
	// 遍历每个按钮配置信息
	for (const FConfirmScreenButtonInfo& AvailableButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		// 初始化一个输入操作的数据表行句柄（用于按钮的输入动作）
		FDataTableRowHandle InputActionRowHandle;
		// 根据按钮类型设置不同的默认输入操作
		switch (AvailableButtonInfo.ConfirmScreenButtonType)
		{

            case EConfirmScreenButtonType::Cancelled:
				// 获取取消操作（如"取消"按钮对应的输入操作）
				InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;

            case EConfirmScreenButtonType::Closed:
				// 关闭操作也使用取消操作的输入
				InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;

            case EConfirmScreenButtonType::Unknown:
				// 未知类型，不设置输入操作
			break;

		default:
			break;
		}
		// 创建按钮控件（UFrontendCommonButtonBase类型）并添加到按钮容器中
		UFrontendCommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry< UFrontendCommonButtonBase>();
		// 设置按钮的显示文本
		AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);
		// 设置按钮触发的输入操作（如按手柄A键触发）
		AddedButton->SetTriggeringInputAction(InputActionRowHandle);
		// 为按钮绑定点击事件（Lambda表达式）
		AddedButton->OnClicked().AddLambda
		(
			[ClickedButtonCallback, AvailableButtonInfo,this]()
			{
				// 调用回调函数，传入当前按钮的类型（如确认、取消等）
				ClickedButtonCallback(AvailableButtonInfo.ConfirmScreenButtonType);
				// 关闭当前控件（例如隐藏或移除）
				DeactivateWidget();
			}
		);
	}
	// 如果按钮容器中有按钮，将最后一个按钮设置为焦点（获取输入焦点）
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		//获取最后一个按钮并设置焦点（通常为了方便手柄/键盘导航）
		DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}

}
