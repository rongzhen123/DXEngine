#include "stdafx.h"
//#include "6022SelfCheck.h"
//#include "win10scope.h"



//获取某种字体字体类型在DC中占用的空间大小
SizeF GetTextBounds(const Font& font, const StringFormat& strFormat, const CString& szText)
{
	GraphicsPath graphicsPathObj;
	FontFamily fontfamily;
	font.GetFamily(&fontfamily);
	graphicsPathObj.AddString(szText, -1, &fontfamily, font.GetStyle(), font.GetSize(), PointF(0, 0), &strFormat);
	RectF rcBound;
	/// 获取边界范围
	graphicsPathObj.GetBounds(&rcBound);
	/// 返回文本的宽高
	return SizeF(rcBound.Width, rcBound.Height);
}

void DrawRect(HDC comdc, int x, int y, int width, int height)
{
	MoveToEx(comdc, x, y, NULL);
	LineTo(comdc, x + width, y);
	LineTo(comdc, x + width, y + height);
	LineTo(comdc, x, y + height);
	LineTo(comdc, x, y);
}
//画圆角矩形
void DrawRoundRectange(Graphics &g, Color pens, int x, int y, int width, int height)
{
	//设置画图时的滤波模式为消除锯齿现象
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	//创建一个红色的画笔
	Pen *pen = new Pen(pens, 1);
	//画矩形上面的边
	//g.DrawLine(pen, x , y, x + width, y);
	g.DrawLine(pen, x + OFFSET_X, y, x + width - OFFSET_X, y);
	//画矩形下面的边
	g.DrawLine(pen, x + OFFSET_X, y + height, x + width - OFFSET_X, y + height);
	//画矩形左面的边
	g.DrawLine(pen, x, y + OFFSET_Y, x, y + height - OFFSET_Y);
	//画矩形右面的边
	g.DrawLine(pen, x + width, y + OFFSET_Y, x + width, y + height - OFFSET_Y);
	//画矩形左上角的圆角
	g.DrawArc(pen, x, y, OFFSET_X * 2, OFFSET_Y * 2, 180, 90);
	//画矩形右下角的圆角
	g.DrawArc(pen, x + width - OFFSET_X * 2, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 360, 90);
	//画矩形右上角的圆角
	g.DrawArc(pen, x + width - OFFSET_X * 2, y, OFFSET_X * 2, OFFSET_Y * 2, 270, 90);
	//画矩形左下角的圆角
	g.DrawArc(pen, x, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 90, 90);
	delete pen;
}
void DrawRoundRectange(Graphics &g, Color pens, int x, int y, int width, int height,int penwidth)
{
	//设置画图时的滤波模式为消除锯齿现象
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	//创建一个红色的画笔
	Pen *pen = new Pen(pens, penwidth);
	//画矩形上面的边
	//g.DrawLine(pen, x , y, x + width, y);
	g.DrawLine(pen, x + OFFSET_X, y, x + width - OFFSET_X, y);
	//画矩形下面的边
	g.DrawLine(pen, x + OFFSET_X, y + height, x + width - OFFSET_X, y + height);
	//画矩形左面的边
	g.DrawLine(pen, x, y + OFFSET_Y, x, y + height - OFFSET_Y);
	//画矩形右面的边
	g.DrawLine(pen, x + width, y + OFFSET_Y, x + width, y + height - OFFSET_Y);
	//画矩形左上角的圆角
	g.DrawArc(pen, x, y, OFFSET_X * 2, OFFSET_Y * 2, 180, 90);
	//画矩形右下角的圆角
	g.DrawArc(pen, x + width - OFFSET_X * 2, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 360, 90);
	//画矩形右上角的圆角
	g.DrawArc(pen, x + width - OFFSET_X * 2, y, OFFSET_X * 2, OFFSET_Y * 2, 270, 90);
	//画矩形左下角的圆角
	g.DrawArc(pen, x, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 90, 90);
	delete pen;
}
//画圆角矩形
void DrawRoundRectangewithpen(Graphics &g, Color pens, int x, int y, int width, int height,int roundwidth,int penwidth)
{
	//设置画图时的滤波模式为消除锯齿现象
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	//创建一个红色的画笔
	Pen *pen = new Pen(pens, penwidth);
	//画矩形上面的边
	//g.DrawLine(pen, x , y, x + width, y);
	g.DrawLine(pen, x + roundwidth, y, x + width - roundwidth, y);
	//画矩形下面的边
	g.DrawLine(pen, x + roundwidth, y + height, x + width - roundwidth, y + height);
	//画矩形左面的边
	g.DrawLine(pen, x, y + roundwidth, x, y + height - roundwidth);
	//画矩形右面的边
	g.DrawLine(pen, x + width, y + roundwidth, x + width, y + height - roundwidth);
	//画矩形左上角的圆角
	g.DrawArc(pen, x, y, roundwidth * 2, roundwidth * 2, 180, 90);
	//画矩形右下角的圆角
	g.DrawArc(pen, x + width - roundwidth * 2, y + height - roundwidth * 2, roundwidth * 2, roundwidth * 2, 360, 90);
	//画矩形右上角的圆角
	g.DrawArc(pen, x + width - roundwidth * 2, y, roundwidth * 2, roundwidth * 2, 270, 90);
	//画矩形左下角的圆角
	g.DrawArc(pen, x, y + height - roundwidth * 2, roundwidth * 2, roundwidth * 2, 90, 90);
	delete pen;
}
//画圆角矩形
void DrawGroupRectange(Graphics &g, Color pens, int x, int y, int width, int height, CString header, LONG length)
{
	int w = (width - length) / 2;
	//设置画图时的滤波模式为消除锯齿现象
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	//创建一个红色的画笔
	Pen *pen = new Pen(pens, 1);
	//画矩形上面的边
	//g.DrawLine(pen, x , y, x + width, y);
	g.DrawLine(pen, x + OFFSET_X, y, x + w, y);
	g.DrawLine(pen, x + OFFSET_X + w + length, y, x + width - OFFSET_X, y);
	//画矩形下面的边
	g.DrawLine(pen, x + OFFSET_X, y + height, x + width - OFFSET_X, y + height);
	//画矩形左面的边
	g.DrawLine(pen, x, y + OFFSET_Y, x, y + height - OFFSET_Y);
	//画矩形右面的边
	g.DrawLine(pen, x + width, y + OFFSET_Y, x + width, y + height - OFFSET_Y);
	//画矩形左上角的圆角
	g.DrawArc(pen, x, y, OFFSET_X * 2, OFFSET_Y * 2, 180, 90);
	//画矩形右下角的圆角
	g.DrawArc(pen, x + width - OFFSET_X * 2, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 360, 90);
	//画矩形右上角的圆角
	g.DrawArc(pen, x + width - OFFSET_X * 2, y, OFFSET_X * 2, OFFSET_Y * 2, 270, 90);
	//画矩形左下角的圆角
	g.DrawArc(pen, x, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 90, 90);
	delete pen;
}

