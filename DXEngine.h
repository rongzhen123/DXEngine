#pragma once

#include "resource.h"
#pragma once

#include "resource.h"

ULONG_PTR m_gdiplusToken;
ULONG_PTR m_gdiplusToken1;
#include <stdio.h>
#include <setupapi.h>
#include <devguid.h>
#include <regex>
#include <comdef.h>
//#include "animation.h"
#include <time.h>
#include <tchar.h>
#include <string>
#include <limits>
#include <Mmsystem.h>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
#include <commdlg.h>
using namespace std;
#define swap(x,y) int temp = x;x=y;y=temp;

static CHOOSECOLOR stChooseColor;
static COLORREF rgbBackgroundColor = RGB(135, 206, 250);
static COLORREF crCustColors[6];
static int checkresult = 0;
#ifdef HANTEK6022D
#define SELF_CHECK_STEP_NUMBER 23  //自检步骤数目
//#define CONFIG_FILE_NAME L"\\6022BL_config.ini"
#else
#define SELF_CHECK_STEP_NUMBER 22
//
#endif
#define CONFIG_FILE_NAME L"\\6022BE_config.ini"
#define SLIDE_BUTTON_ON 1	//自定义的滑块控件的两种状态
#define SLIDE_BUTTON_OFF 0

#define UPDATE_CURRENT_STATE_TIMER 1
#define ERROR_UPDATE_TIMER 2

#define EVENT_LBUTTON_UP 1	//自定义的控件事件类型
#define EVENT_LBUTTON_DOWN 2
#define EVENT_MOUSEMOVE 3
#define EVENT_MOUSEOUT_UP 4 //鼠标松开

#define CHECK_PASS_COLOR GREEN_COLOR
#define CHECK_FAILED_COLOR RED_COLOR

//-------------颜色定义--------------
#define		TRANSPARENT_COLOR			RGB(236,233,216)	//定义透明色
#define		BLACK_COLOR					RGB(0,0,0)			//黑色
#define		WHITE_COLOR					RGB(255,255,255)	//白色
#define		RED_COLOR					RGB(255,0,0)		//红色
#define		PINK_COLOR					RGB(255,0,255)		//粉红色
#define		PLUM_RED_COLOR				RGB(255,160,204)	//梅红色
#define		GREEN_COLOR					RGB(0,255,0)		//绿色
#define		JADEGREEN_COLOR				RGB(128,255,128)	//浅绿色
#define		BLUE_COLOR					RGB(0,0,200)		//蓝色
#define		SKY_COLOR					RGB(0,255,255)		//天蓝色
#define		LIGHT_BLUE_COLOR			RGB(51,102,205)		//浅蓝色
#define		YELLOW_COLOR				RGB(255,255,0)		//黄色
#define		GOLDEN_YELLOW_COLOR			RGB(255,204,0)		//金黄色
#define		BROWN_COLOR					RGB(255,128,0)		//棕色
#define		FRENCHGRAY_COLOR			RGB(155,155,155)	//浅灰色
#define		DEEPGRAY_COLOR				RGB(50,50,50)		//深灰色
#define		PURPLE_COLOR				RGB(204,153,255)	//紫色
#define		BACK_COLOR					RGB(29,38,238)		//tip窗口背景色


#define WM_SET_TIMEBASE WM_USER + 1000
#define WM_SET_VOLTDIV WM_USER + 1001
#define WM_CHECK_6022_OK WM_USER + 1002
#define WM_6022_IMOK WM_USER + 1003
#define WM_6022_MAPFILE_ERROR WM_USER + 1004
#define WM_FACTORY_SETUP WM_USER + 1005
#define WM_6022_NOT_READY WM_USER + 1006
#define WM_CH1_ON WM_USER + 1007
#define WM_CH2_ON WM_USER + 1008
#define WM_CHECK_AMP WM_USER + 1009
#define WM_CHECK_AMP_PASS WM_USER + 1010
#define WM_CHECK_AMP_FAILED WM_USER + 1011
#define WM_CHECK_AMP_NOTREADY WM_USER + 1012
#define WM_SET_DEVMODE WM_USER + 1013

#define WM_CHECK_LA_6022_OK WM_USER + 1014
#define WM_LA_6022_IMOK WM_USER + 1015
#define WM_LA_6022_NOT_READY WM_USER + 1016
#define WM_LA_6022_COLLECT_DATA WM_USER + 1017
#define WM_CHECK_LA WM_USER + 1018
#define WM_CHECK_LA_PASS WM_USER + 1019
#define WM_CHECK_LA_FAILED WM_USER + 1020
#define WM_CHECK_LA_NOTREADY WM_USER + 1021
#define WM_LA_6022_DATA_READY WM_USER + 1022
#define WM_SET_LEVER_POS WM_USER + 1023
#define WM_CHECK_MEAN WM_USER + 1024
#define WM_CHECK_FREQ WM_USER + 1025
#define WM_CHECK_AMP_MEAN WM_USER + 1026
#define WM_CHECK_TWO_AMP WM_USER + 1027
#define WM_AUTO_CALIBRATE WM_USER + 1028
#define WM_AUTO_CALIBRATE_OK WM_USER + 1029
#define WM_AUTO_CALIBRATE_FAILED WM_USER + 1030
#define WM_CHECK_RMS WM_USER + 1031
#define WM_CHECK_RMS_NOT_READY WM_USER + 1032
#define WM_CHECK_RMS_PASS WM_USER + 1033
#define WM_CHECK_FREQ_PASS WM_USER + 1034
#define WM_CHECK_FREQ_NOT_READY WM_USER + 1035
#define WM_CHECK_RMS_FAILED WM_USER + 1036
#define WM_CHECK_FREQ_FAILED WM_USER + 1037

#define WM_CHANNEL_ON WM_USER + 1038
#define WM_ALL_CH_ON WM_USER + 1039

#define WM_6022BE_PLUG WM_USER + 2000
#define WM_6022BE_LOST WM_USER + 2001
#define WM_SHUTDOWN_YOURSELF WM_USER + 2002

#define DEVMODE_6022_LA 0
#define DEVMODE_6022_BE 1


// 全局变量:
HINSTANCE hInst;								// 当前实例

HWND ghwnd;
HWND loghwnd;
struct windowitem;
HWND product_type;
extern CString GetAppPath();
extern int IsValidFileName(CString filename);
static BOOL hdgok = FALSE;
static BOOL dso6022ok = FALSE;
static BOOL recvfrom6022 = FALSE;
static BOOL dso6022ready = FALSE;
static BOOL dsoampcheckpass = FALSE;
static BOOL dsoampcheckready = FALSE;
static BOOL dsofreqcheckpass = FALSE;
static BOOL dsofreqcheckready = FALSE;
static BOOL dsormscheckpass = FALSE;
static BOOL dsormscheckready = FALSE;
static BOOL LA6022ok = FALSE;
static BOOL recvfrom6022LA = FALSE;
static BOOL LA6022ready = FALSE;
static BOOL LA6022DataReady = FALSE;
static BOOL LA6022DataCheckPass = FALSE;
static int error_step_index = -1;
static BOOL haserror = FALSE;
static BOOL dev_lost = FALSE;
static BOOL single_check = FALSE;
static BOOL auto_calibrateok = FALSE;
static USHORT current_show_step = 0;
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);//枚举6022示波器上位机软件主窗口

//BOOL CreateNewDocument();
int current_step_index;


//触摸事件的ID，相关信息请查看MSDN关于触摸编程的相关页面
DWORD dwid1, dwid2;

POINT finger1_old;//触点1按下屏幕时的坐标
POINT finger2_old;//触点2按下屏幕时的坐标
POINT finger1;//触点1当前的位置
POINT finger2;//触点2当前的位置

float before_move_pos_y;
float after_move_pos_y;
float updown_times;
float current_timebase_pos;
float current_voltdiv_pos;
float old_timebase_pos;

float passfail_menu_scroll_pos;

BOOL selected_new_timebase;

BOOL support_touch;		//是否支持触摸，用在电脑上调试用
BOOL can_menurool;		//菜单是否开启滚动，当菜单内容高度大于菜单窗口高度时开启
BOOL moving;			//是否是鼠标或触摸移动
POINT _ptFirst;        // first significant point of the gesture
POINT _ptSecond;       // second significant point of the gesture
DWORD _dwArguments;    // 4 bytes long argument
					   // One of the fields in GESTUREINFO structure is type of ULONGLONG (8 bytes).
					   // The relevant gesture information is stored in lower 4 bytes. This
					   // macro is used to read gesture information from this field.
#define LODWORD(ull) ((DWORD)((ULONGLONG)(ull) & 0x00000000ffffffff))

CString voltdiv1[12] = { L"2mV",L"5mV",L"10mV",L"20mV",L"50mV", L"100mV",L"200mV", L"500mV",L"1V", L"2V",L"5V", L"10V" };

CString timebases1[36] = { L"2ns",L"5ns",L"10ns",L"20ns", L"50ns",L"100ns", L"200ns",L"500ns", L"1us",L"2us", L"5us",L"10us", L"20us",L"50us", L"100us",L"200us", L"500us"
,L"1ms", L"2ms",L"5ms", L"10ms",L"20ms", L"50ms",L"100ms", L"200ms",L"500ms", L"1s",L"2s", L"5s",L"10s",L"20s",L"50s",L"100s",L"200s",L"500s",L"1000s" };

BOOL CH1_WAVE_CLICKED;
BOOL CH2_WAVE_CLICKED;
BOOL CH3_WAVE_CLICKED;
BOOL CH4_WAVE_CLICKED;
BOOL MATH_WAVE_CLICKED;
BOOL REF_WAVE_CLICKED;

BOOL SHOW_TIMEBASE_SCROOL;
float timebase_scrool_factor;//设置时基窗口滚动条的相对大小比例
float voltdiv_scrool_factor;
float utility_scrool_factor;
float utility_scrool_height;


CString cursor_result_freq;
CString cursor_result_voltage;
CString cursor_result_time;
CString cursor_result_period;

int x_zoom;
int y_zoom;
//下面的两个变量用来计算是ZOOM IN 还是 ZOOM OUT
int old_finger_distance;//触摸按下时两个手指的距离
int finger_distance;	//目前两个手指的距离
int current_lever_distance;
int timebase_move_distance; // 记录手势改变时基时手指移动的距离
int timebase_move_lever;
int current_timebase_lever;
int current_voltdiv_lever;
static int current_selected_channel;//当前选中的通道，在触摸屏上缩放设置电压档位时设置当前选中的通道，选中的通道在通道图标上会有标志以区分其他的通道

int check_result[SELF_CHECK_STEP_NUMBER];
//CString FormatFreq(double freq);
HANDLE m_hCheckThreadProc;//菜单线程

//static DWORD WINAPI CheckThread(LPVOID lParam);//线程函数;
static BOOL running = FALSE;
static BOOL quittest = FALSE;
extern SizeF GetTextBounds(const Font& font, const StringFormat& strFormat, const CString& szText);
extern void DrawRoundRectange(Graphics &g, Color pens, int x, int y, int width, int height);
extern void DrawGroupRectange(Graphics &g, Color pens, int x, int y, int width, int height, CString header, LONG length);
extern void FillRoundRectangle(Graphics &g, Color color, int x, int y, int width, int height);

extern void DrawRoundRectange(Graphics &g, Color pens, int x, int y, int width, int height, int roundwidth);
//extern void DrawGroupRectange(Graphics &g, Color pens, int x, int y, int width, int height, CString header, LONG length);
extern void FillRoundRectangle(Graphics &g, Color color, int x, int y, int width, int height, int roundwidth);
extern  void DrawRoundRectangewithpen(Graphics &g, Color pens, int x, int y, int width, int height, int roundwidth,int penwidth);
HWND targethwnd;
HWND targethwnd_LA;
static BOOL has_another_app_run = FALSE;
static BOOL has_error = FALSE;

static BOOL first_open_voltdiv = FALSE;
static BOOL first_open_timebase = FALSE;
int current_menuitem_index;//当前选中的菜单项在本级菜单中的索引

int click_pos_x, click_pos_y;//鼠标按下时的坐标
int current_pos_x, current_pos_y;
int old_pos_x, old_pos_y;
int down_x, down_y;
int cursor_result_window_width;
int cursor_result_window_height;
int old_cursorresultwindow_pos_x, old_cursorresultwindow_pos_y;

static float float_time = 0.0f;
static float float_time1 = 0.0f;
static float autoset_float_time = 0.0f;
static int editbox_title_id; //全局编辑框的标题字符串ID
static int global_tips_title_id;//提示字符串ID
static BOOL start_calibration = FALSE;
#define D3DX_PI    ((FLOAT)  3.141592654f)
#define D3DX_1BYPI ((FLOAT)  0.318309886f)

#define D3DXToRadian( degree ) ((degree) * (D3DX_PI / 180.0f))
#define D3DXToDegree( radian ) ((radian) * (180.0f / D3DX_PI))

int menuwindowwidth;//菜单窗口宽度
int menuwindowheight;//菜单窗口高度

float fft_menu_scrool_pos;//当前滚动条的位置
float menucurrentpos;

int menu_item_height;
int menuitem_height;
int menuitem_width;
int menuitem_interval;
int menuitem_interval_x;
int menuitem_interval_y;
int menuitem_topmargin;
int first_column_menuitem_left_margin;
int second_column_menuitem_left_margin;

int old_mouse_pos_x, old_mouse_pos_y, old_window_pos_x, old_window_pos_y;
//int topbar_clicked(int x);
int mini_button_hit(int x);
int menu_button_hit(int x);
int close_button_hit(int x);
int update_config_button_hit(int x);
int test_this_step(int x);
int start_check_button_hit(int x);
int single_check_button_hit(int x);
int force_pass_button_hit(int x);
int check_fail_button_hit(int x);


int screen_width, screen_height;
HBRUSH TRANSPARENT_BRUSH;				//透明
HBRUSH		BLACKBRUSH;					//黑色
HBRUSH		WHITEBRUSH;						//白色
HBRUSH		RED_BRUSH;							//红色
HBRUSH		PINK_BRUSH;							//粉红色
HBRUSH		PLUM_RED_BRUSH;					//梅红色
HBRUSH		GREEN_BRUSH;							//绿色
HBRUSH		JADEGREEN_BRUSH;					//浅绿色
HBRUSH		BLUE_BRUSH;							//蓝色
HBRUSH		SKY_BRUSH;							//天蓝色
HBRUSH		LIGHT_BLUE_BRUSH;					//浅蓝色
HBRUSH		YELLOW_BRUSH;						//黄色
HBRUSH		GOLDEN_YELLOW_BRUSH;					//金黄色
HBRUSH		BROWN_BRUSH;							//棕色
HBRUSH		FRENCHGRAY_BRUSH;				//浅灰色
HBRUSH		DEEPGRAY_BRUSH;						//深灰色
HBRUSH		PURPLE_BRUSH;					//紫色
Color colors[10] = { Color(255, 255, 255, 255)/*white*/ , Color(255, 155, 155, 155)/*gray*/, Color(255, 255, 0, 0)/*red*/, Color(255, 0, 255, 0)/*green*/,  Color(255, 0, 0, 255)/*blue*/,Color(255, 0, 255, 255)/*light blue*/, Color(255,255, 255, 0)/*yellow*/,Color(255, 255, 0, 255)/*pink*/,Color(255, 204, 153, 255)/*purple*/,Color(255, 255, 128, 0)/*brown*/ };




