#pragma once
#include "stdafx.h"
#ifndef TEXTCONTROL
#define TEXTCONTROL
#include "ControlBase.h"
class TextControl : public ControlBase
{
public:
	TextControl();
	TextControl(CString& t);
	TextControl(const wchar_t* t);
	int draw(HDC hdc);//�ؼ��Ļ��ƺ���
	int event(int eventtype, int x, int y);
};

#endif