/* 填充颜色 */
void FillRoundRectangle(Graphics &g, Color color, int x, int y, int width, int height)
{
	//矩形填充的步骤：
	//1、把圆角矩形画分为四个圆角上分成四个同等的扇形外加三个直角矩形
	//2、先填充三个直角矩形
	//3、然后填充四个角上的扇形
	//创建画刷
	Brush *brush = new SolidBrush(color);
	//填充三个直角矩形
	g.FillRectangle(brush, x, y + OFFSET_Y, width, height - OFFSET_Y * 2);
	g.FillRectangle(brush, x + OFFSET_X, y, width - OFFSET_X * 2, height);
	//填充四个角上的扇形区
	//填充左上角扇形
#define PIE_OFFSET 2
	g.FillPie(brush, x, y, OFFSET_X * 2 + PIE_OFFSET, OFFSET_Y * 2 + PIE_OFFSET, 180, 90);
	//填充右下角的扇形
	g.FillPie(brush, x + width - (OFFSET_X * 2 + PIE_OFFSET), y + height - (OFFSET_Y * 2 + PIE_OFFSET), OFFSET_X * 2 + PIE_OFFSET, OFFSET_Y * 2 + PIE_OFFSET, 360, 90);
	//填充右上角的扇形
	g.FillPie(brush, x + width - (OFFSET_X * 2 + PIE_OFFSET), y, (OFFSET_X * 2 + PIE_OFFSET), (OFFSET_Y * 2 + PIE_OFFSET), 270, 90);
	//填充左下角的扇形
	g.FillPie(brush, x, y + height - (OFFSET_X * 2 + PIE_OFFSET), (OFFSET_X * 2 + PIE_OFFSET), (OFFSET_Y * 2 + PIE_OFFSET), 90, 90);
	delete brush;
}
void FillRoundRectangle(Graphics &g, Color color, int x, int y, int width, int height,int roundwidth)
{
	//矩形填充的步骤：
	//1、把圆角矩形画分为四个圆角上分成四个同等的扇形外加三个直角矩形
	//2、先填充三个直角矩形
	//3、然后填充四个角上的扇形
	//创建画刷
	Brush *brush = new SolidBrush(color);
	//填充三个直角矩形
	g.FillRectangle(brush, x, y + roundwidth, width, height - roundwidth * 2);
	g.FillRectangle(brush, x + roundwidth, y, width - roundwidth * 2, height);
	//填充四个角上的扇形区
	//填充左上角扇形
#define PIE_OFFSET 2
	g.FillPie(brush, x, y, roundwidth * 2 + PIE_OFFSET, roundwidth * 2 + PIE_OFFSET, 180, 90);
	//填充右下角的扇形
	g.FillPie(brush, x + width - (roundwidth * 2 + PIE_OFFSET), y + height - (roundwidth * 2 + PIE_OFFSET), roundwidth * 2 + PIE_OFFSET, roundwidth * 2 + PIE_OFFSET, 360, 90);
	//填充右上角的扇形
	g.FillPie(brush, x + width - (roundwidth * 2 + PIE_OFFSET), y, (roundwidth * 2 + PIE_OFFSET), (roundwidth * 2 + PIE_OFFSET), 270, 90);
	//填充左下角的扇形
	g.FillPie(brush, x, y + height - (roundwidth * 2 + PIE_OFFSET), (roundwidth * 2 + PIE_OFFSET), (roundwidth * 2 + PIE_OFFSET), 90, 90);
	delete brush;
}