int choosesearchdeviceop(int x);
int searchdevice_next_button_hit(int x);
int searchdevice_quit_button_hit(int x);
int choosedevice_tip(int x);

//int old_window_pos_x, old_window_pos_y;
//int old_mouse_pos_x, old_mouse_pos_y;

HWND CreateDropMenuWindow(int x, int y, int width, int height)
{
	HWND hwnd;
	return NULL;
}
/*
enum  window_item_type
{
	Title,//静态文本，不自动换行
	String,//多行文本，可以自动换行
	Button,
	Single_Grid,//单选表格
	Multi_Grid,//多选表格
	Slide_Button,//滑动开关
	Edit_Box,
	Spin,
	Group,
	TopBar,
	Slide,
	Checkbox,
	Radio,
	TEXT,
	DropBox,
	Type_ValueBox,
	Type_KnobButon
};
enum Align_Type
{
	Align_Center,//居中对齐
	Align_Left,	//居左对齐
	Align_Right	//右对齐
};*/
/**********************************************************************************************************************
在该项目的前期每个菜单中的控件都是单独画的，由于为了美观等原因需要调整很多次大小，位置等，由于是自己画，
事件处理也需要我们自己处理，改了位置和大小，事件处理代码中也要同时改动，很麻烦，
所以为了修改和维护的容易，后期才加了这些控件基类，然后只在窗口创建时，添加这些控件，设置好位置大小什么的，
想改位置和大小什么的只用改一处地方，绘图和事件处理相关的代码以后就不用修改了，这是最初的目的，这样改了以后同时就会有其他方面的改动，
每个控件除了位置，大小，当前状态，是否显示等属性外，还有一个重要的属性就是功能函数，是一个函数指针，每个控件都有一个，所以会在工程代码中看到很多process_***_func之类的函数，
就是点击该控件时调用的函数每个控件都有自己的绘图函数和事件处理函数，这些在向菜单窗口添加控件时都设置好，每个菜单项都有一个对应的vector容器，用来存放该菜单中所有的控件项，
后期在菜单的窗口过程函数中根据当前菜单项的索引值，获取到该菜单项对应的控件vector容器，然后在菜单窗口的WM_PAINT绘图事件中逐一调用每个控件的绘图代码，在相应的事件处理函数中逐一的调用
每个控件的事件响应函数，每个控件的event函数的作用是根据鼠标的点击位置来判断当前鼠标点击的是不是自己，如果是，则返回1，代表自己捕获该事件，否则返回0，如果返回1的话这样后续就不用迭代
该容器中其他的控件了，然后就可以调用该控件的功能函数了，比如打开通道，设置doc类或Hard类中的相关变量等
***************************************************************************************************************/
//所有自定义控件的基类，
//视图，就是一个控件容器
struct view;
struct windowitem
{
	int x;//位置信息，是相对于控件所在的窗口客户区左上角的坐标，不是相对于屏幕的坐标，可以查看GetClientRect()和GetWindowRect()的区别
	int y;
	int width;//宽度
	int height;//高度
	COLORREF color;//颜色，colorbutton有用到
	CString owner;//用来区分该控件是哪一项功能的设置项，比如fft,passfail等
	control_type type;
	int title_id;//add 2016/7/9，该控件的title对应在语言文件中的ID
	int step_index;
	CString title;
	BOOL hide;//是否隐藏该控件
	BOOL always_show;//当该项为TRUE时，不管hide为何值，该控件总是显示
	BOOL enabled;//是否使能，不使能时灰显
	int current_state;//当前控件状态，比如滑动开关有开和关两种状态，singlegrid(单选列表)的当前状态就是当前选中的是第几个等
	int(*event_func)(int i);//该控件的功能函数
	int(*update_value)(int x);//该控件的更新当前值函数
	int origin_x;//该控件在窗口中的原始位置
	BOOL ifhit;//是否被点击，鼠标按下时在此控件上该值为TRUE;
	view* subview;
	HWND parent;//该控件的父窗口
	void *userdata;//指向用户自定义的附加数据
	BOOL if_follow_scrool;//是否跟踪滚动，有些控件在判断事件时不需要将滚动的位置信息添加到自己的位置信息中,大部分控件都需要，默认为TRUE,只有少数控件不需要，可以改变此值
	windowitem()
	{
		//ZeroMemory(this, sizeof(windowitem));//dangerous!!
		enabled = TRUE;
		hide = FALSE;
		always_show = FALSE;
		if_follow_scrool = TRUE;
		ifhit = FALSE;
		update_value = NULL;
		step_index = -1;
	}
	virtual ~windowitem()
	{

	}
	virtual int draw(HDC hdc)//控件的绘制函数
	{
		return 1;
	}
	virtual int draw_forward(HDC hdc)//菜单往前滑动时调用该画法
	{
		return 1;
	}
	virtual int draw_backward(HDC hdc)//菜单往后滑动时调用该画法
	{
		return 1;
	}
	virtual int event(int eventtype, int x, int y)//控件的事件捕获函数
	{
		return 0;
	}
	virtual int getdatavalue(int x)//更新当前控件的值，现在没有用到
	{
		return 0;
	}
};
struct  view
{
	vector<windowitem*> *subitemvector;
	view()
	{
		subitemvector = new vector<windowitem*>;
	}
	~view()
	{
		vector<windowitem*>::iterator it;
		for (it = subitemvector->begin(); it != subitemvector->end(); it++)
		{
			if (NULL != *it)
			{
				delete *it;
				*it = NULL;
			}
		}
		subitemvector->clear();
	}
};
stack<view*> setting_menu_view_stack;
stack<view*> autoset_menu_view_stack;
view* nextview;
view* oldview;
view* autoset_nextview;
view* autoset_oldview;
windowitem* currenteditwindowitem;//当前占用全局编辑窗口编辑的控件
vector<windowitem *> toolsubitems;
								  //辅助函数，获取一个点在二维XY坐标系中的角度，参数origin为原点坐标
float GetDegreeFromPoint(POINT pos, POINT origin)
{
	float c = sqrt((float)((pos.x - origin.x)*(pos.x - origin.x) + (origin.y - pos.y)*(origin.y - pos.y)));
	float sina = ((float)(origin.y - pos.y)) / c;//正弦

	float radian = (float)asin(sina);//弧度
	float degree = D3DXToDegree(radian);
	float newdegree = degree;

	if (pos.x >= origin.x)//在第一象限和第四象限
	{
		degree = 180.0f - degree;
	}
	else if (pos.x <= origin.x && pos.y >= origin.y)//在第三象限
	{
		degree = 360.0f + degree;
	}
	return degree;
}
struct ImageButton :windowitem
{
	CString buttonimage;
	int image_x;//由于图片需要从一张大图片中截取显示一部分，该属性为截取的位置
	int image_y;
	int image_width;
	int image_height;
	ImageButton()
	{

	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);

			Image knobimage(buttonimage);
			//	Image image_title_base
			g.DrawImage(&knobimage, x, y, image_x, image_y, image_width, image_height, UnitPixel);
		}
		else
		{

		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		return 0;
	}
	int draw_backward(HDC hdc)
	{
		return 0;
	}
	int event(int eventtype, int x, int y)
	{
		//if (can_menurool == FALSE)
		{
			RECT rect;
			GetWindowRect(ghwnd, &rect);
			if (EVENT_LBUTTON_UP == eventtype)
			{
				if (this->enabled == TRUE)
				{
					if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y /*+ fft_menu_scrool_pos*/&& y <= this->y + this->height /*+ fft_menu_scrool_pos*/)
					{
						if (this->current_state == 1)
						{
							this->current_state = 0;
						}
						else
						{
							this->current_state = 1;
						}
						return 1;
					}
				}
			}
			else
			{
				return 0;
			}
		}
		return 0;
	}
};
struct KnobButton :windowitem
{
	CString buttonimage;//旋钮图片文件名
	float  threshold; //旋钮旋转角度的阈值，旋转多少度识别为旋转
	HWND targethwnd;//与该旋钮控件关联的需要设置值得控件
					//	windowitem* targetwindowitem;
	BOOL firsthit;
	POINT firsthitpoint;
	float step;//旋钮旋转一次改变的值，正向旋转加该值，反向旋转减该值
	float start_degree;//触摸开始时的角度
	float current_degree;//触摸过程中当前的角度，减去开始时的角度用来与阈值比较，超过阈值就触发旋转事件
	float display_degree;//圆盘的旋转角度，显示用。
	float last_degree;//上一次的角度，用来计算新的旋转角度
	float min_value;
	float max_value;
	int value_type;//0表示float，1表示int
	KnobButton()
	{
		CString apppath = GetAppPath();
		buttonimage = apppath + _T("\\Resource\\knob.png");
		threshold = 10;
		firsthit = FALSE;
		value_type = 0;
		min_value = 0.0f;
		max_value = 9999999999.0f;
		display_degree = last_degree = 0.0;
	}

	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			float center_x = float(x + width / 2);
			float center_y = float(y + height / 2);
			Gdiplus::PointF P(center_x, center_y);  // 旋转中心
			Gdiplus::Matrix matrix;
			matrix.RotateAt(display_degree, P);
			g.SetTransform(&matrix);
			Image knobimage(buttonimage);
			//	Image image_title_base
			g.DrawImage(&knobimage, x, y, width, height);
		}
		else
		{

		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		return 0;
	}
	int draw_backward(HDC hdc)
	{
		return 0;
	}
	int event(int eventtype, int xpos, int ypos)//控件的事件捕获函数
	{
		int circle_center_x = x + width / 2;
		int circle_center_y = y + height / 2;
		int radiu = width / 2;
		POINT origin = { circle_center_x ,circle_center_y };
		if (eventtype == EVENT_MOUSEMOVE)
		{
			if (xpos > x && xpos < x + width && ypos > y && ypos < y + height)
			{
				if (firsthit == FALSE)
				{
					firsthit = TRUE;
					firsthitpoint.x = xpos;
					firsthitpoint.y = ypos;
					start_degree = GetDegreeFromPoint(firsthitpoint, origin);
					last_degree = start_degree;
				}
				POINT pt;
				pt.x = xpos;
				pt.y = ypos;

				current_degree = GetDegreeFromPoint(pt, origin);
				float diff_degree = current_degree - start_degree;

				float last_diff = current_degree - last_degree;
				display_degree += last_diff;
				if (abs(diff_degree) > threshold)//旋转角度大于阈值，触发旋转动作，这里简单的将targethwnd的内容减去或加上step
				{
					start_degree = current_degree;

				}
				InvalidateRect(parent, NULL, FALSE);
				last_degree = current_degree;
			}
		}
		else if (eventtype == EVENT_LBUTTON_UP)
		{
			//start_degree = current_degree = 0;
			firsthit = FALSE;
		}
		return 0;
	}
};
struct EditBox :windowitem //文字输入框
{
	CString content;//标题内容
	int font_size;//绘制标题文字时用的字体大小
	HWND hwnd;//系统控件edit的窗口句柄
	HWND backwnd;//在平板上会出现菜单窗口覆盖住edit控件的情况，所以再加个窗口作为edit控件的父窗口
	int editbox_x;
	int editbox_y;
	int editbox_width;
	int editbox_height;
	int editbox_fontsize;
	BOOL ifshow_box;
	EditBox(int x, int y, int width, int height, CString neirong, int editfontsize = 36, BOOL showbox = FALSE, BOOL enable = TRUE) :editbox_x(x), editbox_y(y), editbox_width(width), editbox_height(height), editbox_fontsize(editfontsize), ifshow_box(showbox), content(neirong)
	{
		
		if (!backwnd)
		{
			return;
		}
		ShowWindow(backwnd, TRUE);
		UpdateWindow(backwnd);
		SetLayeredWindowAttributes(backwnd, 0, 0, LWA_ALPHA);
		POINT pt = { 20,0 };
		ClientToScreen(backwnd, &pt);
		HWND tmp = CreateWindow(L"static", L"", WS_VISIBLE | WS_POPUP | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT | DT_VCENTER, -100, -100, 1, 1, backwnd, NULL, NULL, NULL);
		if (!tmp)
		{
			return;
		}
		ShowWindow(tmp, TRUE);
		UpdateWindow(tmp);
		hwnd = CreateWindow(L"edit", L"", WS_VISIBLE | WS_POPUP | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT | DT_VCENTER, pt.x, pt.y, editbox_width, editbox_height, backwnd, NULL, NULL, NULL);
		if (!hwnd)
		{
			return;
		}
		ShowWindow(hwnd, TRUE);
		UpdateWindow(hwnd);
		SetWindowPos(hwnd, NULL, editbox_x, editbox_y + 5, editbox_width, editbox_height, SWP_NOSIZE);
		//edit控件默认的字体太小，设置大一点
		LOGFONT LogFont;
		ZeroMemory(&LogFont, sizeof(LogFont));
		lstrcpy(LogFont.lfFaceName, _T("黑体"));
		LogFont.lfHeight = editbox_fontsize;
		HFONT m_hFont = CreateFontIndirect(&LogFont);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)m_hFont, TRUE);
		SetWindowText(hwnd, content);
	}
	~EditBox()
	{
		DestroyWindow(hwnd);
		hwnd = NULL;
		DestroyWindow(backwnd);
		backwnd = NULL;
	}
	void ReStoreWindow()
	{
		
		if (!backwnd)
		{
			return;
		}
		UpdateWindow(backwnd);
		SetLayeredWindowAttributes(backwnd, 0, 0, LWA_ALPHA);
		ShowWindow(backwnd, TRUE);
		POINT pt = { 0,0 };
		ClientToScreen(backwnd, &pt);
		hwnd = CreateWindow(L"edit", L"", WS_VISIBLE | WS_POPUP | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT | DT_VCENTER, pt.x, pt.y, editbox_width, editbox_height, backwnd, NULL, NULL, NULL);
		if (!hwnd)
		{
			return;
		}
		UpdateWindow(hwnd);
		SetWindowPos(hwnd, NULL, editbox_x, editbox_y, editbox_width, editbox_height, SWP_NOSIZE);
		ShowWindow(hwnd, TRUE);
		//edit控件默认的字体太小，设置大一点
		LOGFONT LogFont;
		ZeroMemory(&LogFont, sizeof(LogFont));
		lstrcpy(LogFont.lfFaceName, _T("黑体"));
		LogFont.lfHeight = editbox_fontsize;
		HFONT m_hFont = CreateFontIndirect(&LogFont);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)m_hFont, TRUE);
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			ShowWindow(backwnd, TRUE);
			ShowWindow(hwnd, TRUE);

			RECT rect;
			GetWindowRect(ghwnd, &rect);
			//SetWindowPos(menuhwnd, NULL, rect.right - menuwindowwidth /*- m_pView->m_nMarginRight*/, m_pView->m_rcGrid.top, 0, 0, SWP_NOSIZE);

			Graphics g(hdc);
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			if (ifshow_box)
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), first_column_menuitem_left_margin/* - menucurrentpos*/, this->y - 15/* + fft_menu_scrool_pos*/, this->width - 25, this->height);
			}
			if (enabled)
			{
				//FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			else
			{
				//FillRoundRectangle(g, Color(255, 155, 155, 155), first_column_menuitem_left_margin + 5, this->y + fft_menu_scrool_pos, this->width - 20, this->height, 0);
			}
		}
		else
		{
			ShowWindow(backwnd, FALSE);
			ShowWindow(hwnd, FALSE);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			ShowWindow(backwnd, FALSE);
			ShowWindow(hwnd, FALSE);
		}
		else
		{
			ShowWindow(backwnd, FALSE);
			ShowWindow(hwnd, FALSE);
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			ShowWindow(backwnd, FALSE);
			ShowWindow(hwnd, FALSE);
			//SetWindowPos(hwnd, NULL, editbox_x + menucurrentpos, editbox_y, editbox_width, editbox_height, SWP_NOSIZE);
		}
		else
		{
			ShowWindow(backwnd, FALSE);
			ShowWindow(hwnd, FALSE);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		//if (can_menurool == FALSE)
		{
			RECT rect;
			GetWindowRect(ghwnd, &rect);
			//SetWindowPos(menuhwnd, NULL, rect.right - menuwindowwidth /*- m_pView->m_nMarginRight*/, m_pView->m_rcGrid.top, 0, 0, SWP_NOSIZE);
			if (EVENT_LBUTTON_UP == eventtype)
			{
				if (this->enabled == TRUE)
				{
					if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y /*+ fft_menu_scrool_pos*/&& y <= this->y + this->height /*+ fft_menu_scrool_pos*/)
					{
						if (this->current_state == 1)
						{
							this->current_state = 0;
						}
						else
						{
							this->current_state = 1;
						}
						return 1;
					}
				}
			}
			else
			{
				return 0;
			}
		}
		return 0;
	}
};


