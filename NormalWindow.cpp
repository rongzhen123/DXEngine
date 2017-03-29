#include "StdAfx.h"
#include "NormalWindow.h"

void NormalWindow::OnDraw(HDC dc)
{
	//child_controls
	vector<ControlBase*>::iterator it;
	for (it = child_controls.begin(); it != child_controls.end(); it++)
	{
		(*it)->draw(dc);
	}
}

void NormalWindow::OnLButtonDown(int x, int y)
{
	vector<ControlBase*>::iterator it;
	for (it = child_controls.begin(); it != child_controls.end(); it++)
	{
		(*it)->event(EVENT_LBUTTON_DOWN,x,y);
	}
}

void NormalWindow::OnLButtonUp(int x, int y)
{
	vector<ControlBase*>::iterator it;
	for (it = child_controls.begin(); it != child_controls.end(); it++)
	{
		(*it)->event(EVENT_LBUTTON_UP,x,y);
	}
}
/*
void NormalWindow::OnRButtonDown(int x, int y)
{
	vector<ControlBase*>::iterator it;
	for (it = child_controls.begin(); it != child_controls.end(); it++)
	{
		(*it)->event();
	}
}

void NormalWindow::OnRButtonUp(int x, int y)
{
	vector<ControlBase*>::iterator it;
	for (it = child_controls.begin(); it != child_controls.end(); it++)
	{
		(*it)->draw(dc);
	}
}*/
