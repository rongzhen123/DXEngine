#include "StdAfx.h"
#include "windowbase.h"

WindowBase::WindowBase()
	:window_width(0),
	window_height(0),
	position_x(0),
	position_y(0),
	hwnd(NULL),
	parent(NULL),
	color(RGB(0,255,0)),
	title(L"")
{

}

void WindowBase::OnDraw(HDC dc)
{
}

void WindowBase::OnLButtonDown(int x, int y)
{
}

void WindowBase::OnLButtonUp(int x, int y)
{
}

void WindowBase::OnRButtonDown(int x, int y)
{
}

void WindowBase::OnRButtonUp(int x, int y)
{
}

void WindowBase::OnMouseMove(int mousedown)
{
}

void WindowBase::OnCreate()
{
}

void WindowBase::OnClose()
{
}
