#pragma once
#include "stdafx.h"


#ifndef CONTROLBASE
#define CONTROLBASE
#include "windowbase.h"

extern SizeF GetTextBounds(const Font& font, const StringFormat& strFormat, const CString& szText);
extern void DrawRoundRectange(Graphics &g, Color pens, int x, int y, int width, int height);
extern void DrawGroupRectange(Graphics &g, Color pens, int x, int y, int width, int height, CString header, LONG length);
extern void FillRoundRectangle(Graphics &g, Color color, int x, int y, int width, int height);

extern void DrawRoundRectange(Graphics &g, Color pens, int x, int y, int width, int height, int roundwidth);
//extern void DrawGroupRectange(Graphics &g, Color pens, int x, int y, int width, int height, CString header, LONG length);
extern void FillRoundRectangle(Graphics &g, Color color, int x, int y, int width, int height, int roundwidth);
extern  void DrawRoundRectangewithpen(Graphics &g, Color pens, int x, int y, int width, int height, int roundwidth, int penwidth);

//class DXEngine;
class ControlBase
{
public:
	int x;//λ����Ϣ��������ڿؼ����ڵĴ��ڿͻ������Ͻǵ����꣬�����������Ļ�����꣬���Բ鿴GetClientRect()��GetWindowRect()������
	int y;
	int width;//���
	int height;//�߶�
	COLORREF color;//��ɫ��colorbutton���õ�
	CString owner;//�������ָÿؼ�����һ��ܵ����������fft,passfail��
	control_type type;
	//int title_id;//add 2016/7/9���ÿؼ���title��Ӧ�������ļ��е�ID
	int step_index;
	int font_size;
	CString title;
	BOOL hide;//�Ƿ����ظÿؼ�
	BOOL always_show;//������ΪTRUEʱ������hideΪ��ֵ���ÿؼ�������ʾ
	BOOL enabled;//�Ƿ�ʹ�ܣ���ʹ��ʱ����
	int current_state;//��ǰ�ؼ�״̬�����绬�������п��͹�����״̬��singlegrid(��ѡ�б�)�ĵ�ǰ״̬���ǵ�ǰѡ�е��ǵڼ�����
	int(*event_func)(int i);//�ÿؼ��Ĺ��ܺ���
	int(*update_value)(int x);//�ÿؼ��ĸ��µ�ǰֵ����
	int origin_x;//�ÿؼ��ڴ����е�ԭʼλ��
	BOOL ifhit;//�Ƿ񱻵������갴��ʱ�ڴ˿ؼ��ϸ�ֵΪTRUE;
	//view* subview;
	int scrool_pos;
	//HWND parent;//�ÿؼ��ĸ�����
	//WindowBase* parent;
	void *userdata;//ָ���û��Զ���ĸ�������

	BOOL if_follow_scrool;//�Ƿ���ٹ�������Щ�ؼ����ж��¼�ʱ����Ҫ��������λ����Ϣ��ӵ��Լ���λ����Ϣ��,�󲿷ֿؼ�����Ҫ��Ĭ��ΪTRUE,ֻ�������ؼ�����Ҫ�����Ըı��ֵ
	ControlBase()
	{
		//ZeroMemory(this, sizeof(windowitem));//dangerous!!
		enabled = TRUE;
		hide = FALSE;
		always_show = FALSE;
		if_follow_scrool = TRUE;
		ifhit = FALSE;
		update_value = NULL;
		step_index = -1;
		font_size = 20;
		scrool_pos = 0;
	}
	virtual ~ControlBase()
	{

	}
	virtual int draw(HDC hdc)//�ؼ��Ļ��ƺ���
	{
		return 1;
	}
	virtual int draw_forward(HDC hdc)//�˵���ǰ����ʱ���øû���
	{
		return 1;
	}
	virtual int draw_backward(HDC hdc)//�˵����󻬶�ʱ���øû���
	{
		return 1;
	}
	virtual int event(int eventtype, int x, int y)//�ؼ����¼�������
	{
		return 0;
	}

};

#endif