#include "StdAfx.h"
#include "TextControl.h"

TextControl::TextControl() :ControlBase()
{

}

TextControl::TextControl(CString & t) : ControlBase()
{
	title = t;
}

TextControl::TextControl(const wchar_t * t)
{
	title = t;
}

int TextControl::draw(HDC hdc)
{
	if (this->hide == FALSE)
	{
		Graphics g(hdc);
		StringFormat stringformat;
		stringformat.SetFormatFlags(StringFormatFlagsNoClip);
		SolidBrush brush(Color(255, GetRValue(color), GetGValue(color), GetBValue(color)));
		g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
		FontFamily fontFamily(L"ËÎÌו");
		Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
		Gdiplus::PointF point1(this->x, this->y + scrool_pos);
		Gdiplus::RectF rect(this->x, this->y, this->width, this->height);
		g.DrawString(title, -1, &font1, rect, &stringformat, &brush);
	}
	return 0;
}

int TextControl::event(int eventtype, int x, int y)
{
	return 0;
}
