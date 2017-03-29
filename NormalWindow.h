#pragma once
#include "stdafx.h"
#include "windowbase.h"

class NormalWindow : public WindowBase
{
	 void OnDraw(HDC dc);
	 void OnLButtonDown(int x, int y);
	 void OnLButtonUp(int x, int y);
	// void OnRButtonDown(int x, int y);
	// void OnRButtonUp(int x, int y);
};
