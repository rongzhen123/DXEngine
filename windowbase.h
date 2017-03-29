#pragma once
#include "stdafx.h"

#ifndef WINDOWBASE
#define WINDOWBASE
using namespace std;
#include "ControlBase.h"
//#include "DXEngine.h"
//class ControlBase;

class WindowBase
{
public:
	WindowBase();

	int window_width;
	int window_height;
	int position_x;
	int position_y;
	HWND hwnd;
	HWND parent;
	CString title;
	COLORREF color;//ÑÕÉ«
	void* userdata;
	vector<ControlBase*> child_controls;//×Ó¿Ø¼þ

	virtual void OnDraw(HDC dc);
	virtual void OnLButtonDown(int x,int y);
	virtual void OnLButtonUp(int x,int y);
	virtual void OnRButtonDown(int x,int y);
	virtual void OnRButtonUp(int x,int y);
	virtual void OnMouseMove(int mousedown);
	virtual void OnCreate();
	virtual void OnClose();

};

#endif
