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
	int target_var;//�ñ༭���Ӧ��Ŀ�����
	//int* target_value;
	EditBox();
	EditBox(CString& t);
	EditBox(const wchar_t* t);
	void Create();
	int draw(HDC hdc);//�ؼ��Ļ��ƺ���
	int event(int eventtype, int x, int y);
	//virtual int UpdateTargetValue();
	int(*UpdateTargetValueFunc)(int i);//�ÿؼ��Ĺ��ܺ���
};

#endif
