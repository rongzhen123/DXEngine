#pragma once
#include "stdafx.h"
#include "ControlBase.h"

class ColorButton : public ControlBase
{
	int draw(HDC hdc);//�ؼ��Ļ��ƺ���
	int event(int eventtype, int x, int y);
};