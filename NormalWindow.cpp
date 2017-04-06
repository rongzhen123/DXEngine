#include "StdAfx.h"
#include "NormalWindow.h"
#include "ControlBase.h"
#include "EditBox.h"
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
void NormalWindow::OnCtrlEditUpdate(HWND ctrl_hwnd)
{
	vector<ControlBase*>::iterator it;
	for (it = child_controls.begin(); it != child_controls.end(); it++)
	{
		if ((*it)->type == Edit_Box)
		{
			if (((EditBox*)(*it))->hwnd == ctrl_hwnd)
			{
				if (((EditBox*)(*it))->content_type == Content_Type_Digit_Int)
				{
					CString content;
					wchar_t neirong[256];
					GetWindowText(ctrl_hwnd, neirong, 256);
					content = neirong;
					int string_length = content.GetLength();
					if (string_length >= 256)
					{
						GetWindowText(ctrl_hwnd, neirong, 256);
						content = neirong;
						content.Truncate(255);
						SetWindowText(ctrl_hwnd, content);
					}
					//输入框只接受数字，其他的字符不接受
					for (int nIndex = 0; nIndex < string_length; nIndex++)
					{
						if (content[nIndex] > '9' || content[nIndex] < '0')
						{
							CString tmp = content.Left(nIndex) + content.Right(content.GetLength() - nIndex - 1);
							SetWindowText(ctrl_hwnd, tmp);
						}
					}
					GetWindowText(ctrl_hwnd, neirong, 256);
					content = neirong;
					string_length = content.GetLength();
					SendMessage(ctrl_hwnd, EM_SETSEL, string_length, string_length);
				
					((EditBox*)(*it))->target_var = _ttoi(neirong);
					if (((EditBox*)(*it))->UpdateTargetValueFunc != NULL)
					{
						((EditBox*)(*it))->UpdateTargetValueFunc(((EditBox*)(*it))->target_var);
					}
					//*((EditBox*)(*it))->target_value = ((EditBox*)(*it))->target_var;
				/*	CString tip;
					tip.Format(L"value=%d,plane_width=%d,plane_depth=%d,m=%d,n=%d",*value, plane_width, plane_depth,m,n);
					AfxMessageBox(tip);*/
					return;
				}
				else if (((EditBox*)(*it))->content_type == Content_Type_Alphabet)
				{

				}
				else if (((EditBox*)(*it))->content_type == Content_Type_Digit_Float)
				{

				}
				else if (((EditBox*)(*it))->content_type == Content_Type_Any)
				{

				}
			}
		}
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