struct ValueBox :windowitem//
{
	int drop_width;
	int drop_height;
	COLORREF value_color;
	int font_size;
	int value_font_size;
	CString value;
	ValueBox() :windowitem()
	{
		value_font_size = 30;
	}
	~ValueBox()
	{

	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			//if (can_menurool == FALSE)
			{
				Graphics g(hdc);
				SolidBrush brush(Color(255, 255, 255, 255));
				g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
				FontFamily fontFamily(L"宋体");
				if (this->if_follow_scrool == TRUE)
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
					FillRoundRectangle(g, Color(255, 51, 102, 205), this->x , this->y + fft_menu_scrool_pos, this->width - 10 - this->width / 2, this->height);
					FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + 10, this->y + fft_menu_scrool_pos, this->width - 15 - this->width / 2, this->height, 0);

					if (enabled)
					{
						//FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
					}
					else
					{
						FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + this->width / 2 - 5, this->y + fft_menu_scrool_pos, this->width - 20 - this->width / 2, this->height, 0);
					}

					Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
					Gdiplus::Font font3(&fontFamily, value_font_size, FontStyleBold, UnitPixel);
					SizeF t;
					StringFormat stringformat;
					t = GetTextBounds(font2, &stringformat, this->title);
					int w = (this->width / 2 - 10 - t.Width) / 2;
					int h = (this->height - t.Height) / 2 - 5;
					if (w > 10)
					{
						w = 10;
					}
					Gdiplus::PointF point0(this->x + w, this->y + h + fft_menu_scrool_pos);
					CString newstring = this->title;
					g.DrawString(newstring, -1, &font2, point0, &brush);

					int content_width = this->width - 20 - this->width / 2;
					t = GetTextBounds(font3, &stringformat, value);
					w = (content_width - t.Width) / 2;
					Gdiplus::PointF point1(this->x + this->width / 2 + w - 12, this->y + h + fft_menu_scrool_pos);
					g.DrawString(value, -1, &font3, point1, &brush);
					if (enabled)
					{
						//FillRoundRectangle(g, Color(255, 50, 50, 50), this->x + this->width - 50/*- menucurrentpos*/, this->y + 5 + fft_menu_scrool_pos, 23, this->height - 7);
					}
					else
					{
						//FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + this->width - 50/*- menucurrentpos*/, this->y + 5 + fft_menu_scrool_pos, 23, this->height - 7);
					}
				}
				else
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y, this->width - 25, this->height);
					FillRoundRectangle(g, Color(255, 51, 102, 205), this->x , this->y, this->width - 10 - this->width / 2, this->height);
					FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + 10, this->y, this->width - 15 - this->width / 2, this->height, 0);
					if (enabled)
					{
						//FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
					}
					else
					{
						FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + this->width / 2 - 5, this->y, this->width - 20 - this->width / 2, this->height, 0);
					}

					Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
					Gdiplus::Font font3(&fontFamily, value_font_size, FontStyleBold, UnitPixel);
					SizeF t;
					StringFormat stringformat;
					t = GetTextBounds(font2, &stringformat, this->title);
					int w = (this->width / 2 - 10 - t.Width) / 2;
					int h = (this->height - t.Height) / 2 - 5;
					if (w > 10)
					{
						w = 10;
					}
					Gdiplus::PointF point0(this->x + w, this->y + h);
					CString newstring = this->title;
					g.DrawString(newstring, -1, &font2, point0, &brush);

					int content_width = this->width - 20 - this->width / 2;
					t = GetTextBounds(font3, &stringformat, value);
					w = (content_width - t.Width) / 2;
					Gdiplus::PointF point1(this->x + this->width / 2 - 12 + w, this->y + h);
					g.DrawString(value, -1, &font3, point1, &brush);
					if (enabled)
					{
						//FillRoundRectangle(g, Color(255, 50, 50, 50), this->x + this->width - 50, this->y + 5, 23, this->height - 7);
					}
					else
					{
						//FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + this->width - 50, this->y + 5, 23, this->height - 7);
					}
				}
			}
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y , this->width - 25, this->height);
			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y, this->width - 10 - this->width / 2, this->height);
			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + 10 + menucurrentpos, this->y , this->width - 15 - this->width / 2, this->height, 0);

			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::Font font3(&fontFamily, value_font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = (this->width / 2 - 10 - t.Width) / 2;
			int h = (this->height - t.Height) / 2 - 5;
			if (w > 10)
			{
				w = 10;
			}
			Gdiplus::PointF point0(this->x + w + menucurrentpos, this->y + h );
			CString newstring = this->title;
			g.DrawString(newstring, -1, &font2, point0, &brush);

			int content_width = this->width / 2 - 62;
			t = GetTextBounds(font2, &stringformat, value);
			w = (content_width - t.Width) / 2;
			Gdiplus::PointF point1(this->x + this->width / 2 + w + menucurrentpos, this->y + h);
			//m_Lan.GetValue(drop_items.at(this->current_state));
			g.DrawString(value, -1, &font2, point1, &brush);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y , this->width - 25, this->height);
			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y, this->width - 10 - this->width / 2, this->height);
			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + 10 - menucurrentpos, this->y, this->width - 15 - this->width / 2, this->height, 0);
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::Font font3(&fontFamily, value_font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = (this->width / 2 - 10 - t.Width) / 2;
			int h = (this->height - t.Height) / 2 - 5;
			if (w > 10)
			{
				w = 10;
			}
			Gdiplus::PointF point0(this->x + w - menucurrentpos, this->y + h);
			CString newstring = this->title;
			g.DrawString(newstring, -1, &font2, point0, &brush);

			int content_width = this->width / 2 - 62;
			t = GetTextBounds(font2, &stringformat, value);
			w = (content_width - t.Width) / 2;
			Gdiplus::PointF point1(this->x + this->width / 2 + w - menucurrentpos, this->y + h);
			//	m_Lan.GetValue(drop_items.at(this->current_state));
			g.DrawString(value, -1, &font2, point1, &brush);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		//if (can_menurool == FALSE)
		{
			if (EVENT_LBUTTON_DOWN == eventtype)
			{
				if (enabled)
				{
					if (x >= this->x + this->width / 2 && x <= this->x + this->width && y >= this->y && y <= this->y + this->height)
					{
						ifhit = TRUE;
						return 0;
					}
				}
			}
			else
				if (EVENT_LBUTTON_UP == eventtype)
				{
					if (enabled && ifhit)
					{
						if (x >= this->x + this->width / 2 && x <= this->x + this->width && y >= this->y && y <= this->y + this->height)
						{
							ifhit = FALSE;
							return 1;
						}
					}
				}
		}
		return 0;
	}
};

struct checkbox :windowitem//复选框
{
	CString content;//标题内容
	int font_size;//绘制标题文字时用的字体大小
	int box_width;
	int box_height;
	checkbox(int size = 28) :windowitem()
	{
		content = L"";
		font_size = size;
		always_show = FALSE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			stringformat.SetFormatFlags(StringFormatFlagsNoClip);
			SolidBrush brush(Color(255, 255, 255, 255));
			Brush *brush1 = new SolidBrush(Color(255, 255, 0, 0));
			//g.FillRectangle(brush1, rect.right - 70, rect.top + 10, 60, 50);//画方形
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x, this->y + fft_menu_scrool_pos);
			Gdiplus::Pen pen1(Color(255, 0, 255, 0));
			Gdiplus::Pen pen2(Color(255, 155, 155, 155));
			Gdiplus::RectF rect0(this->x, this->y, this->box_width, this->box_height);

			if (this->enabled)
			{
				g.DrawRectangle(&pen1, rect0);
			}
			else
			{
				g.DrawRectangle(&pen2, rect0);
			}

			if (this->current_state == 1)
			{
				g.FillRectangle(brush1, this->x + 2, this->y + 2, this->box_width - 2, this->box_height - 3);
			}
			Gdiplus::RectF rect(this->x + this->box_width + 2, this->y + 12, this->width, this->height);
			g.DrawString(this->title, -1, &font1, rect, &stringformat, &brush);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			stringformat.SetFormatFlags(StringFormatFlagsNoClip);
			SolidBrush brush(Color(255, 255, 255, 255));
			Brush *brush1 = new SolidBrush(Color(255, 255, 0, 0));
			//g.FillRectangle(brush1, rect.right - 70, rect.top + 10, 60, 50);//画方形
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x, this->y + fft_menu_scrool_pos);
			Gdiplus::Pen pen1(Color(255, 0, 255, 0));
			Gdiplus::RectF rect0(this->x - (int)menucurrentpos, this->y, this->box_width, this->box_height);
			g.DrawRectangle(&pen1, rect0);
			if (this->current_state == 1)
			{
				g.FillRectangle(brush1, this->x + 2 - (int)menucurrentpos, this->y + 2, this->box_width - 2, this->box_height - 3);
			}
			Gdiplus::RectF rect(this->x + this->box_width + 2 - menucurrentpos, this->y + 12, this->width, this->height);
			g.DrawString(this->title, -1, &font1, rect, &stringformat, &brush);
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			stringformat.SetFormatFlags(StringFormatFlagsNoClip);
			SolidBrush brush(Color(255, 255, 255, 255));
			Brush *brush1 = new SolidBrush(Color(255, 255, 0, 0));
			//g.FillRectangle(brush1, rect.right - 70, rect.top + 10, 60, 50);//画方形
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x, this->y + fft_menu_scrool_pos);
			Gdiplus::Pen pen1(Color(255, 0, 255, 0));
			Gdiplus::RectF rect0(this->x + menucurrentpos, this->y, this->box_width, this->box_height);
			g.DrawRectangle(&pen1, rect0);
			if (this->current_state == 1)
			{
				g.FillRectangle(brush1, this->x + 2 + (int)menucurrentpos, this->y + 12, this->box_width - 2, this->box_height - 3);
			}
			Gdiplus::RectF rect(this->x + this->box_width + 2 + menucurrentpos, this->y + 12, this->width, this->height);
			g.DrawString(this->title, -1, &font1, rect, &stringformat, &brush);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		//if (can_menurool == FALSE)
		{
			if (EVENT_LBUTTON_UP == eventtype)
			{
				if (this->enabled == TRUE)
				{
					if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y /*+ fft_menu_scrool_pos*/&& y <= this->y + this->height /*+ fft_menu_scrool_pos*/)
					{
						if (this->current_state == 1)
						{
							this->current_state = 0;
						}
						else
						{
							this->current_state = 1;
						}
						return 1;
					}
				}
			}
			else
			{
				return 0;
			}
		}
		return 0;
	}
};
struct title : windowitem//问题标题
{
	CString content;//标题内容
	int font_size;//绘制标题文字时用的字体大小
	title(int size = 28) :windowitem()
	{
		content = L"";
		font_size = size;
		always_show = FALSE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			stringformat.SetFormatFlags(StringFormatFlagsNoClip);
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x, this->y + fft_menu_scrool_pos);
			Gdiplus::RectF rect(this->x, this->y, this->width, this->height);
			//g.DrawString(content, -1, &font1, point1, &brush);
			g.DrawString(this->content, -1, &font1, rect, &stringformat, &brush);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x - menucurrentpos, this->y + fft_menu_scrool_pos);
			g.DrawString(this->content, -1, &font1, point1, &brush);
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x + menucurrentpos/*- menucurrentpos*/, this->y + fft_menu_scrool_pos);
			g.DrawString(this->content, -1, &font1, point1, &brush);
		}
		return 1;
	}
};
struct title_string : windowitem//问题标题
{
	CString content;//标题内容
	int font_size;//绘制标题文字时用的字体大小
	title_string(int size = 28, COLORREF c = RGB(255, 255, 255)) :windowitem()
	{
		content = L"";
		font_size = size;
		always_show = FALSE;
		color = c;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			stringformat.SetFormatFlags(StringFormatFlagsNoClip);
			SolidBrush brush(Color(255, GetRValue(color), GetGValue(color), GetBValue(color)));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x, this->y + fft_menu_scrool_pos);
			Gdiplus::RectF rect(this->x, this->y, this->width, this->height);
			//g.DrawString(content, -1, &font1, point1, &brush);
			g.DrawString(content, -1, &font1, rect, &stringformat, &brush);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, GetRValue(color), GetGValue(color), GetBValue(color)));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x - menucurrentpos, this->y + fft_menu_scrool_pos);
			g.DrawString(content, -1, &font1, point1, &brush);
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, GetRValue(color), GetGValue(color), GetBValue(color)));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x + menucurrentpos/*- menucurrentpos*/, this->y + fft_menu_scrool_pos);
			g.DrawString(content, -1, &font1, point1, &brush);
		}
		return 1;
	}
};

