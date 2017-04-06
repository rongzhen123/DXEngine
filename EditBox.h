#pragma once
#include "stdafx.h"
#ifndef EDITBOX
#define EDITBOX
#include "ControlBase.h"
class EditBox : public ControlBase
{
public:
	HWND hwnd;
	CString content;
	COLORREF background_color;
	COLORREF text_color;
	int text_font_size;
	Edit_Text_Align_Type text_align_type;
	Content_Type content_type;
	int target_var;//该编辑框对应的目标变量
	//int* target_value;
	EditBox();
	EditBox(CString& t);
	EditBox(const wchar_t* t);
	void Create();
	int draw(HDC hdc);//控件的绘制函数
	int event(int eventtype, int x, int y);
	//virtual int UpdateTargetValue();
	int(*UpdateTargetValueFunc)(int i);//该控件的功能函数
};

#endif
