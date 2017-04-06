#pragma once
#include "stdafx.h"
#ifndef NORMALWINDOW
#define NORMALWINDOW

#include "windowbase.h"
//class WindowBase;
class NormalWindow : public WindowBase
{
public:
	NormalWindow()
	{
		
	}
	 void OnDraw(HDC dc);
	 void OnLButtonDown(int x, int y);
	 void OnLButtonUp(int x, int y);
	 void OnCtrlEditUpdate(HWND ctrl_hwnd);
	 
	 //map<ControlBase*, void*> targetvalues;
	// void OnRButtonDown(int x, int y);
	// void OnRButtonUp(int x, int y);
};
#endif