struct Text : windowitem//问题标题
{
	CString content;//标题内容
	int font_size;//绘制标题文字时用的字体大小
	Text(int size = 28) :windowitem()
	{
		content = L"";
		font_size = size;
		always_show = FALSE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			stringformat.SetFormatFlags(StringFormatFlagsNoClip);
			SolidBrush brush(Color(255, GetRValue(color), GetGValue(color), GetBValue(color)));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x, this->y + fft_menu_scrool_pos);
			Gdiplus::RectF rect(this->x, this->y, this->width, this->height);
			g.DrawString(content, -1, &font1, rect, &stringformat, &brush);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, GetRValue(color), GetGValue(color), GetBValue(color)));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x - menucurrentpos, this->y + fft_menu_scrool_pos);
			g.DrawString(content, -1, &font1, point1, &brush);
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, GetRValue(color), GetGValue(color), GetBValue(color)));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font1(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::PointF point1(this->x + menucurrentpos/*- menucurrentpos*/, this->y + fft_menu_scrool_pos);
			g.DrawString(content, -1, &font1, point1, &brush);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (EVENT_LBUTTON_UP == eventtype)
		{
			if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y /*+ fft_menu_scrool_pos*/&& y <= this->y + this->height /*+ fft_menu_scrool_pos*/)
			{
				return 1;
			}
		}
		return 0;
	}
};
struct viewtopbar :windowitem//view 顶部按钮
{
	CString title;
	CString parent_title;
	viewtopbar(int columnwidth = 200, int columnheight = 80) :windowitem()
	{
		width = columnwidth;
		height = columnheight;
		always_show = TRUE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			//if (can_menurool == FALSE)
			{
				Graphics g(hdc);
				SolidBrush brush(Color(255, 255, 255, 255));
				g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
				FontFamily fontFamily(L"宋体");
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x/* - menucurrentpos*/, this->y/* + fft_menu_scrool_pos*/, this->width - 25, this->height);
				FillRoundRectangle(g, Color(255, GetRValue(color), GetGValue(color), GetBValue(color)), this->x /*- menucurrentpos*/, this->y /*+ fft_menu_scrool_pos*/, this->width - 25, this->height);

				SizeF t;
				StringFormat stringformat;
				int font_size = 30;
				for (; font_size >= 20;)
				{
					Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
					SizeF t;
					t = GetTextBounds(font2, &stringformat, this->title);
					if (t.Width > this->width - 90)
					{
						font_size = font_size - 2;
					}
					else
					{
						break;
					}
				}
				Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
				t = GetTextBounds(font2, &stringformat, this->title);
				int w = this->width - t.Width;
				int h = (this->height - t.Height) / 2 - 5;
				Gdiplus::PointF point0(this->x + w / 2 - 15 /*- menucurrentpos*/, this->y + h/* + fft_menu_scrool_pos*/);
				g.DrawString(this->title, -1, &font2, point0, &brush);

				Gdiplus::PointF point1(this->x + 15 /*- menucurrentpos*/, this->y + h /*+ fft_menu_scrool_pos*/);
				g.DrawString(parent_title, -1, &font2, point1, &brush);
			}
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y /*+ fft_menu_scrool_pos*/, this->width - 25, this->height);
			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y /*+ fft_menu_scrool_pos*/, this->width - 25, this->height);
			SizeF t;
			int font_size = 30;
			for (; font_size >= 20;)
			{
				Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
				SizeF t;
				t = GetTextBounds(font2, &stringformat,this->title);
				if (t.Width > this->width - 90)
				{
					font_size = font_size - 2;
				}
				else
				{
					break;
				}
			}
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);

			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - t.Width;
			int h = (this->height - t.Height) / 2 - 5;
			Gdiplus::PointF point0(this->x + w / 2 - 15 + menucurrentpos, this->y + h /*+ fft_menu_scrool_pos*/);
			g.DrawString(this->title, -1, &font2, point0, &brush);

			Gdiplus::PointF point1(this->x + 15 + menucurrentpos, this->y + h /*+ fft_menu_scrool_pos*/);
			g.DrawString(parent_title, -1, &font2, point1, &brush);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y /*+ fft_menu_scrool_pos*/, this->width - 25, this->height);
			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y /*+ fft_menu_scrool_pos*/, this->width - 25, this->height);
			SizeF t;

			int font_size = 30;
			for (; font_size >= 20;)
			{
				Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
				SizeF t;
				t = GetTextBounds(font2, &stringformat, this->title);
				if (t.Width > this->width - 90)
				{
					font_size = font_size - 2;
				}
				else
				{
					break;
				}
			}
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);

			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - t.Width;
			int h = (this->height - t.Height) / 2 - 5;
			Gdiplus::PointF point0(this->x + w / 2 - 15 - menucurrentpos, this->y + h /*+ fft_menu_scrool_pos*/);
			g.DrawString(this->title, -1, &font2, point0, &brush);

			Gdiplus::PointF point1(this->x + 15 - menucurrentpos, this->y + h /*+ fft_menu_scrool_pos*/);
			g.DrawString(parent_title, -1, &font2, point1, &brush);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		//if (can_menurool == FALSE)
		{
			if (EVENT_LBUTTON_UP == eventtype)
			{
				if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y /*+ fft_menu_scrool_pos*/&& y <= this->y + this->height /*+ fft_menu_scrool_pos*/)
				{
					return 1;
				}
			}
		}
		return 0;
	}
};

struct viewtopbar_dropdown :windowitem//view 顶部按钮
{
	CString title;
	CString parent_title;
	viewtopbar_dropdown(int columnwidth = 200, int columnheight = 80) :windowitem()
	{
		width = columnwidth;
		height = columnheight;
		always_show = TRUE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			//if (can_menurool == FALSE)
			{
				Graphics g(hdc);
				SolidBrush brush(Color(255, 255, 255, 255));
				g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
				FontFamily fontFamily(L"宋体");
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x/* - menucurrentpos*/, this->y/* + fft_menu_scrool_pos*/, this->width - 25, this->height);
				FillRoundRectangle(g, Color(255, 51, 102, 205), this->x /*- menucurrentpos*/, this->y /*+ fft_menu_scrool_pos*/, this->width - 25, this->height);

				Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);
				SizeF t;
				StringFormat stringformat;
				t = GetTextBounds(font2, &stringformat, this->title);
				int w = this->width - t.Width;
				Gdiplus::PointF point0(this->x + w / 2 - 15 /*- menucurrentpos*/, this->y + 15/* + fft_menu_scrool_pos*/);
				g.DrawString(this->title, -1, &font2, point0, &brush);

				Gdiplus::PointF point1(this->x + 15 /*- menucurrentpos*/, this->y + 15 /*+ fft_menu_scrool_pos*/);
				g.DrawString(parent_title, -1, &font2, point1, &brush);
			}
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y /*+ fft_menu_scrool_pos*/, this->width - 25, this->height);
			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y /*+ fft_menu_scrool_pos*/, this->width - 25, this->height);

			Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - t.Width;
			Gdiplus::PointF point0(this->x + w / 2 - 15 + menucurrentpos, this->y + 15 /*+ fft_menu_scrool_pos*/);
			g.DrawString(this->title, -1, &font2, point0, &brush);

			Gdiplus::PointF point1(this->x + 15 + menucurrentpos, this->y + 15 /*+ fft_menu_scrool_pos*/);
			g.DrawString(parent_title, -1, &font2, point1, &brush);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y /*+ fft_menu_scrool_pos*/, this->width - 25, this->height);
			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y /*+ fft_menu_scrool_pos*/, this->width - 25, this->height);

			Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - t.Width;
			Gdiplus::PointF point0(this->x + w / 2 - 15 - menucurrentpos, this->y + 15 /*+ fft_menu_scrool_pos*/);
			g.DrawString(this->title, -1, &font2, point0, &brush);

			Gdiplus::PointF point1(this->x + 15 - menucurrentpos, this->y + 15 /*+ fft_menu_scrool_pos*/);
			g.DrawString(parent_title, -1, &font2, point1, &brush);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		//if (can_menurool == FALSE)
		{
			if (EVENT_LBUTTON_UP == eventtype)
			{
				if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y /*+ fft_menu_scrool_pos*/&& y <= this->y + this->height /*+ fft_menu_scrool_pos*/)
				{
					return 1;
				}
			}
		}
		return 0;
	}
};

struct button :windowitem//按钮
{
	CString title;
	button(int columnwidth = 200, int columnheight = 80) :windowitem()
	{
		width = columnwidth;
		height = columnheight;
		always_show = FALSE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width, this->height);
			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + fft_menu_scrool_pos, this->width, this->height);

			Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - t.Width;
			int h = (this->height - t.Height) / 2;
			Gdiplus::PointF point0(this->x + w / 2 + 5, this->y + h + fft_menu_scrool_pos);
			g.DrawString(this->title, -1, &font2, point0, &brush);
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width, this->height);
			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width, this->height);

			Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - t.Width;
			int h = (this->height - t.Height) / 2;
			Gdiplus::PointF point0(this->x + w / 2 + 5 + menucurrentpos, this->y + h + fft_menu_scrool_pos);
			g.DrawString(this->title, -1, &font2, point0, &brush);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width, this->height);
			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width, this->height);

			Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - t.Width;
			int h = (this->height - t.Height) / 2;
			Gdiplus::PointF point0(this->x + w / 2 - menucurrentpos + 5, this->y + h + fft_menu_scrool_pos);
			g.DrawString(this->title, -1, &font2, point0, &brush);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (EVENT_LBUTTON_UP == eventtype)
		{
			if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + fft_menu_scrool_pos&& y <= this->y + this->height + fft_menu_scrool_pos)
			{
				return 1;
			}
		}
		return 0;
	}
};

struct colorbutton :windowitem//按钮
{
	CString title;
	int font_size;
	colorbutton(int columnwidth = 200, int columnheight = 80) :windowitem()
	{
		width = columnwidth;
		height = columnheight;
		font_size = 25;
		always_show = FALSE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			if (this->if_follow_scrool == TRUE)
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
				if (enabled)
				{
					FillRoundRectangle(g, Color(255, GetRValue(color), GetGValue(color), GetBValue(color)), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height,0);
				}
				else
				{
					FillRoundRectangle(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height,0);
				}
				Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
				SizeF t;
				t = GetTextBounds(font2, &stringformat, this->title);
				int w = this->width - 25 - t.Width;
				int h = (this->height - t.Height) / 2;
				Gdiplus::PointF point0(this->x + w / 2 - 5, this->y + h + fft_menu_scrool_pos - 5);
				g.DrawString(this->title, -1, &font2, point0, &brush);
			}
			else
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y, this->width - 25, this->height,0);
				if (enabled)
				{
					FillRoundRectangle(g, Color(255, GetRValue(color), GetGValue(color), GetBValue(color)), this->x, this->y, this->width - 25, this->height,0);
				}
				else
				{
					FillRoundRectangle(g, Color(255, 155, 155, 155), this->x, this->y, this->width - 25, this->height,0);
				}
				Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
				SizeF t;
				t = GetTextBounds(font2, &stringformat, this->title);
				int w = this->width - 25 - t.Width;
				int h = (this->height - t.Height) / 2;
				Gdiplus::PointF point0(this->x + w / 2 - 5, this->y + h - 5);
				g.DrawString(this->title, -1, &font2, point0, &brush);
			}

			if (this->step_index == current_step_index)
			{
				DrawRoundRectangewithpen(g, Color(255, 0, 255, 0), this->x - 10, this->y - 10, this->width - 25 + 20, this->height+20, 1,5);
			}
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			if (enabled)
			{
				FillRoundRectangle(g, Color(255, GetRValue(color), GetGValue(color), GetBValue(color)), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}

			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - 25 - t.Width;
			int h = (this->height - t.Height) / 2;
			Gdiplus::PointF point0(this->x + w / 2 + menucurrentpos - 5, this->y + h + fft_menu_scrool_pos - 5);
			g.DrawString(this->title, -1, &font2, point0, &brush);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			if (enabled)
			{
				FillRoundRectangle(g, Color(255, GetRValue(color), GetGValue(color), GetBValue(color)), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}

			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - 25 - t.Width;
			int h = (this->height - t.Height) / 2;
			Gdiplus::PointF point0(this->x + w / 2 - menucurrentpos - 5, this->y + h + fft_menu_scrool_pos - 5);
			g.DrawString(this->title, -1, &font2, point0, &brush);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (this->enabled == TRUE)
		{
			if (EVENT_LBUTTON_UP == eventtype)
			{
				if (this->if_follow_scrool == TRUE)
				{
					if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + fft_menu_scrool_pos&& y <= this->y + this->height + fft_menu_scrool_pos)
					{
						return 1;
					}
				}
				else
				{
					if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y && y <= this->y + this->height)
					{
						return 1;
					}
				}
			}
		}
		return 0;
	}
};
struct menuitemmulti :windowitem//多选菜单
{
	int item_count;
	vector<int> items;
	int(*process_func)(int i);//判断选中的子集
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);

			vector<int>::iterator it;
			int i = 0;
			for (it = items.begin(); it != items.end(); it++)
			{
				if (process_func(i) != 0)
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + (menuitem_height - 10 + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, menuitem_height - 10);
					FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + (menuitem_height - 10 + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, menuitem_height - 10);
				}
				else
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + (menuitem_height - 10 + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, menuitem_height - 10);
				}
				Gdiplus::PointF point0(this->x + 15, this->y + 15 + i * (menuitem_height - 10 + menuitem_interval) + fft_menu_scrool_pos);
			//	g.DrawString(*(it), -1, &font2, point0, &brush);
				i++;
			}
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);

			vector<int>::iterator it;
			vector<CString>::iterator result;

			int i = 0;
			for (it = items.begin(); it != items.end(); it++)
			{
				if (process_func(i) != 0)
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + (menuitem_height - 10 + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, menuitem_height - 10);
					FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y + (menuitem_height - 10 + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, menuitem_height - 10);
				}
				else
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + (menuitem_height - 10 + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, menuitem_height - 10);
				}
				Gdiplus::PointF point0(this->x + 15 + menucurrentpos, this->y + 15 + (menuitem_height - 10 + menuitem_interval)*i + fft_menu_scrool_pos);
				//g.DrawString(m_Lan.GetValue(*(it)), -1, &font2, point0, &brush);
				i++;
			}
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);

			vector<int>::iterator it;
			int i = 0;
			for (it = items.begin(); it != items.end(); it++)
			{
				if (process_func(i) != 0)
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + (menuitem_height - 10 + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, menuitem_height - 10);
					FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y + (menuitem_height - 10 + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, menuitem_height - 10);
				}
				else
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + (menuitem_height - 10 + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, menuitem_height - 10);
				}
				Gdiplus::PointF point0(this->x + 15 - menucurrentpos, this->y + 15 + (menuitem_height - 10 + menuitem_interval)*i + fft_menu_scrool_pos);
				//g.DrawString(m_Lan.GetValue(*(it)), -1, &font2, point0, &brush);
				i++;
			}
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (EVENT_LBUTTON_UP == eventtype)
		{
			if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + fft_menu_scrool_pos&& y <= this->y + this->height + fft_menu_scrool_pos)
			{
				if (this->enabled == TRUE)
				{
					for (int i = 0; i < this->item_count; i++)
					{
						if (y >= this->y + fft_menu_scrool_pos + i*(menuitem_height - 10 + menuitem_interval) && y <= this->y + fft_menu_scrool_pos + i*(menuitem_height - 10 + menuitem_interval) + menuitem_height - 10)
						{
							this->current_state = i;
							return 1;
						}
					}
				}
				else
				{
					return 0;
				}
			}
		}
		return 0;
	}
};
typedef int(*pFunc)(int);//定义函数别名才能放在vector中

