#include "stdafx.h"
//#include "6022SelfCheck.h"
//#include "win10scope.h"



//��ȡĳ����������������DC��ռ�õĿռ��С
SizeF GetTextBounds(const Font& font, const StringFormat& strFormat, const CString& szText)
{
	GraphicsPath graphicsPathObj;
	FontFamily fontfamily;
	font.GetFamily(&fontfamily);
	graphicsPathObj.AddString(szText, -1, &fontfamily, font.GetStyle(), font.GetSize(), PointF(0, 0), &strFormat);
	RectF rcBound;
	/// ��ȡ�߽緶Χ
	graphicsPathObj.GetBounds(&rcBound);
	/// �����ı��Ŀ��
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
//��Բ�Ǿ���
void DrawRoundRectange(Graphics &g, Color pens, int x, int y, int width, int height)
{
	//���û�ͼʱ���˲�ģʽΪ�����������
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	//����һ����ɫ�Ļ���
	Pen *pen = new Pen(pens, 1);
	//����������ı�
	//g.DrawLine(pen, x , y, x + width, y);
	g.DrawLine(pen, x + OFFSET_X, y, x + width - OFFSET_X, y);
	//����������ı�
	g.DrawLine(pen, x + OFFSET_X, y + height, x + width - OFFSET_X, y + height);
	//����������ı�
	g.DrawLine(pen, x, y + OFFSET_Y, x, y + height - OFFSET_Y);
	//����������ı�
	g.DrawLine(pen, x + width, y + OFFSET_Y, x + width, y + height - OFFSET_Y);
	//���������Ͻǵ�Բ��
	g.DrawArc(pen, x, y, OFFSET_X * 2, OFFSET_Y * 2, 180, 90);
	//���������½ǵ�Բ��
	g.DrawArc(pen, x + width - OFFSET_X * 2, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 360, 90);
	//���������Ͻǵ�Բ��
	g.DrawArc(pen, x + width - OFFSET_X * 2, y, OFFSET_X * 2, OFFSET_Y * 2, 270, 90);
	//���������½ǵ�Բ��
	g.DrawArc(pen, x, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 90, 90);
	delete pen;
}
void DrawRoundRectange(Graphics &g, Color pens, int x, int y, int width, int height,int penwidth)
{
	//���û�ͼʱ���˲�ģʽΪ�����������
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	//����һ����ɫ�Ļ���
	Pen *pen = new Pen(pens, penwidth);
	//����������ı�
	//g.DrawLine(pen, x , y, x + width, y);
	g.DrawLine(pen, x + OFFSET_X, y, x + width - OFFSET_X, y);
	//����������ı�
	g.DrawLine(pen, x + OFFSET_X, y + height, x + width - OFFSET_X, y + height);
	//����������ı�
	g.DrawLine(pen, x, y + OFFSET_Y, x, y + height - OFFSET_Y);
	//����������ı�
	g.DrawLine(pen, x + width, y + OFFSET_Y, x + width, y + height - OFFSET_Y);
	//���������Ͻǵ�Բ��
	g.DrawArc(pen, x, y, OFFSET_X * 2, OFFSET_Y * 2, 180, 90);
	//���������½ǵ�Բ��
	g.DrawArc(pen, x + width - OFFSET_X * 2, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 360, 90);
	//���������Ͻǵ�Բ��
	g.DrawArc(pen, x + width - OFFSET_X * 2, y, OFFSET_X * 2, OFFSET_Y * 2, 270, 90);
	//���������½ǵ�Բ��
	g.DrawArc(pen, x, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 90, 90);
	delete pen;
}
//��Բ�Ǿ���
void DrawRoundRectangewithpen(Graphics &g, Color pens, int x, int y, int width, int height,int roundwidth,int penwidth)
{
	//���û�ͼʱ���˲�ģʽΪ�����������
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	//����һ����ɫ�Ļ���
	Pen *pen = new Pen(pens, penwidth);
	//����������ı�
	//g.DrawLine(pen, x , y, x + width, y);
	g.DrawLine(pen, x + roundwidth, y, x + width - roundwidth, y);
	//����������ı�
	g.DrawLine(pen, x + roundwidth, y + height, x + width - roundwidth, y + height);
	//����������ı�
	g.DrawLine(pen, x, y + roundwidth, x, y + height - roundwidth);
	//����������ı�
	g.DrawLine(pen, x + width, y + roundwidth, x + width, y + height - roundwidth);
	//���������Ͻǵ�Բ��
	g.DrawArc(pen, x, y, roundwidth * 2, roundwidth * 2, 180, 90);
	//���������½ǵ�Բ��
	g.DrawArc(pen, x + width - roundwidth * 2, y + height - roundwidth * 2, roundwidth * 2, roundwidth * 2, 360, 90);
	//���������Ͻǵ�Բ��
	g.DrawArc(pen, x + width - roundwidth * 2, y, roundwidth * 2, roundwidth * 2, 270, 90);
	//���������½ǵ�Բ��
	g.DrawArc(pen, x, y + height - roundwidth * 2, roundwidth * 2, roundwidth * 2, 90, 90);
	delete pen;
}
//��Բ�Ǿ���
void DrawGroupRectange(Graphics &g, Color pens, int x, int y, int width, int height, CString header, LONG length)
{
	int w = (width - length) / 2;
	//���û�ͼʱ���˲�ģʽΪ�����������
	g.SetSmoothingMode(SmoothingModeAntiAlias);
	//����һ����ɫ�Ļ���
	Pen *pen = new Pen(pens, 1);
	//����������ı�
	//g.DrawLine(pen, x , y, x + width, y);
	g.DrawLine(pen, x + OFFSET_X, y, x + w, y);
	g.DrawLine(pen, x + OFFSET_X + w + length, y, x + width - OFFSET_X, y);
	//����������ı�
	g.DrawLine(pen, x + OFFSET_X, y + height, x + width - OFFSET_X, y + height);
	//����������ı�
	g.DrawLine(pen, x, y + OFFSET_Y, x, y + height - OFFSET_Y);
	//����������ı�
	g.DrawLine(pen, x + width, y + OFFSET_Y, x + width, y + height - OFFSET_Y);
	//���������Ͻǵ�Բ��
	g.DrawArc(pen, x, y, OFFSET_X * 2, OFFSET_Y * 2, 180, 90);
	//���������½ǵ�Բ��
	g.DrawArc(pen, x + width - OFFSET_X * 2, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 360, 90);
	//���������Ͻǵ�Բ��
	g.DrawArc(pen, x + width - OFFSET_X * 2, y, OFFSET_X * 2, OFFSET_Y * 2, 270, 90);
	//���������½ǵ�Բ��
	g.DrawArc(pen, x, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 90, 90);
	delete pen;
}

/* �����ɫ */
void FillRoundRectangle(Graphics &g, Color color, int x, int y, int width, int height)
{
	//�������Ĳ��裺
	//1����Բ�Ǿ��λ���Ϊ�ĸ�Բ���Ϸֳ��ĸ�ͬ�ȵ������������ֱ�Ǿ���
	//2�����������ֱ�Ǿ���
	//3��Ȼ������ĸ����ϵ�����
	//������ˢ
	Brush *brush = new SolidBrush(color);
	//�������ֱ�Ǿ���
	g.FillRectangle(brush, x, y + OFFSET_Y, width, height - OFFSET_Y * 2);
	g.FillRectangle(brush, x + OFFSET_X, y, width - OFFSET_X * 2, height);
	//����ĸ����ϵ�������
	//������Ͻ�����
#define PIE_OFFSET 2
	g.FillPie(brush, x, y, OFFSET_X * 2 + PIE_OFFSET, OFFSET_Y * 2 + PIE_OFFSET, 180, 90);
	//������½ǵ�����
	g.FillPie(brush, x + width - (OFFSET_X * 2 + PIE_OFFSET), y + height - (OFFSET_Y * 2 + PIE_OFFSET), OFFSET_X * 2 + PIE_OFFSET, OFFSET_Y * 2 + PIE_OFFSET, 360, 90);
	//������Ͻǵ�����
	g.FillPie(brush, x + width - (OFFSET_X * 2 + PIE_OFFSET), y, (OFFSET_X * 2 + PIE_OFFSET), (OFFSET_Y * 2 + PIE_OFFSET), 270, 90);
	//������½ǵ�����
	g.FillPie(brush, x, y + height - (OFFSET_X * 2 + PIE_OFFSET), (OFFSET_X * 2 + PIE_OFFSET), (OFFSET_Y * 2 + PIE_OFFSET), 90, 90);
	delete brush;
}
void FillRoundRectangle(Graphics &g, Color color, int x, int y, int width, int height,int roundwidth)
{
	//�������Ĳ��裺
	//1����Բ�Ǿ��λ���Ϊ�ĸ�Բ���Ϸֳ��ĸ�ͬ�ȵ������������ֱ�Ǿ���
	//2�����������ֱ�Ǿ���
	//3��Ȼ������ĸ����ϵ�����
	//������ˢ
	Brush *brush = new SolidBrush(color);
	//�������ֱ�Ǿ���
	g.FillRectangle(brush, x, y + roundwidth, width, height - roundwidth * 2);
	g.FillRectangle(brush, x + roundwidth, y, width - roundwidth * 2, height);
	//����ĸ����ϵ�������
	//������Ͻ�����
#define PIE_OFFSET 2
	g.FillPie(brush, x, y, roundwidth * 2 + PIE_OFFSET, roundwidth * 2 + PIE_OFFSET, 180, 90);
	//������½ǵ�����
	g.FillPie(brush, x + width - (roundwidth * 2 + PIE_OFFSET), y + height - (roundwidth * 2 + PIE_OFFSET), roundwidth * 2 + PIE_OFFSET, roundwidth * 2 + PIE_OFFSET, 360, 90);
	//������Ͻǵ�����
	g.FillPie(brush, x + width - (roundwidth * 2 + PIE_OFFSET), y, (roundwidth * 2 + PIE_OFFSET), (roundwidth * 2 + PIE_OFFSET), 270, 90);
	//������½ǵ�����
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
	DWORD dwAttr = ::GetFileAttributes(filename);  //�õ��ļ�����

	if (dwAttr == 0xFFFFFFFF)    // �ļ���Ŀ¼������
	{
		return FALSE;
	}
	else if (dwAttr&FILE_ATTRIBUTE_DIRECTORY)  // �����Ŀ¼
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
	//ɾ����ͷ�ͽ�β�������ַ�
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
//�ж��ļ��������Ƿ�Ϸ�
//����ֵ��> 0 �Ϸ�
//		-1 �ļ���Ϊ��
//		-2 �ļ������в��Ϸ��ַ�
//		-3 �ļ���̫��������255���ַ�
int IsValidFileName(CString filename)
{
//	BOOL ret;
	//ɾ����ͷ�ͽ�β�������ַ�
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
		return 1;//�Ϸ�
	}
	else
	{
		return -2;
	}
}