#pragma once
#include "stdafx.h"
#include "windowbase.h"
//

#ifndef WINDOWMANAGER
#define WINDOWMANAGER

using namespace std;

LRESULT CALLBACK WindowManagerProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


class WindowManager
{
public:

	void* userdata;//存放用户自定义数据
	static WindowManager* getInstance();
	int Init(HINSTANCE hInst);
	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	int MessageLoop();
	BOOL RegisterWindow(WindowBase* wb);

	CString name;
	map<HWND, WindowBase*> windows;
	HINSTANCE hInstance;
private:
	WindowManager();
	WindowManager(const WindowManager&);
	WindowManager& operator=(const WindowManager&);
	static WindowManager* instance;

};

#endif