struct menuitemradio :windowitem//单选菜单
{
	int item_count;
	//vector<CString> items;
	vector<int> items;
	vector<int> items_type;
	vector<pFunc> items_func;
	int font_size;//绘制文字时用的字体大小
	int item_height;
	menuitemradio(int fontsize = 30, int itemheight = menuitem_height - 10) :windowitem()
	{
		font_size = fontsize;
		item_height = itemheight;
		items.clear();
	}
	~menuitemradio()
	{
		items.clear();
		//OutputDebugString(L"menuitemradio destruct!\r\n");
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::Font font1(&fontFamily, font_size - 4, FontStyleBold, UnitPixel);
			SizeF t;
			int w = 0; ;
			vector<int>::iterator it;
			int i = 0;
			for (it = items.begin(); it != items.end(); it++)
			{
				if (enabled == TRUE)
				{
					if (current_state == i)
					{
						DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
						FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					}
					else
					{
						DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					}
					/*//t = GetTextBounds(font2, &stringformat, m_Lan.GetValue(*(it)));
					int h = (this->item_height - t.Height) / 2 - 5;
					Gdiplus::PointF point0(this->x + 15, this->y + h + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);

					if (t.Width > this->width - 50)
					{
					//	g.DrawString(m_Lan.GetValue(*(it)), -1, &font1, point0, &brush);
					}
					else
					{
						g.DrawString(m_Lan.GetValue(*(it)), -1, &font2, point0, &brush);
					}*/
					
					i++;
				}
				else
				{

					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					FillRoundRectangle(g, Color(255, 155, 155, 155), this->x, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
				/*	t = GetTextBounds(font2, &stringformat, m_Lan.GetValue(*(it)));
					int h = (this->item_height - t.Height) / 2 - 5;
					Gdiplus::PointF point0(this->x + 15, this->y + h + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);

					if (t.Width > this->width - 50)
					{
						g.DrawString(m_Lan.GetValue(*(it)), -1, &font1, point0, &brush);
					}
					else
					{
						g.DrawString(m_Lan.GetValue(*(it)), -1, &font2, point0, &brush);
					}
					if (this->event_func == chooseacquiremode)//特殊处理获取方式会有下级菜单
					{
						if (this->items_type.at(i) == 1)
						{
							Gdiplus::PointF point(this->x + this->width - 60, this->y + h + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);
							g.DrawString(L">", -1, &font2, point, &brush);
						}
					}*/
					i++;
				}
			}
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SizeF t;
			int w = 0; ;
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::Font font1(&fontFamily, font_size - 4, FontStyleBold, UnitPixel);
			vector<int>::iterator it;

			int i = 0;
			for (it = items.begin(); it != items.end(); it++)
			{
				if (enabled == TRUE)
				{
					if (current_state == i)
					{
						DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
						FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					}
					else
					{
						DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					}
					//FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y + (menuitem_height + menuitem_interval)*i + fft_menu_scrool_pos, this->width - 25, this->height);
					/*t = GetTextBounds(font2, &stringformat, m_Lan.GetValue(*(it)));
					int h = (this->item_height - t.Height) / 2 - 5;
					Gdiplus::PointF point0(this->x + 15 + menucurrentpos, this->y + h + (item_height + menuitem_interval)*i + fft_menu_scrool_pos);

					if (this->event_func == chooseacquiremode)//特殊处理获取方式会有下级菜单
					{
						if (this->items_type.at(i) == 1)
						{
							Gdiplus::PointF point(this->x + this->width - 60 + menucurrentpos, this->y + h + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);
							g.DrawString(L">", -1, &font2, point, &brush);
						}
					}*/
				}
				else
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					/*t = GetTextBounds(font2, &stringformat, m_Lan.GetValue(*(it)));
					int h = (this->item_height - t.Height) / 2 - 5;
					Gdiplus::PointF point0(this->x + 15 + menucurrentpos, this->y + h + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);

					if (t.Width > this->width - 50)
					{
						g.DrawString(m_Lan.GetValue(*(it)), -1, &font1, point0, &brush);
					}
					else
					{
						g.DrawString(m_Lan.GetValue(*(it)), -1, &font2, point0, &brush);
					}
					if (this->event_func == chooseacquiremode)//特殊处理获取方式会有下级菜单
					{
						if (this->items_type.at(i) == 1)
						{
							Gdiplus::PointF point(this->x + this->width - 60 + menucurrentpos, this->y + h + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);
							g.DrawString(L">", -1, &font2, point, &brush);
						}
					}*/
				}
				i++;
			}
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			SizeF t;
			int w = 0; ;
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			Gdiplus::Font font1(&fontFamily, font_size - 4, FontStyleBold, UnitPixel);
			vector<int>::iterator it;
			int i = 0;
			for (it = items.begin(); it != items.end(); it++)
			{
				if (enabled == TRUE)
				{
					if (current_state == i)
					{
						DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
						FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					}
					else
					{
						DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					}
					/*t = GetTextBounds(font2, &stringformat, m_Lan.GetValue(*(it)));
					int h = (this->item_height - t.Height) / 2 - 5;
					Gdiplus::PointF point0(this->x + 15 - menucurrentpos, this->y + h + (item_height + menuitem_interval)*i + fft_menu_scrool_pos);
					if (t.Width > this->width - 50)
					{
						g.DrawString(m_Lan.GetValue(*(it)), -1, &font1, point0, &brush);
					}
					else
					{
						g.DrawString(m_Lan.GetValue(*(it)), -1, &font2, point0, &brush);
					}
					if (this->event_func == chooseacquiremode)//特殊处理获取方式会有下级菜单
					{
						if (this->items_type.at(i) == 1)
						{
							Gdiplus::PointF point(this->x + this->width - 60 - menucurrentpos, this->y + 15 + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);
							g.DrawString(L">", -1, &font2, point, &brush);
						}
					}*/
				}
				else
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					FillRoundRectangle(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					/*t = GetTextBounds(font2, &stringformat, m_Lan.GetValue(*(it)));
					int h = (this->item_height - t.Height) / 2 - 5;
					Gdiplus::PointF point0(this->x + 15 - menucurrentpos, this->y + h + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);

					if (t.Width > this->width - 50)
					{
						g.DrawString(m_Lan.GetValue(*(it)), -1, &font1, point0, &brush);
					}
					else
					{
						g.DrawString(m_Lan.GetValue(*(it)), -1, &font2, point0, &brush);
					}
					if (this->event_func == chooseacquiremode)//特殊处理获取方式会有下级菜单
					{
						if (this->items_type.at(i) == 1)
						{
							Gdiplus::PointF point(this->x + this->width - 60 - menucurrentpos, this->y + h + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);
							g.DrawString(L">", -1, &font2, point, &brush);
						}
					}*/
				}
				i++;
			}
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (enabled == TRUE)
		{
			if (EVENT_LBUTTON_UP == eventtype)
			{
				if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + fft_menu_scrool_pos&& y <= this->y + this->height + fft_menu_scrool_pos)
				{
					for (int i = 0; i < this->item_count; i++)
					{
						if (y >= this->y + fft_menu_scrool_pos + i*(item_height + menuitem_interval) && y <= this->y + fft_menu_scrool_pos + i*(item_height + menuitem_interval) + menuitem_height - 10)
						{
							if (this->type != Slide)
							{
								if (this->event_func(i) != 1)
								{
									this->current_state = i;
								}
							}
							return 1;
						}
					}
				}
			}
		}
		return 0;
	}
};

