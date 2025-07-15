#pragma once

/*
 * 消息界面显示类型枚举
 */
UENUM(BlueprintType) 
enum class EConfirmScreenType : uint8 
{
    //只显示确认按钮类型
    OK,
    //显示确认按钮，显示取消按钮类型
    YesNo,
    //显示确认按钮，显示取消按钮，显示取消按钮类型
    YesNoCancel,
    //未知类型，在蓝图中隐藏，仅用于C++使用
    Unknown     UMETA(Hidden)
};

/*
 * 确认消息显示界面按钮类型枚举
 */
UENUM(BlueprintType)
enum class EConfirmScreenButtonType : uint8
{
    //确认按钮
    Confirmed UMETA(DisplayName = "确认"),
    //取消按钮
    Cancelled UMETA(DisplayName = "取消"),
    //关闭界面
    Closed UMETA(DisplayName = "仅关闭界面"),
    Unknown UMETA(Hidden)//在蓝图中隐藏，仅用于C++使用
};