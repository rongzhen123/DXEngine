#pragma once
#include "stdafx.h"


#ifndef CONTROLBASE
#define CONTROLBASE
#include "windowbase.h"

extern SizeF GetTextBounds(const Font& font, const StringFormat& strFormat, const CString& szText);
extern void DrawRoundRectange(Graphics &g, Color pens, int x, int y, int width, int height);
extern void DrawGroupRectange(Graphics &g, Color pens, int x, int y, int width, int height, CString header, LONG length);
extern void FillRoundRectangle(Graphics &g, Color color, int x, int y, int width, int height);

extern void DrawRoundRectange(Graphics &g, Color pens, int x, int y, int width, int height, int roundwidth);
//extern void DrawGroupRectange(Graphics &g, Color pens, int x, int y, int width, int height, CString header, LONG length);
extern void FillRoundRectangle(Graphics &g, Color color, int x, int y, int width, int height, int roundwidth);
extern  void DrawRoundRectangewithpen(Graphics &g, Color pens, int x, int y, int width, int height, int roundwidth, int penwidth);

//class DXEngine;
class ControlBase
{
public:
	int x;//位置信息，是相对于控件所在的窗口客户区左上角的坐标，不是相对于屏幕的坐标，可以查看GetClientRect()和GetWindowRect()的区别
	int y;
	int width;//宽度
	int height;//高度
	COLORREF color;//颜色，colorbutton有用到
	CString owner;//用来区分该控件是哪一项功能的设置项，比如fft,passfail等
	control_type type;
	//int title_id;//add 2016/7/9，该控件的title对应在语言文件中的ID
	int step_index;
	int font_size;
	CString title;
	BOOL hide;//是否隐藏该控件
	BOOL always_show;//当该项为TRUE时，不管hide为何值，该控件总是显示
	BOOL enabled;//是否使能，不使能时灰显
	int current_state;//当前控件状态，比如滑动开关有开和关两种状态，singlegrid(单选列表)的当前状态就是当前选中的是第几个等
	int(*event_func)(int i);//该控件的功能函数
	int(*update_value)(int x);//该控件的更新当前值函数
	int origin_x;//该控件在窗口中的原始位置
	BOOL ifhit;//是否被点击，鼠标按下时在此控件上该值为TRUE;
	//view* subview;
	int scrool_pos;
	//HWND parent;//该控件的父窗口
	//WindowBase* parent;
	void *userdata;//指向用户自定义的附加数据

	BOOL if_follow_scrool;//是否跟踪滚动，有些控件在判断事件时不需要将滚动的位置信息添加到自己的位置信息中,大部分控件都需要，默认为TRUE,只有少数控件不需要，可以改变此值
	ControlBase()
	{
		//ZeroMemory(this, sizeof(windowitem));//dangerous!!
		enabled = TRUE;
		hide = FALSE;
		always_show = FALSE;
		if_follow_scrool = TRUE;
		ifhit = FALSE;
		update_value = NULL;
		step_index = -1;
		font_size = 20;
		scrool_pos = 0;
	}
	virtual ~ControlBase()
	{

	}
	virtual int draw(HDC hdc)//控件的绘制函数
	{
		return 1;
	}
	virtual int draw_forward(HDC hdc)//菜单往前滑动时调用该画法
	{
		return 1;
	}
	virtual int draw_backward(HDC hdc)//菜单往后滑动时调用该画法
	{
		return 1;
	}
	virtual int event(int eventtype, int x, int y)//控件的事件捕获函数
	{
		return 0;
	}

};

#endif