struct menuitemradio_string :windowitem//单选菜单
{
	int item_count;
	vector<CString> items;
	//vector<int> items;
	vector<int> items_type;
	vector<pFunc> items_func;
	int font_size;
	int item_height;
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);

			vector<CString>::iterator it;
			int i = 0;
			for (it = items.begin(); it != items.end(); it++)
			{
				if (current_state == i)
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
				}
				else
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
				}
				Gdiplus::PointF point0(this->x + 5, this->y + 15 + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);
				g.DrawString(*(it), -1, &font2, point0, &brush);

				/*if (this->event_func == chooseacquiremode)//特殊处理获取方式会有下级菜单
				{
				if (this->items_type.at(i) == 1)
				{
				Gdiplus::PointF point(this->x + this->width - 60, this->y + 15 + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);
				g.DrawString(L">", -1, &font2, point, &brush);
				}
				}*/
				i++;
			}
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);

			vector<CString>::iterator it;
			int i = 0;
			for (it = items.begin(); it != items.end(); it++)
			{
				if (current_state == i)
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
				}
				else
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
				}
				//FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y + (menuitem_height + menuitem_interval)*i + fft_menu_scrool_pos, this->width - 25, this->height);
				Gdiplus::PointF point0(this->x + 5 + menucurrentpos, this->y + 15 + (item_height + menuitem_interval)*i + fft_menu_scrool_pos);
				g.DrawString(*(it), -1, &font2, point0, &brush);

				/*if (this->event_func == chooseacquiremode)//特殊处理获取方式会有下级菜单
				{
				if (this->items_type.at(i) == 1)
				{
				Gdiplus::PointF point(this->x + this->width - 60 + menucurrentpos, this->y + 15 + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);
				g.DrawString(L">", -1, &font2, point, &brush);
				}
				}*/
				i++;
			}
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			vector<CString>::iterator it;
			int i = 0;
			for (it = items.begin(); it != items.end(); it++)
			{
				if (current_state == i)
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
					FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
				}
				else
				{
					DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + (item_height + menuitem_interval) * i + fft_menu_scrool_pos, this->width - 25, item_height);
				}
				Gdiplus::PointF point0(this->x + 5 - menucurrentpos, this->y + 15 + (item_height + menuitem_interval)*i + fft_menu_scrool_pos);
				g.DrawString(*(it), -1, &font2, point0, &brush);

				/*	if (this->event_func == chooseacquiremode)//特殊处理获取方式会有下级菜单
				{
				if (this->items_type.at(i) == 1)
				{
				Gdiplus::PointF point(this->x + this->width - 60 - menucurrentpos, this->y + 15 + i * (item_height + menuitem_interval) + fft_menu_scrool_pos);
				g.DrawString(L">", -1, &font2, point, &brush);
				}
				}*/
				i++;
			}
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (EVENT_LBUTTON_UP == eventtype)
		{
			if (this->hide == FALSE)
			{
				if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + fft_menu_scrool_pos&& y <= this->y + this->height + fft_menu_scrool_pos)
				{
					for (int i = 0; i < this->item_count; i++)
					{
						if (y >= this->y + fft_menu_scrool_pos + i*(item_height + menuitem_interval) && y <= this->y + fft_menu_scrool_pos + i*(item_height + menuitem_interval) + item_height)
						{
							if (this->type != Slide)
							{
								if (this->event_func(i) != 1)
								{
									this->current_state = i;
								}
							}
							return 1;
						}
					}
				}
			}
		}
		return 0;
	}
};
struct MenuSlideButton :windowitem
{
	CString title;
	int button_pos_x;
	int button_pos_y;
	int button_width;
	int button_height;
	int click_pos_x;//按下时的x坐标
	int click_pos_y;//按下时的y坐标
	BOOL slide_change;//是否为滑动改变
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Pen pen1(Color(255, 0, 255, 0));
			Gdiplus::Font font1(&fontFamily, 25, FontStyleBold, UnitPixel);
			Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);
			if (enabled)
			{
				FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			if (this->current_state == SLIDE_BUTTON_OFF || enabled == FALSE)//当前状态是关闭状态
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40, this->button_pos_y + fft_menu_scrool_pos, this->button_width, this->button_height);
				FillRoundRectangle(g, Color(255, 50, 50, 50), this->x + this->width - this->button_width - 40, this->button_pos_y + fft_menu_scrool_pos, this->button_width, this->button_height);
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40 + 2, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40 + 2, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				SizeF t;
				t = GetTextBounds(font2, &stringformat, L"关");
				int w = this->button_width / 2 - t.Width;
				int h = (this->height - t.Height) / 2 - 5;
				Gdiplus::PointF point0(this->x + this->width - this->button_width - 40 + w / 2 - 5, this->button_pos_y + h + fft_menu_scrool_pos);
				g.DrawString(L"关", -1, &font2, point0, &brush);
			}
			else//当前状态是打开状态
			{
				SizeF t;
				t = GetTextBounds(font2, &stringformat, L"开");
				int w = this->width - t.Width;
				int h = (this->height - t.Height) / 2 - 5;
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + this->width - this->button_width - 40, this->button_pos_y + fft_menu_scrool_pos, this->button_width, this->button_height);
				DrawRoundRectange(g, Color(255, 155, 50, 50), this->x + this->width - this->button_width - 40 + this->button_width / 2 + 2, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				FillRoundRectangle(g, Color(255, 50, 50, 50), this->x + this->width - this->button_width - 40 + this->button_width / 2 + 2, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				TextOut(hdc, this->x + this->width - this->button_width - 49 + this->button_width / 2 + 24, this->button_pos_y + h + fft_menu_scrool_pos, L"开", 1);
			}
			SizeF 	t = GetTextBounds(font2, &stringformat, L"开");
			int h = (this->height - t.Height) / 2 - 5;
			Gdiplus::PointF point0(this->x + 15, this->y + h + fft_menu_scrool_pos);
			g.DrawString(L"开", -1, &font2, point0, &brush);
		}
		return 1;
	}

	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Pen pen1(Color(255, 0, 255, 0));
			Gdiplus::Font font1(&fontFamily, 25, FontStyleBold, UnitPixel);
			Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);
			if (enabled)
			{
				FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			if (this->current_state == SLIDE_BUTTON_OFF || enabled == FALSE)//如果当前状态是关闭状态
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40 + menucurrentpos, this->button_pos_y + fft_menu_scrool_pos, this->button_width, this->button_height);
				FillRoundRectangle(g, Color(255, 50, 50, 50), this->x + this->width - this->button_width - 40 + menucurrentpos, this->button_pos_y + fft_menu_scrool_pos, this->button_width, this->button_height);
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40 + 2 + menucurrentpos, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40 + 2 + menucurrentpos, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				SizeF t;
				t = GetTextBounds(font2, &stringformat, L"关");
				int w = this->button_width / 2 - t.Width;
				int h = (this->height - t.Height) / 2 - 5;
				Gdiplus::PointF point0(this->x + this->width - this->button_width - 40 + w / 2 - 5 + menucurrentpos, this->button_pos_y + h + fft_menu_scrool_pos);
				g.DrawString(L"关", -1, &font2, point0, &brush);
			}
			else//当前状态是打开状态
			{
				SizeF t;
				t = GetTextBounds(font2, &stringformat, L"开");
				int w = this->width - t.Width;
				int h = (this->height - t.Height) / 2 - 5;
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + this->width - this->button_width - 40 + menucurrentpos, this->button_pos_y + fft_menu_scrool_pos, this->button_width, this->button_height);
				DrawRoundRectange(g, Color(255, 155, 50, 50), this->x + this->width - this->button_width - 40 + this->button_width / 2 + 2 + menucurrentpos, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				FillRoundRectangle(g, Color(255, 50, 50, 50), this->x + this->width - this->button_width - 40 + this->button_width / 2 + 2 + menucurrentpos, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				TextOut(hdc, this->x + this->width - this->button_width - 49 + this->button_width / 2 + 24 + menucurrentpos, this->button_pos_y + h + fft_menu_scrool_pos, L"开", 1);
			}
			SizeF 	t = GetTextBounds(font2, &stringformat, L"开");
			int h = (this->height - t.Height) / 2 - 5;
			Gdiplus::PointF point0(this->x + 15 + menucurrentpos, this->y + h + fft_menu_scrool_pos);
			g.DrawString(L"开", -1, &font2, point0, &brush);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Pen pen1(Color(255, 0, 255, 0));
			Gdiplus::Font font1(&fontFamily, 25, FontStyleBold, UnitPixel);
			Gdiplus::Font font2(&fontFamily, 30, FontStyleBold, UnitPixel);
			if (enabled)
			{
				FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			if (this->current_state == SLIDE_BUTTON_OFF || enabled == FALSE)//如果当前状态是关闭状态
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40 - menucurrentpos, this->button_pos_y + fft_menu_scrool_pos, this->button_width, this->button_height);
				FillRoundRectangle(g, Color(255, 50, 50, 50), this->x + this->width - this->button_width - 40 - menucurrentpos, this->button_pos_y + fft_menu_scrool_pos, this->button_width, this->button_height);
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40 + 2 - menucurrentpos, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40 + 2 - menucurrentpos, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				SizeF t;
				t = GetTextBounds(font2, &stringformat, L"关");
				int w = this->button_width / 2 - t.Width;
				int h = (this->height - t.Height) / 2 - 5;
				Gdiplus::PointF point0(this->x + this->width - this->button_width - 40 + w / 2 - 5 - menucurrentpos, this->button_pos_y + h + fft_menu_scrool_pos);
				g.DrawString(L"关", -1, &font2, point0, &brush);
			}
			else//当前状态是打开状态
			{
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + this->width - this->button_width - 40 - menucurrentpos, this->button_pos_y + fft_menu_scrool_pos, this->button_width, this->button_height);
				DrawRoundRectange(g, Color(255, 155, 50, 50), this->x + this->width - this->button_width - 40 + this->button_width / 2 + 2 - menucurrentpos, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				FillRoundRectangle(g, Color(255, 50, 50, 50), this->x + this->width - this->button_width - 40 + this->button_width / 2 + 2 - menucurrentpos, this->button_pos_y + 2 + fft_menu_scrool_pos, this->button_width / 2 - 4, this->button_height - 5);
				SizeF t;
				t = GetTextBounds(font2, &stringformat, L"开");
				int w = this->width - t.Width;
				int h = (this->height - t.Height) / 2 - 5;
				TextOut(hdc, this->x + this->width - this->button_width - 49 + this->button_width / 2 + 24 - menucurrentpos, this->button_pos_y + h + fft_menu_scrool_pos, L"开", 1);
			}
			SizeF 	t = GetTextBounds(font2, &stringformat, L"开");
			int h = (this->height - t.Height) / 2 - 5;
			Gdiplus::PointF point0(this->x + 15 - menucurrentpos, this->y + h + fft_menu_scrool_pos);
			g.DrawString(L"开", -1, &font2, point0, &brush);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (EVENT_LBUTTON_UP == eventtype)//如果鼠标点击了该控件的左半边，说明是要切换到关闭状态
		{
			ifhit = FALSE;
			if (this->enabled)
			{
				if (slide_change == FALSE)
				{

					if (x >= this->x + this->width - this->button_width - 40 && x <= this->x + this->width - this->button_width - 40 + this->button_width / 2 && y >= this->button_pos_y + fft_menu_scrool_pos&& y <= this->button_pos_y + this->button_height + fft_menu_scrool_pos)
					{
						this->current_state = SLIDE_BUTTON_OFF;
						return 1;
					}//如果鼠标点击了该控件的右半边，说明是要切换到关闭状态
					else if (x >= this->x + this->width - this->button_width - 40 + this->button_width / 2 && x <= this->x + this->width - this->button_width - 40 + this->button_width && y >= this->button_pos_y + fft_menu_scrool_pos&& y <= this->button_pos_y + this->button_height + fft_menu_scrool_pos)
					{
						this->current_state = SLIDE_BUTTON_ON;
						return 1;
					}
				}
			}
			slide_change = FALSE;
		}
		else if (EVENT_LBUTTON_DOWN == eventtype)
		{
			if (this->enabled)
			{
				if (x >= this->x + this->width - this->button_width - 40 && x <= this->x + this->width - this->button_width - 40 + this->button_width && y >= this->button_pos_y + fft_menu_scrool_pos&& y <= this->button_pos_y + this->button_height + fft_menu_scrool_pos)
				{
					ifhit = TRUE;
					click_pos_x = x;
					click_pos_y = y;
					slide_change = FALSE;
					return 0;
				}
			}
		}
		else if (EVENT_MOUSEMOVE == eventtype)
		{
			if (this->enabled && ifhit == TRUE)
			{
				if (x >= this->x + this->width - this->button_width - 40 && x <= this->x + this->width - this->button_width - 40 + this->button_width  && y >= this->button_pos_y + fft_menu_scrool_pos&& y <= this->button_pos_y + this->button_height + fft_menu_scrool_pos)
				{
					int x_diff = x - click_pos_x;
					if (x_diff > 0 && abs(x_diff) > 20)//向右滑动
					{
						this->current_state = SLIDE_BUTTON_ON;
						slide_change = TRUE;
						return 1;
					}
					else if (x_diff < 0 && abs(x_diff) > 20)//向左滑动
					{
						this->current_state = SLIDE_BUTTON_OFF;
						slide_change = TRUE;
						return 1;
					}
					else
					{
						slide_change = FALSE;
					}
					return 0;
				}
			}
		}
		return 0;
	}
};
struct menuitembutton :windowitem//按钮
{
	CString title;
	Align_Type  align_type;
	menuitembutton(int columnwidth = 200, int columnheight = 80, Align_Type aligntype = Align_Left) :windowitem()
	{
		width = columnwidth;
		height = columnheight;
		always_show = FALSE;
		align_type = aligntype;//默认是左对齐
		color = RGB(0, 0, 0);
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			if (this->ifhit == TRUE)
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
				FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + 3, this->y + fft_menu_scrool_pos + 3, this->width - 25 - 6, this->height - 6);
			}
			else
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			if (enabled)
			{
				//FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
				if (color == RGB(0, 0, 0))
				{

				}
				else
				{
					FillRoundRectangle(g, Color(255, GetRValue(color), GetGValue(color), GetBValue(color)), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
				}
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			Pen *pen = new Pen(Color(255, 255, 255, 255), 1);
			Gdiplus::PointF point1(this->x + 5, this->y + this->height - 5 + fft_menu_scrool_pos);
			Gdiplus::PointF point2(this->x + this->width - 25, this->y + this->height - 5 + fft_menu_scrool_pos);
			int font_size = 30;
			for (; font_size >= 20;)
			{
				Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
				SizeF t;
				t = GetTextBounds(font2, &stringformat, this->title);
				if (t.Width > this->width - 90)
				{
					font_size -= 2;
				}
				else
				{
					break;
				}
			}

			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int h = (this->height - t.Height) / 2 - 5;
			if (align_type == Align_Left)
			{
				Gdiplus::PointF point0(this->x + 15, this->y + h + fft_menu_scrool_pos);
				g.DrawString(this->title, -1, &font2, point0, &brush);
			}
			else //if(align_type == Align_Center)
			{
				SizeF t;
				t = GetTextBounds(font2, &stringformat, this->title);
				int w = (this->width - t.Width) / 2 - 20;
				Gdiplus::PointF point0(this->x + w, this->y + h + fft_menu_scrool_pos);
				g.DrawString(this->title, -1, &font2, point0, &brush);
			}

			if (this->subview != NULL)
			{
				Gdiplus::PointF point(this->x + this->width - 60, this->y + h + fft_menu_scrool_pos);
				g.DrawString(L">", -1, &font2, point, &brush);
			}
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			
			//DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			if (this->ifhit == TRUE)
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
				FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + 3 + menucurrentpos, this->y + fft_menu_scrool_pos + 3, this->width - 25 - 6, this->height - 6);
			}
			else
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			if (enabled)
			{
				//FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			Pen *pen = new Pen(Color(255, 255, 255, 255), 1);
			Gdiplus::PointF point1(this->x + 5 + menucurrentpos, this->y + this->height - 5 + fft_menu_scrool_pos);
			Gdiplus::PointF point2(this->x + this->width - 25 + menucurrentpos, this->y + this->height - 5 + fft_menu_scrool_pos);
			int font_size = 30;
			for (; font_size >= 20;)
			{
				Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
				SizeF t;
				t = GetTextBounds(font2, &stringformat, this->title);
				if (t.Width > this->width - 90)
				{
					font_size -= 2;
				}
				else
				{
					break;
				}
			}
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int h = (this->height - t.Height) / 2 - 5;
			if (align_type == Align_Left)
			{
				Gdiplus::PointF point0(this->x + 15 + menucurrentpos, this->y + h + fft_menu_scrool_pos);
				g.DrawString(this->title, -1, &font2, point0, &brush);
			}
			else //if(align_type == Align_Center)
			{
				SizeF t;
				t = GetTextBounds(font2, &stringformat, this->title);
				int w = (this->width - t.Width) / 2 - 20;
				Gdiplus::PointF point0(this->x + w + menucurrentpos, this->y + h + fft_menu_scrool_pos);
				g.DrawString(this->title, -1, &font2, point0, &brush);
			}
			if (this->subview != NULL)
			{
				Gdiplus::PointF point(this->x + this->width - 60 + menucurrentpos, this->y + h + fft_menu_scrool_pos);
				g.DrawString(L">", -1, &font2, point, &brush);
			}
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			//DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			if (this->ifhit == TRUE)
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
				FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + 3 - menucurrentpos, this->y + fft_menu_scrool_pos + 3, this->width - 25 - 6, this->height - 6);
			}
			else
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			if (enabled)
			{
				//FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			Pen *pen = new Pen(Color(255, 255, 255, 255), 1);
			Gdiplus::PointF point1(this->x + 5 - menucurrentpos, this->y + this->height - 5 + fft_menu_scrool_pos);
			Gdiplus::PointF point2(this->x + this->width - 25 - menucurrentpos, this->y + this->height - 5 + fft_menu_scrool_pos);
			int font_size = 30;
			for (; font_size >= 20;)
			{
				Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
				SizeF t;
				t = GetTextBounds(font2, &stringformat, this->title);
				if (t.Width > this->width - 90)
				{
					font_size = font_size - 2;
				}
				else
				{
					break;
				}
			}
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int h = (this->height - t.Height) / 2 - 5;
			if (align_type == Align_Left)
			{
				Gdiplus::PointF point0(this->x + 15 - menucurrentpos, this->y + h + fft_menu_scrool_pos);
				g.DrawString(this->title, -1, &font2, point0, &brush);
			}
			else //if(align_type == Align_Center)
			{
				SizeF t;
				t = GetTextBounds(font2, &stringformat, this->title);
				int w = (this->width - t.Width) / 2 - 20;
				Gdiplus::PointF point0(this->x + w - menucurrentpos, this->y + h + fft_menu_scrool_pos);
				g.DrawString(this->title, -1, &font2, point0, &brush);
			}

			if (this->subview != NULL)
			{
				Gdiplus::PointF point(this->x + this->width - 60 - menucurrentpos, this->y + h + fft_menu_scrool_pos);
				g.DrawString(L">", -1, &font2, point, &brush);
			}
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (EVENT_LBUTTON_DOWN == eventtype)
		{
			if (this->enabled)
			{
				if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + fft_menu_scrool_pos&& y <= this->y + this->height + fft_menu_scrool_pos)
				{
					this->ifhit = TRUE;
					
					return 0;
				}
			}
		}
		else if (EVENT_LBUTTON_UP == eventtype)
		{
			if (this->enabled)
			{
				if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + fft_menu_scrool_pos&& y <= this->y + this->height + fft_menu_scrool_pos)
				{
					this->ifhit = FALSE;
					
					return 1;
				}
				this->ifhit = FALSE;
				
			}
		}
		else if (EVENT_MOUSEOUT_UP == eventtype)
		{
			this->ifhit = FALSE;
			
		}
		return 0;
	}
};

struct menuitembutton_string :windowitem//按钮
{
	CString title;
	int font_size;

