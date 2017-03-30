#include "StdAfx.h"
#include "WindowManager.h"

LRESULT CALLBACK WindowManagerProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WindowManager::getInstance()->MsgProc(hwnd, msg, wParam, lParam);
	return 1;
}

WindowManager::WindowManager()
{
	userdata = NULL;
}

WindowManager::WindowManager(const WindowManager& t)
{
	userdata = t.userdata;
	name = t.name;
}

WindowManager& WindowManager::operator=(const WindowManager& t)
{
	instance->name = t.name;
	return (WindowManager&)instance;
}

WindowManager* WindowManager::instance = new WindowManager();

WindowManager * WindowManager::getInstance()
{
	return instance;
}

int WindowManager::Init(HINSTANCE hInst)
{
	WNDCLASSEXW wcex;
	hInstance = hInst;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowManagerProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = NULL;//LoadIcon(hInst, MAKEINTRESOURCE(IDI_MY6022SELFCHECK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_MY6022SELFCHECK);
	wcex.lpszClassName = L"WindowManager";
	wcex.hIconSm = NULL;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	if (RegisterClassExW(&wcex))
	{

	}
	else
	{
		AfxMessageBox(L"RegisterClassExW ERROR");
	}
	windows.clear();

	return 0;
}

LRESULT WindowManager::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	switch (msg)
	{
		case WM_CREATE:
		{
			auto it = windows.find(hwnd);
			if (it != windows.end())
			{
		
			}
		}
		return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_LBUTTONDOWN:
		{
			int x_pos = LOWORD(lParam);
			int y_pos = HIWORD(lParam);
			auto it = windows.find(hwnd);
			if (it != windows.end())
			{
				it->second->OnLButtonDown(x_pos,y_pos);
			}
			return 0;	
		}
		case WM_MBUTTONDOWN:
		{
			int x_pos = LOWORD(lParam);
			int y_pos = HIWORD(lParam);
			auto it = windows.find(hwnd);
			if (it != windows.end())
			{
			//	it->second->OnLButtonDown();
			}
			return 0;
		}
		
		case WM_RBUTTONDOWN:
		{
			int x_pos = LOWORD(lParam);
			int y_pos = HIWORD(lParam);
			auto it = windows.find(hwnd);
			if (it != windows.end())
			{
				it->second->OnRButtonDown(x_pos,y_pos);
			}
			return 0;
		}
		
		case WM_LBUTTONUP:
		{
			int x_pos = LOWORD(lParam);
			int y_pos = HIWORD(lParam);
			auto it = windows.find(hwnd);
			if (it != windows.end())
			{
				it->second->OnLButtonUp(x_pos,y_pos);
			}
			return 0;
		}
		
		case WM_MBUTTONUP:
		{
			int x_pos = LOWORD(lParam);
			int y_pos = HIWORD(lParam);
			auto it = windows.find(hwnd);
			if (it != windows.end())
			{
				//it->second->OnLButtonDown();
			}
			return 0;
		}
		case WM_RBUTTONUP:
		{
			int x_pos = LOWORD(lParam);
			int y_pos = HIWORD(lParam);
			auto it = windows.find(hwnd);
			if (it != windows.end())
			{
				it->second->OnRButtonUp(x_pos,y_pos);
			}
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			int x_pos = LOWORD(lParam);
			int y_pos = HIWORD(lParam);
			return 0;
		}
		
		case WM_PAINT:
		{
			HDC hdc = BeginPaint(hwnd,&ps);
			HDC comdc = CreateCompatibleDC(hdc);
			HBITMAP hbm;
			HBITMAP comdcoldbitmap;
			RECT rect;
			GetClientRect(hwnd, &rect);
			HBRUSH hBrush;
			hbm = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
			comdcoldbitmap = (HBITMAP)SelectObject(comdc, hbm);
			auto it = windows.find(hwnd);
			if (it != windows.end())
			{
				hBrush = CreateSolidBrush(it->second->color);
				FillRect(comdc, &rect, hBrush);
				it->second->OnDraw(comdc);
			}
			BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top - 20, comdc, 0, 0, SRCCOPY);
			SelectObject(comdc, comdcoldbitmap);
			DeleteObject(hbm);
			DeleteDC(comdc);
			EndPaint(hwnd, &ps);
			return 0;
		}
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

int WindowManager::MessageLoop()
{
	MSG msg;
	// 主消息循环: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
	//	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}

HWND WindowManager::RegisterWindow(WindowBase * wb)
{
	HWND hWnd = CreateWindowEx(WS_EX_LAYERED, L"WindowManager", wb->title, WS_OVERLAPPED, 0, 0, wb->window_width, wb->window_height, nullptr, NULL, hInstance, (LPVOID)NULL);
	if (!hWnd)
	{
		CString tip;
		tip.Format(L"RegisterWindow error id = %d", GetLastError());
		AfxMessageBox(tip);
		return NULL;
	}
	ShowWindow(hWnd, TRUE);
	UpdateWindow(hWnd);
	SetLayeredWindowAttributes(hWnd, 0, 250, LWA_ALPHA);
	windows.insert(make_pair(hWnd,wb));
	return hWnd;
}


