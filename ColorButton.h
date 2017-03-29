#pragma once
#include "stdafx.h"
#include "ControlBase.h"

class ColorButton : public ControlBase
{
	int draw(HDC hdc);//控件的绘制函数
	int event(int eventtype, int x, int y);
};