	menuitembutton_string(int columnwidth = 200, int columnheight = 80, int fontsize = 30) :windowitem()
	{
		width = columnwidth;
		height = columnheight;
		font_size = fontsize;
		always_show = FALSE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			if (enabled)
			{
				//FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			Pen *pen = new Pen(Color(255, 255, 255, 255), 1);
			Gdiplus::PointF point1(this->x + 5, this->y + this->height - 5 + fft_menu_scrool_pos);
			Gdiplus::PointF point2(this->x + this->width - 25, this->y + this->height - 5 + fft_menu_scrool_pos);
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - t.Width;
			int h = this->height - t.Height;
			Gdiplus::PointF point0(this->x + 5, this->y + h / 2 + fft_menu_scrool_pos);
			g.DrawString(this->title, -1, &font2, point0, &brush);
			if (this->subview != NULL)
			{
				Gdiplus::PointF point(this->x + this->width - 60, this->y + 15 + fft_menu_scrool_pos);
				g.DrawString(L">", -1, &font2, point, &brush);
			}
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			if (enabled)
			{
				//FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			Pen *pen = new Pen(Color(255, 255, 255, 255), 1);
			Gdiplus::PointF point1(this->x + 5 + menucurrentpos, this->y + this->height - 5 + fft_menu_scrool_pos);
			Gdiplus::PointF point2(this->x + this->width - 25 + menucurrentpos, this->y + this->height - 5 + fft_menu_scrool_pos);
			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - t.Width;
			int h = this->height - t.Height;
			Gdiplus::PointF point0(this->x + 5 + menucurrentpos, this->y + h / 2 + fft_menu_scrool_pos);
			g.DrawString(this->title, -1, &font2, point0, &brush);
			if (this->subview != NULL)
			{
				Gdiplus::PointF point(this->x + this->width - 60 + menucurrentpos, this->y + 15 + fft_menu_scrool_pos);
				g.DrawString(L">", -1, &font2, point, &brush);
			}
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			if (enabled)
			{
				//FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width - 25, this->height);
			}
			Pen *pen = new Pen(Color(255, 255, 255, 255), 1);
			Gdiplus::PointF point1(this->x + 5 - menucurrentpos, this->y + this->height - 5 + fft_menu_scrool_pos);
			Gdiplus::PointF point2(this->x + this->width - 25 - menucurrentpos, this->y + this->height - 5 + fft_menu_scrool_pos);

			Gdiplus::Font font2(&fontFamily, font_size, FontStyleBold, UnitPixel);
			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->title);
			int w = this->width - t.Width;
			int h = this->height - t.Height;
			Gdiplus::PointF point0(this->x + 5 - menucurrentpos, this->y + h / 2 + fft_menu_scrool_pos);
			g.DrawString(this->title, -1, &font2, point0, &brush);
			if (this->subview != NULL)
			{
				Gdiplus::PointF point(this->x + this->width - 60 - menucurrentpos, this->y + 15 + fft_menu_scrool_pos);
				g.DrawString(L">", -1, &font2, point, &brush);
			}
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (EVENT_LBUTTON_UP == eventtype)
		{
			if (this->enabled)
			{
				if (x >= this->x + 5 && x <= this->x + this->width && y >= this->y + fft_menu_scrool_pos&& y <= this->y + this->height + fft_menu_scrool_pos)
				{
					return 1;
				}
			}
		}
		return 0;
	}
};
struct menuitemslide :windowitem//滑块
{
	CString title;
	float current_value;
	int button_width;
	int button_height;
	int slide_width;
	int slide_height;
	float max_value;
	float min_value;
	BOOL button_hit;
	menuitemslide(int columnwidth = 200, int columnheight = 80) :windowitem()
	{
		width = columnwidth;
		height = columnheight;
		always_show = FALSE;
		button_hit = FALSE;
		current_value = 0;
		type = Slide;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;
			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width, this->height);
			if (enabled)
			{
				FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + fft_menu_scrool_pos, this->width, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width, this->height);
			}
			Pen *pen = new Pen(Color(255, 100, 100, 100), 4);
			Gdiplus::PointF point1(this->x + this->width / 2, this->y + 5 /*+ this->height / 2 */ + fft_menu_scrool_pos);
			Gdiplus::PointF point2(this->x + this->width / 2, this->y + 5 + this->height - 10 + fft_menu_scrool_pos);
			g.DrawLine(pen, point1, point2);

			DrawRoundRectange(g, Color(255, 155, 50, 50), this->x + 10, this->y + this->height - 10 - this->current_value - this->button_height / 2 + fft_menu_scrool_pos, this->button_width, this->button_height);
			FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + 10, this->y + this->height - 10 - this->current_value - this->button_height / 2 + fft_menu_scrool_pos, this->button_width, this->button_height);
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width, this->height);
			if (enabled)
			{
				FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + menucurrentpos, this->y + fft_menu_scrool_pos, this->width, this->height);
			}
			Pen *pen = new Pen(Color(255, 100, 100, 100), 4);
			Gdiplus::PointF point1(this->x + this->width / 2 + menucurrentpos, this->y + 5 /*+ this->height / 2 */ + fft_menu_scrool_pos);
			Gdiplus::PointF point2(this->x + this->width / 2 + menucurrentpos, this->y + 5 + this->height - 10 + fft_menu_scrool_pos);
			g.DrawLine(pen, point1, point2);

			DrawRoundRectange(g, Color(255, 155, 50, 50), this->x + 10 + menucurrentpos, this->y + this->height - 10 - this->current_value - this->button_height / 2 + fft_menu_scrool_pos, this->button_width, this->button_height);
			FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + 10 + menucurrentpos, this->y + this->height - 10 - this->current_value - this->button_height / 2 + fft_menu_scrool_pos, this->button_width, this->button_height);
		}
		return 1;
	}
	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width, this->height);
			if (enabled)
			{
				FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width, this->height);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x - menucurrentpos, this->y + fft_menu_scrool_pos, this->width, this->height);
			}
			Pen *pen = new Pen(Color(255, 100, 100, 100), 4);
			Gdiplus::PointF point1(this->x + this->width / 2 - menucurrentpos, this->y + 5 /*+ this->height / 2 */ + fft_menu_scrool_pos);
			Gdiplus::PointF point2(this->x + this->width / 2 - menucurrentpos, this->y + 5 + this->height - 10 + fft_menu_scrool_pos);
			g.DrawLine(pen, point1, point2);

			DrawRoundRectange(g, Color(255, 155, 50, 50), this->x + 10 - menucurrentpos, this->y + this->height - 10 - this->current_value - this->button_height / 2 + fft_menu_scrool_pos, this->button_width, this->button_height);
			FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + 10 - menucurrentpos, this->y + this->height - 10 - this->current_value - this->button_height / 2 + fft_menu_scrool_pos, this->button_width, this->button_height);

		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (EVENT_LBUTTON_UP == eventtype)
		{
			button_hit = FALSE;
			if (this->enabled)
			{
				if (x >= this->x && x <= this->x + this->width && y >= this->y + fft_menu_scrool_pos&& y <= this->y + this->height + fft_menu_scrool_pos)
				{
					return 1;
				}
			}
		}
		else if (EVENT_LBUTTON_DOWN == eventtype)
		{
			button_hit = FALSE;
			if (x >= this->x  && x <= this->x + this->width && y >= this->y + fft_menu_scrool_pos&& y <= this->y + this->height + fft_menu_scrool_pos)
			{
				button_hit = TRUE;
				return 1;
			}
			return 0;
		}
		else if (EVENT_MOUSEMOVE == eventtype)
		{
			if (button_hit)
			{
				if (this->y + this->height - y >= min_value && this->y + this->height - y <= max_value)
				{
					current_value = (float)(this->y + this->height - y);
				}
				return 1;
			}
			return 0;
		}
		return 0;
	}
};
struct menuspin :windowitem
{
	CString title;
	CString	unit;//单位
	float step;//每次增加或减小的值
	float min;//最小值
	float max;//最大值
	float current_value;
	int button_pos_x;
	int button_width;
	int button_height;
	menuspin(int columnwidth = 200, int columnheight = 80, int state = SLIDE_BUTTON_OFF) :windowitem()
	{
		width = columnwidth;
		height = columnheight;
		always_show = FALSE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			int i = 0;
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			SolidBrush brush1(Color(255, 200, 200, 200));

			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");

			Gdiplus::Font font1(&fontFamily, 55, FontStyleBold, UnitPixel);
			Gdiplus::Font font2(&fontFamily, 40, FontStyleBold, UnitPixel);
			Gdiplus::Font font3(&fontFamily, 26, FontStyleBold, UnitPixel);

			Gdiplus::PointF point11(this->x + 15/* - menucurrentpos*/, this->y + fft_menu_scrool_pos);
			g.DrawString(this->title, -1, &font3, point11, &brush1);

			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x, this->y + fft_menu_scrool_pos + this->height / 2 - 25, this->width - 25, this->height / 2 + 10);

			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + 15, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->button_height);
			if (this->current_value > this->min)//如果值小于最小值，减号按钮绘制成灰色表示不可以继续减小了
			{
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + 15, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + 15, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}
			Gdiplus::PointF point1(this->x + 23, this->y + this->height / 2 - 12 + fft_menu_scrool_pos);
			g.DrawString(L"-", -1, &font1, point1, &brush);

			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->button_height);
			if (this->max - this->current_value > 0)//如果值大于最大值，加号按钮绘制成灰色表示不可以继续增加了
			{
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + this->width - this->button_width - 40, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}

			Gdiplus::PointF point2(this->x + +this->width - this->button_width - 33, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 23);
			g.DrawString(L"+", -1, &font1, point2, &brush);

			Gdiplus::PointF point3(this->x + this->button_width + 30, this->y + this->height / 2 - 7 + fft_menu_scrool_pos);
			CString tip;
			tip.Format(L"%0.2f", this->current_value);
			g.DrawString(tip, -1, &font2, point3, &brush);
		}
		return 1;
	}
	int draw_forward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			int i = 0;
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			SolidBrush brush1(Color(255, 200, 200, 200));

			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");

			Gdiplus::Font font1(&fontFamily, 55, FontStyleBold, UnitPixel);
			Gdiplus::Font font2(&fontFamily, 40, FontStyleBold, UnitPixel);
			Gdiplus::Font font3(&fontFamily, 26, FontStyleBold, UnitPixel);

			Gdiplus::PointF point11(this->x + 15 + menucurrentpos/* - menucurrentpos*/, this->y + fft_menu_scrool_pos);
			g.DrawString(this->title, -1, &font3, point11, &brush1);

			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x + menucurrentpos, this->y + fft_menu_scrool_pos + this->height / 2 - 25, this->width - 25, this->height / 2 + 10);

			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos + 15, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->button_height);
			if (this->current_value > this->min)//如果值小于最小值，减号按钮绘制成灰色表示不可以继续减小了
			{
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + menucurrentpos + 15, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + menucurrentpos + 15, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}
			Gdiplus::PointF point1(this->x + menucurrentpos + 23, this->y + this->height / 2 - 12 + fft_menu_scrool_pos);
			g.DrawString(L"-", -1, &font1, point1, &brush);

			//	Gdiplus::PointF point12(this->x +this->width - 105, this->y + 19 + fft_menu_scrool_pos);
			//	g.DrawString(this->unit, -1, &font3, point12, &brush);

			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + menucurrentpos + this->width - this->button_width - 40, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->button_height);
			if (this->max - this->current_value > 0)//如果值大于最大值，加号按钮绘制成灰色表示不可以继续增加了
			{
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + menucurrentpos + this->width - this->button_width - 40, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + menucurrentpos + this->width - this->button_width - 40, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}

			Gdiplus::PointF point2(this->x + menucurrentpos + this->width - this->button_width - 33, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 23);
			g.DrawString(L"+", -1, &font1, point2, &brush);

			Gdiplus::PointF point3(this->x + menucurrentpos + this->button_width + 30, this->y + this->height / 2 - 7 + fft_menu_scrool_pos);
			CString tip;
			tip.Format(L"%0.2f", this->current_value);
			g.DrawString(tip, -1, &font2, point3, &brush);
		}
		return 1;
	}

	int draw_backward(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			int i = 0;
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			SolidBrush brush1(Color(255, 200, 200, 200));

			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");

			Gdiplus::Font font1(&fontFamily, 55, FontStyleBold, UnitPixel);
			Gdiplus::Font font2(&fontFamily, 40, FontStyleBold, UnitPixel);
			Gdiplus::Font font3(&fontFamily, 26, FontStyleBold, UnitPixel);

			Gdiplus::PointF point11(this->x + 15 - menucurrentpos/* - menucurrentpos*/, this->y + fft_menu_scrool_pos);
			g.DrawString(this->title, -1, &font3, point11, &brush1);

			FillRoundRectangle(g, Color(255, 51, 102, 205), this->x - menucurrentpos, this->y + fft_menu_scrool_pos + this->height / 2 - 25, this->width - 25, this->height / 2 + 10);

			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos + 15, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->button_height);
			if (this->current_value > this->min)//如果值小于最小值，减号按钮绘制成灰色表示不可以继续减小了
			{
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x - menucurrentpos + 15, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x - menucurrentpos + 15, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}
			Gdiplus::PointF point1(this->x - menucurrentpos + 23, this->y + this->height / 2 - 12 + fft_menu_scrool_pos);
			g.DrawString(L"-", -1, &font1, point1, &brush);

			//	Gdiplus::PointF point12(this->x +this->width - 105, this->y + 19 + fft_menu_scrool_pos);
			//	g.DrawString(this->unit, -1, &font3, point12, &brush);

			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x - menucurrentpos + this->width - this->button_width - 40, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->button_height);
			if (this->max - this->current_value > 0)//如果值大于最大值，加号按钮绘制成灰色表示不可以继续增加了
			{
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x - menucurrentpos + this->width - this->button_width - 40, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x - menucurrentpos + this->width - this->button_width - 40, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->height / 2 - 10);
			}

			Gdiplus::PointF point2(this->x - menucurrentpos + this->width - this->button_width - 33, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 23);
			g.DrawString(L"+", -1, &font1, point2, &brush);

			Gdiplus::PointF point3(this->x - menucurrentpos + this->button_width + 30, this->y + this->height / 2 - 7 + fft_menu_scrool_pos);
			CString tip;
			tip.Format(L"%0.2f", this->current_value);
			g.DrawString(tip, -1, &font2, point3, &brush);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (EVENT_LBUTTON_UP == eventtype)
		{
			//DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + 15, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->button_height);
			if (x >= this->x + 15 && x <= this->x + 15 + this->button_width && y >= this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25 && y <= this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25 + this->button_height)
			{
				if (this->current_value - this->step >= this->min)//减小当前值
				{
					this->current_value -= this->step;
				}
				
				return 1;
			}//DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + this->width - this->button_width - 40, this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25, this->button_width, this->button_height);
			else if (x >= this->x + this->width - this->button_width - 40 && x <= this->x + this->width - this->button_width - 40 + this->button_width && y >= this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25 && y <= this->y + 10 + fft_menu_scrool_pos + this->height / 2 - 25 + this->button_height)
			{
				if (this->current_value + this->step <= this->max)//增大当前值
				{
					this->current_value += this->step;
				}
				
				return 1;
			}
		}
		return 0;
	}
};
struct group :windowitem//分组，就是一个标题加上一个外框，类似MFC中的GROUP控件
{
	CString header;
	group(CString title, int columnwidth = 200, int columnheight = 80) :windowitem()
	{
		width = columnwidth;
		height = columnheight;
		header = title;
		always_show = FALSE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			int i = 0;
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");

			Gdiplus::Font font1(&fontFamily, 55, FontStyleBold, UnitPixel);
			Gdiplus::Font font2(&fontFamily, 35, FontStyleBold, UnitPixel);

			SizeF t;
			t = GetTextBounds(font2, &stringformat, this->header);
			DrawGroupRectange(g, Color(255, 155, 155, 155), this->x, this->y + fft_menu_scrool_pos, this->width, this->height, header, t.Width + 10);
			int w = (width - t.Width) / 2;
			Gdiplus::PointF point0(this->x + OFFSET_X + w - 8, this->y - 18 + fft_menu_scrool_pos);
			g.DrawString(header, -1, &font2, point0, &brush);
		}
		return 1;
	}
};

