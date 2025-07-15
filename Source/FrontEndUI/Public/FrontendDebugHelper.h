#pragma once

namespace Debug
{
	/**
	 * 静态函数：在编辑器中同时输出屏幕消息和日志
	 * @param Msg: 要输出的消息内容
	 * @param Inkey: 屏幕消息唯一标识（可覆盖旧消息），-1 表示自动生成新消息
	 * @InColor: 消息文本颜色(现在是随机颜色)
	 */
	static void Print(const FString& Msg, int32 Inkey = -1, const FColor& InColor = FColor::MakeRandomColor())
	{
		if (GEditor)
		{
			// 添加屏幕调试消息（在编辑器视口中显示）
			// 参数说明：
			//   Inkey: 消息唯一标识（可覆盖旧消息），-1 表示自动生成新消息
			//   7.f: 消息显示持续时间（秒）
			//   InColor: 消息文本颜色
			//   Msg: 要显示的消息内容			
			GEditor->AddOnScreenDebugMessage(Inkey, 7.f, InColor, Msg);
			// 将消息输出到日志系统
			// 参数说明：
			//   LogTemp: 日志类别（临时）
			//   Warning: 日志级别（警告）
			//   TEXT("%s"): 格式化字符串模板
			//   *Msg: 将 FString 转换为 TCHAR* 指针（解引用）
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
	}
  
}