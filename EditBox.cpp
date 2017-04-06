#include "StdAfx.h"
#include "EditBox.h"

EditBox::EditBox()
	:content(L""),
	background_color(RGB(0,255,0)),
	text_color(RGB(0,0,0)),
	text_font_size(20), 
	text_align_type(Align_LEFT),
	ControlBase()
{
	type = Edit_Box;
}

EditBox::EditBox(CString & t)
	:content(t),
	background_color(RGB(0, 255, 0)),
	text_color(RGB(0, 0, 0)),
	text_font_size(20),
	text_align_type(Align_LEFT),
	ControlBase()
{
	type = Edit_Box;
}

EditBox::EditBox(const wchar_t * t) 
	:content(t),
	background_color(RGB(0, 255, 0)),
	text_color(RGB(0, 0, 0)),
	text_font_size(20),
	text_align_type(Align_LEFT),
	content_type(Content_Type_Digit_Int),
	ControlBase()
{
	type = Edit_Box;
}

void EditBox::Create()
{
	hwnd = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER /*| WS_VSCROLL*/ | ES_LEFT | DT_VCENTER, x+50, y, width, height, parent_hwnd, NULL, NULL, NULL);
	if (!hwnd)
	{
		CString tip;
		tip.Format(L"´´½¨edit¿Ø¼þÊ§°Ü,ERROR ID = %d",GetLastError());
		AfxMessageBox(tip);
		return;
	}
	if (hide)
	{
		ShowWindow(hwnd, FALSE);
	}
	else
	{
		ShowWindow(hwnd, TRUE);
	}
	
	UpdateWindow(hwnd);
	type = Edit_Box;
	//´´½¨Âß¼­×ÖÌå
	/*HFONT hFont = CreateFont(20, 20, 0, 0, 400 ,
		FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
		FF_DONTCARE, TEXT("Î¢ÈíÑÅºÚ"));

	SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, NULL);*/

}

int EditBox::draw(HDC hdc)
{
	if (this->hide == FALSE)
	{
		Graphics g(hdc);
		StringFormat stringformat;
		stringformat.SetFormatFlags(StringFormatFlagsNoClip);
		SolidBrush brush(Color(255, GetRValue(color), GetGValue(color), GetBValue(color)));
		g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
		FontFamily fontFamily(L"ËÎÌå");
		Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
		Gdiplus::PointF point1(this->x, this->y + scrool_pos);
		Gdiplus::RectF rect(this->x, this->y+2, this->width, this->height);
		g.DrawString(title, -1, &font1, rect, &stringformat, &brush);
		ShowWindow(hwnd, TRUE);
	}
	else
	{
		ShowWindow(hwnd, FALSE);
	}
	return 0;
}

int EditBox::event(int eventtype, int x, int y)
{
	return 0;
}