struct spin :windowitem//左边一个减号，右边一个加号，中间是当前的值，可以按加号或减号改变当前的值，目前不能直接编辑中间的值
{
	float step;//每次增加或减小的值
	float min;//最小值
	float max;//最大值
	float current_value;
	spin(int columnwidth = 200, int columnheight = 80, int state = SLIDE_BUTTON_OFF) :windowitem()
	{
		width = columnwidth;
		height = columnheight;
		always_show = FALSE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			int i = 0;
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");

			Gdiplus::Font font1(&fontFamily, 55, FontStyleBold, UnitPixel);
			Gdiplus::Font font2(&fontFamily, 40, FontStyleBold, UnitPixel);

			DrawRoundRectange(g, Color(255, 155, 155, 155), this->x /*- menucurrentpos*/, this->y + fft_menu_scrool_pos, this->width, this->height);
			if (this->current_value > this->min)//如果值小于最小值，减号按钮绘制成灰色表示不可以继续减小了
			{
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + 5 /*- menucurrentpos*/, this->y + 5 + fft_menu_scrool_pos, this->width / 4, this->height - 10);
			}
			else
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + 5 /*- menucurrentpos*/, this->y + 5 + fft_menu_scrool_pos, this->width / 4, this->height - 10);
			}
			Gdiplus::PointF point1(this->x + 20/* - menucurrentpos*/, this->y + 13 + fft_menu_scrool_pos);
			g.DrawString(L"-", -1, &font1, point1, &brush);

			if (this->current_value < this->max)//如果值大于最大值，加号按钮绘制成灰色表示不可以继续增加了
			{
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x + this->width / 4 * 3 - 5/* - menucurrentpos*/, this->y + 5 + fft_menu_scrool_pos, this->width / 4, this->height - 10);
			}
			if (this->current_value >= this->max)
			{
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + this->width / 4 * 3 - 5/* - menucurrentpos*/, this->y + 5 + fft_menu_scrool_pos, this->width / 4, this->height - 10);
			}

			Gdiplus::PointF point2(this->x + this->width / 4 * 3 + 10 /*- menucurrentpos*/, this->y + 13 + fft_menu_scrool_pos);
			g.DrawString(L"+", -1, &font1, point2, &brush);

			Gdiplus::PointF point3(this->x + this->width / 4 + 23 /*- menucurrentpos*/, this->y + 18 + fft_menu_scrool_pos);
			CString tip;
			tip.Format(L"%0.2f", this->current_value);
			g.DrawString(tip, -1, &font2, point3, &brush);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (EVENT_LBUTTON_UP == eventtype)
		{
			if (x >= this->x + 5 && x <= this->x + 5 + this->width / 4 && y >= this->y + 5 + fft_menu_scrool_pos&& y <= this->y + 5 - 10 + this->height + fft_menu_scrool_pos)
			{
				if (this->current_value > this->min)//减小当前值
				{
					this->current_value -= this->step;
				}
				return 1;
			}
			else if (x >= this->x + this->width / 4 * 3 - 5 && x <= this->x + this->width / 4 * 3 - 5 + this->width / 4 && y >= this->y + 5 + fft_menu_scrool_pos && y <= this->y + 5 + fft_menu_scrool_pos + this->height - 10)
			{
				if (this->current_value < this->max)//增大当前值
				{
					this->current_value += this->step;
				}
				return 1;
			}
		}
		return 0;
	}
};

//滑动开关
struct SlideButton :windowitem
{
	CString title;
	SlideButton(int columnwidth = 200, int columnheight = 80, int state = SLIDE_BUTTON_OFF) :windowitem()
	{
		width = columnwidth;
		height = columnheight;
		always_show = FALSE;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			HFONT font = ::CreateFont(27, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("宋体"));
			HFONT comdcoldfont = (HFONT)::SelectObject(hdc, font);

			HBRUSH hBrush = CreateSolidBrush(RGB(50, 50, 50));
			HBRUSH hBrush2 = CreateSolidBrush(LIGHT_BLUE_COLOR);
			HBRUSH hBrush3 = CreateSolidBrush(GREEN_COLOR);
			HPEN pen = CreatePen(PS_SOLID, 1, GREEN_COLOR);
			HPEN oldpen = (HPEN)SelectObject(hdc, pen);

			int i = 0;
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Pen pen1(Color(255, 0, 255, 0));
			Gdiplus::Font font1(&fontFamily, 25, FontStyleBold, UnitPixel);

			if (this->current_state == SLIDE_BUTTON_OFF)//如果当前状态是关闭状态
			{
				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x /*- menucurrentpos*/, this->y + fft_menu_scrool_pos, this->width, this->height);
				FillRoundRectangle(g, Color(255, 50, 50, 50), this->x /*- menucurrentpos*/, this->y + fft_menu_scrool_pos, this->width, this->height);

				DrawRoundRectange(g, Color(255, 155, 155, 155), this->x + 2 /*- menucurrentpos*/, this->y + 2 + fft_menu_scrool_pos, this->width / 2 - 4, this->height - 5);
				FillRoundRectangle(g, Color(255, 155, 155, 155), this->x + 2/* - menucurrentpos*/, this->y + 2 + fft_menu_scrool_pos, this->width / 2 - 4, this->height - 5);
				TextOut(hdc, this->x + 15 /*- menucurrentpos*/, this->y + 8 + fft_menu_scrool_pos, L"关", 1);
			}
			else//当前状态是打开状态
			{
				FillRoundRectangle(g, Color(255, 0, 255, 0), this->x /*- menucurrentpos*/, this->y + fft_menu_scrool_pos, this->width, this->height);
				DrawRoundRectange(g, Color(255, 155, 50, 50), this->x + this->width / 2 /*- menucurrentpos*/, this->y + 2 + fft_menu_scrool_pos, this->width / 2 - 4, this->height - 5);
				FillRoundRectangle(g, Color(255, 50, 50, 50), this->x + this->width / 2/* - menucurrentpos*/, this->y + 2 + fft_menu_scrool_pos, this->width / 2 - 4, this->height - 5);
				TextOut(hdc, this->x + this->width / 2 + 15 /*- menucurrentpos*/, this->y + 8 + fft_menu_scrool_pos, L"开", 1);
			}

			SelectObject(hdc, comdcoldfont);
			DeleteObject(font);
			SelectObject(hdc, oldpen);

			DeleteObject(pen);
			DeleteObject(hBrush);
			DeleteObject(hBrush2);
			DeleteObject(hBrush3);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (EVENT_LBUTTON_UP == eventtype)//如果鼠标点击了该控件的左半边，说明是要切换到关闭状态
		{
			if (x >= this->x && x <= this->x + this->width / 2 && y >= this->y + fft_menu_scrool_pos&& y <= this->y + this->height + fft_menu_scrool_pos)
			{
				this->current_state = SLIDE_BUTTON_OFF;
				return 1;
			}//如果鼠标点击了该控件的右半边，说明是要切换到关闭状态
			else if (x >= this->x + this->width / 2 && x <= this->x + this->width && y >= this->y + fft_menu_scrool_pos && y <= this->y + this->height + fft_menu_scrool_pos)
			{
				this->current_state = SLIDE_BUTTON_ON;
				return 1;
			}
		}
		return 0;
	}
};
struct SingleGrid :windowitem
{
	int child_num;
	vector<CString> child_titles;

	int column;
	int item_width;
	int item_height;
	SingleGrid(int columns = 2, int columnwidth = 100, int columnheight = 80) :windowitem()
	{
		child_num = 0;
		column = columns;
		item_width = columnwidth;
		item_height = columnheight;
		child_titles.clear();
		event_func = NULL;
		hide = FALSE;
		always_show = FALSE;
	}
	void add_item(CString newchild)
	{
		child_titles.push_back(newchild);
		child_num++;
	}
	int draw(HDC hdc)
	{
		if (this->hide == FALSE)
		{
			HFONT font = ::CreateFont(27, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("宋体"));
			HFONT comdcoldfont = (HFONT)::SelectObject(hdc, font);

			HBRUSH hBrush = CreateSolidBrush(RGB(50, 50, 50));
			HBRUSH hBrush2 = CreateSolidBrush(LIGHT_BLUE_COLOR);
			HBRUSH hBrush3 = CreateSolidBrush(GREEN_COLOR);
			HPEN pen = CreatePen(PS_SOLID, 1, RGB(155, 155, 155));
			HPEN oldpen = (HPEN)SelectObject(hdc, pen);

			int i = 0;
			Graphics g(hdc);
			StringFormat stringformat;

			SolidBrush brush(Color(255, 255, 255, 255));
			g.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			FontFamily fontFamily(L"宋体");
			Gdiplus::Pen pen1(Color(255, 0, 255, 0));
			Gdiplus::Font font1(&fontFamily, 25, FontStyleBold, UnitPixel);

			int vols = this->child_num / 2 + 1;
			int remanider = this->child_num % 2;

			for (i = 0; i < child_num; i++)
			{
				if (this->current_state == i)
				{
					RECT rec = { this->x + (i % 2)*this->width / 2 + 4 /*- menucurrentpos*/, this->y + (i / 2)*item_height + fft_menu_scrool_pos + 4,this->x - menucurrentpos + (i % 2)*this->width / 2 + this->width / 2 - 4, this->y + (i / 2)*item_height + item_height + fft_menu_scrool_pos - 4 };
					FillRect(hdc, &rec, hBrush2);
					break;
				}
			}
			for (i = 0; i < vols; i++)
			{
				MoveToEx(hdc, this->x /*- menucurrentpos*/, this->y + i * item_height + fft_menu_scrool_pos, NULL);
				LineTo(hdc, this->x /*- menucurrentpos*/ + this->width, this->y + i * item_height + fft_menu_scrool_pos);
				SizeF t;
				int w;
				if (i < vols - 1)
				{
					for (int j = 0; j < 2; j++)
					{
						t = GetTextBounds(font1, &stringformat, this->child_titles[2 * i + j]);
						w = (this->width / 2 - t.Width) / 2;
						Gdiplus::PointF point1(this->x/* - menucurrentpos */ + w + j * this->width / 2, this->y + i * item_height + 30 + fft_menu_scrool_pos);
						g.DrawString(this->child_titles[2 * i + j], -1, &font1, point1, &brush);
					}
				}
			}
			i--;
			if (remanider != 0)
			{
				Gdiplus::PointF point1(this->x /*- menucurrentpos*/ + 20 + 30, this->y + i * item_height + 30 + fft_menu_scrool_pos);
				g.DrawString(this->child_titles[2 * i], -1, &font1, point1, &brush);
			}
			if (remanider != 0)
			{
				i++;
				MoveToEx(hdc, this->x /*- menucurrentpos*/, this->y + i * item_height + fft_menu_scrool_pos, NULL);
				LineTo(hdc, this->x /*- menucurrentpos*/ + this->width, this->y + i * item_height + fft_menu_scrool_pos);
			}
			MoveToEx(hdc, this->x /*- menucurrentpos*/, this->y + fft_menu_scrool_pos, NULL);
			LineTo(hdc, this->x - menucurrentpos, this->y + i * item_height + fft_menu_scrool_pos);

			MoveToEx(hdc, this->x + this->width / 2, this->y + fft_menu_scrool_pos, NULL);
			LineTo(hdc, this->x + this->width / 2, this->y + i * item_height + fft_menu_scrool_pos);

			MoveToEx(hdc, this->x + this->width, this->y + fft_menu_scrool_pos, NULL);
			LineTo(hdc, this->x + this->width, this->y + i * item_height + fft_menu_scrool_pos);

			SelectObject(hdc, comdcoldfont);
			DeleteObject(font);
			SelectObject(hdc, oldpen);

			DeleteObject(pen);
			DeleteObject(hBrush);
			DeleteObject(hBrush2);
			DeleteObject(hBrush3);
		}
		return 1;
	}
	int event(int eventtype, int x, int y)
	{
		if (this->hide)
		{
			return 0;
		}
		int vols = this->child_num / 2 + 1;
		int remanider = this->child_num % 2;
		if (remanider != 0)
		{
			vols++;
		}
		if (x <= this->x || x >= this->x + this->width)
		{

			return 0;
		}
		if (y <= this->y + fft_menu_scrool_pos || y >= this->y + this->item_height * vols + fft_menu_scrool_pos)
		{

			return 0;
		}

		int i = 0;
		int x_index = 0;
		int y_index = 0;
		if (x >= this->x && x <= this->x + this->width / 2)
		{
			x_index = 0;
		}
		else if (x >= this->x + this->width / 2 && x <= this->x + this->width)
		{
			x_index = 1;
		}

		for (i = 0; i < vols; i++)
		{
			if (y >= this->y + i*this->item_height + fft_menu_scrool_pos && y <= this->y + (i + 1)*this->item_height + fft_menu_scrool_pos)
			{
				y_index = i;
				break;
			}
		}
		int result = 2 * y_index + x_index;
		if (result < this->child_num)
		{
			this->current_state = result;
		}
		return 1;
	}
};

vector<windowitem*> utilityfuncfftitems;
vector<windowitem*> utilityfuncpassfailitems;
vector<windowitem*> settingmenuitems;

template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

struct item
{
	CString title;
	void* subitems;
};


// Enable Visual Style
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#pragma endregion
