// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_PrimaryLayout.h"
#include "FrontendDebugHelper.h"



UCommonActivatableWidgetContainerBase* UWidget_PrimaryLayout::FindWidgetStackByTag(const FGameplayTag& InTag) const
{
	// 使用checkf宏来确保运行时条件满足。这里检查RegisteredWidgetStackMap是否包含键InTag。
	// 如果不包含（即找不到对应的widget stack），则触发断言并输出错误信息，其中包含标签的字符串表示。
	// 注意：在Shipping版本中，checkf宏会被移除，因此这个检查只在开发版本中有效。
	checkf(RegisteredWidgetStackMap.Contains(InTag),TEXT("can not find the widget stack by the tag %s"),*InTag.ToString());
	// 使用FindRef方法从RegisteredWidgetStackMap中查找与InTag关联的值。
	// FindRef在找到时返回对应的值，如果没找到，则返回一个默认构造的值（对于指针类型通常是nullptr）。
	// 但是，由于上面已经用checkf断言了InTag一定存在，所以这里理论上不会返回nullptr。
	// 注意：即使上面的断言触发（在调试时），程序会中断，所以下面的代码在断言失败时不会被执行（在调试配置中）。
	return RegisteredWidgetStackMap.FindRef(InTag);
}

void UWidget_PrimaryLayout::RegisterWidgetStack(UPARAM(meta = (Categories = "Frontend.WidgetStack"))FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	// 检查当前是否处于"设计时"（在编辑器中编辑UI）
	if (!IsDesignTime())
	{	// 检查注册表中是否已存在相同标签的容器
		if (!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			// 将新的UI层级标签和对应容器添加到映射表
			RegisteredWidgetStackMap.Add(InStackTag, InStack);			
		}
	}
}
