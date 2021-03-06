#include "StdAfx.h"
#include "ColorButton.h"
//#include "DXEngine.h"
#include "EditBox.h"
ColorButton::ColorButton()
	:ControlBase()
{
	color = RGB(255,0,0);
	text_color = RGB(255,255,255);
}

int ColorButton::draw(HDC hdc)
{
	if (this->hide == FALSE)
	{
		Graphics g(hdc);
		StringFormat stringformat;

		SolidBrush brush(Color(255, GetRValue(text_color), GetGValue(text_color), GetBValue(text_color)));
		g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
		FontFamily fontFamily(L"����");
		if (this->if_follow_scrool == TRUE)
		{
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + scrool_pos, this->width - 25, this->height);
			if (enabled)
			{
				FillRoundRectangle(g, Color(255, GetRValue(color), GetGValue(color), GetBValue(color)), this->x, this->y + scrool_pos, this->width - 25, this->height, 0);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x, this->y + scrool_pos, this->width - 25, this->height, 0);
			}
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - 25 - t.Width;
			int h = (this->height - t.Height) / 2;
			Gdiplus::PointF point0(this->x + w / 2 - 5, this->y + h + scrool_pos);
			g.DrawString(this->title, -1, &font2, point0, &brush);
		}
		else
		{
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y, this->width - 25, this->height, 0);
			if (enabled)
			{
				FillRoundRectangle(g, Color(255, GetRValue(color), GetGValue(color), GetBValue(color)), this->x, this->y, this->width - 25, this->height, 0);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x, this->y, this->width - 25, this->height, 0);
			}
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - 25 - t.Width;
			int h = (this->height - t.Height) / 2;
			Gdiplus::PointF point0(this->x + w / 2 - 5, this->y + h);
			g.DrawString(this->title, -1, &font2, point0, &brush);
		}
	}
	return 0;
}

int ColorButton::event(int eventtype, int x, int y)
{
	if (EVENT_LBUTTON_UP == eventtype)
	{
		if (this->enabled == TRUE)
		{
			if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + scrool_pos && y <= this->y + this->height + scrool_pos)
			{
				//AfxMessageBox(L"ColorButton up");
				HWND target = (HWND)userdata;
				this->event_func((int)target);
				return 1;
			}
		}
	}
	else
	{
		return 0;
	}
	return 0;
}

CreatePlaneButton::CreatePlaneButton():ColorButton()
{

}

int CreatePlaneButton::event(int eventtype, int x, int y)
{
	if (eventtype == EVENT_LBUTTON_UP)
	{
		if (this->enabled == TRUE)
		{
			if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + scrool_pos && y <= this->y + this->height + scrool_pos)
			{
				AfxMessageBox(L"CreatePlaneButton up");
				//((DXEngineApp*)(userdata))->
				return 1;
			}
		}
	}
	return 0;
}

CreateBoxButton::CreateBoxButton()
{

}

int CreateBoxButton::event(int eventtype, int x, int y)
{
	if (eventtype == EVENT_LBUTTON_UP)
	{
		if (this->enabled == TRUE)
		{
			if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + scrool_pos && y <= this->y + this->height + scrool_pos)
			{
				AfxMessageBox(L"CreateBoxButton up");
				return 1;
			}
		}
	}
	//AfxMessageBox(L"CreateBoxButton");
	return 0;
}

CreateSphereButton::CreateSphereButton()
{

}

int CreateSphereButton::event(int eventtype, int x, int y)
{
	if (eventtype == EVENT_LBUTTON_UP)
	{
		if (this->enabled == TRUE)
		{
			if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + scrool_pos && y <= this->y + this->height + scrool_pos)
			{
				AfxMessageBox(L"CreateSphereButton up");
				return 1;
			}
		}
	}
	//AfxMessageBox(L"CreateSphereButton");
	return 0;
}

CreateCylinderButton::CreateCylinderButton()
{

}

int CreateCylinderButton::event(int eventtype, int x, int y)
{
	//AfxMessageBox(L"CreateCylinderButton");
	if (eventtype == EVENT_LBUTTON_UP)
	{
		if (this->enabled == TRUE)
		{
			if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + scrool_pos && y <= this->y + this->height + scrool_pos)
			{
				AfxMessageBox(L"CreateCylinderButton up");
				return 1;
			}
		}
	}
	return 0;
}

CreateCylinder::CreateCylinder()
{
}

int CreateCylinder::event(int eventtype, int x, int y)
{
	return 0;
}

CreatePlane::CreatePlane()
{
}

int CreatePlane::event(int eventtype, int x, int y)
{
	if (eventtype == EVENT_LBUTTON_UP)
	{
		if (this->enabled == TRUE)
		{
			if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + scrool_pos && y <= this->y + this->height + scrool_pos)
			{	
				if (app->plane_width > 0 && app->plane_depth > 0 && app->m > 0 && app->n > 0)
				{
					app->SetupPlane(app->plane_width, app->plane_depth, app->m, app->n,app->position_x,app->position_y,app->position_z,app->scale_x,app->scale_y,app->scale_z);
				}
				return 1;
			}
		}
	}
	return 0;
}

CreateBox::CreateBox()
{
}

int CreateBox::event(int eventtype, int x, int y)
{
	if (eventtype == EVENT_LBUTTON_UP)
	{
		if (this->enabled == TRUE)
		{
			if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + scrool_pos && y <= this->y + this->height + scrool_pos)
			{
				AfxMessageBox(L"CreateBox up");
				return 1;
			}
		}
	}
	return 0;
}

CreateSphere::CreateSphere()
{
}

int CreateSphere::event(int eventtype, int x, int y)
{
	return 0;
}