int choosesearchdeviceop(int x)
{
	return 0;
}

int searchdevice_next_button_hit(int x)
{
	return 0;
}

int searchdevice_quit_button_hit(int x)
{
	return 0;
}

int choosedevice_tip(int x)
{
	return 0;
}

CString GetAppPath()
{
	CString appPath, strPath;
	int at;
	TCHAR tempPath[_MAX_PATH];

	::GetModuleFileName(NULL, tempPath, _MAX_PATH);
	appPath = tempPath;
	at = appPath.ReverseFind('\\');
	appPath = appPath.Left(at);
	return appPath;
}
BOOL IsDirectory(const CString filename)
{
	DWORD dwAttr = ::GetFileAttributes(filename);  //得到文件属性

	if (dwAttr == 0xFFFFFFFF)    // 文件或目录不存在
	{
		return FALSE;
	}
	else if (dwAttr&FILE_ATTRIBUTE_DIRECTORY)  // 如果是目录
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL S_IsValidFileName(CString &strP, CString &strExt)
{
	// LN add 2005/05/18 begin
	BOOL ret;
	//删除开头和结尾的无意字符
	strP.TrimLeft();
	strP.TrimRight();

	// check length > 0
	int length = strP.GetLength();
	if (length <= 0)
	{
		return FALSE;
	}

	// check last \\ or / position
	int pos = 0;
	int pos1 = strP.ReverseFind('\\');
	int pos2 = strP.ReverseFind('/');

	// get max pos
	if (pos1 > pos2)
	{
		pos = pos1;
	}
	else
	{
		pos = pos2;
	}

	// check pos
	if (pos >= 0 && pos < length)
	{
		// valid dir
		ret = IsDirectory(strP.Left(pos));
		if (ret == TRUE)
		{
			CString strT = strP.Right(length - pos - 1);

			// valid file name
			if (strT.
				FindOneOf(_T("\\/:,;*?\"<>|")) == -1
				&& strT.GetLength() > 0)
			{
				// check fdb
				if (strExt.CompareNoCase(_T("*")) == 0)
				{
					return TRUE;
				}
				if (strP.Right(strExt.GetLength()).
					CompareNoCase(strExt) != 0)
				{
					strP += strExt;
				}
				return TRUE;
			}
		}
		return FALSE;
	}

	return TRUE;
	// LN add 2005/05/18 end
}
//判断文件名主体是否合法
//返回值：> 0 合法
//		-1 文件名为空
//		-2 文件名含有不合法字符
//		-3 文件名太长，大于255个字符
int IsValidFileName(CString filename)
{
//	BOOL ret;
	//删除开头和结尾的无意字符
	filename.TrimLeft();
	filename.TrimRight();

	// check length > 0
	int length = filename.GetLength();
	if (length <= 0)
	{
		return -1;
	}
	else if (length >= 20)
	{
		return -3;
	}
	if (filename.FindOneOf(_T("\\/:,;*?\"<>|")) == -1)
	{
		return 1;//合法
	}
	else
	{
		return -2;
	}
}