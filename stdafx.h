// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#if !defined(AFX_STDAFX_H__B94F470C_7337_48FF_917D_61335175551B__INCLUDED_)
#define AFX_STDAFX_H__B94F470C_7337_48FF_917D_61335175551B__INCLUDED_

//#undef _DEBUG


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxmt.h>
#endif
#include "Shlwapi.h"
#pragma comment(lib,"Shlwapi.lib")

#include "assert.h"
#include  <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include "GdiPlus.h" 
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>
#define OFFSET_X 5	//画圆角矩形是圆角的X方向半径
#define OFFSET_Y 5

#define SLIDE_BUTTON_ON 1	//自定义的滑块控件的两种状态
#define SLIDE_BUTTON_OFF 0

#define UPDATE_CURRENT_STATE_TIMER 1
#define ERROR_UPDATE_TIMER 2

#define EVENT_LBUTTON_UP 1	//自定义的控件事件类型
#define EVENT_LBUTTON_DOWN 2
#define EVENT_MOUSEMOVE 3
#define EVENT_MOUSEOUT_UP 4 //鼠标松开
typedef float Real;



typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int int32;
typedef short int16;
typedef signed char int8;
typedef unsigned __int64 uint64;
typedef __int64 int64;

enum  control_type
{
	Title,//静态文本，不自动换行
	MultiString,//多行文本，可以自动换行
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
};

enum Edit_Text_Align_Type
{
	Align_LEFT,//居中对齐
	Align_RIGHT,	//居左对齐
	Align_LEFT_TOP,	//右对齐
	Align_RIGHT_TOP
};

enum Content_Type
{
	Content_Type_Any,//任意
	Content_Type_Digit_Int,//整数
	Content_Type_Digit_Float,//小数
	Content_Type_Alphabet//字母
};

enum  ToastLevel
{
	LEVEL_TIP,//该级别的消息停留一定的时间后会自动消失
	LEVEL_WARNNING,
	LEVEL_ERROR	//该级别的消息需要用户点击才能消失
};
struct Toast//窗口提示消息
{
	int content_id;
	ToastLevel	Level;//消息级别
};

enum MSG_USER
{
	MSG_USER_MSG_BOX = (WM_USER + 101),
	MSG_USER_SET_CH_COUPLING,
	MSG_USER_SET_CH_PROBE,
	MSG_USER_SET_CH_COLOR,
	MSG_USER_SET_TIMEBASE,
	MSG_USER_INVALIDATE_VIEW
};

struct ManualMeshParameter
{
	float position_x, position_y, position_z;
	float scale_x, scale_y, scale_z;
	float rotation_x, rotation_y, rotation_z;
	uint16 color_r, color_g, color_b, color_a;
	std::wstring texture_filename;
	ManualMeshParameter()
	{
		position_x = position_y = position_z = 0;
		scale_x = scale_y = scale_z = 1;
		rotation_x = rotation_y = rotation_z = 1;
		texture_filename = L"";
		color_r = color_g = color_b = color_a = 0;
	}
	void Reset()
	{
		position_x = position_y = position_z = 0;
		scale_x = scale_y = scale_z = 1;
		rotation_x = rotation_y = rotation_z = 1;
		texture_filename = L"";
		color_r = color_g = color_b = color_a = 0;
	}
};
#define MAX_REC_SIZE		512

#define NUMVIEWS			40

/*
*SCPI 搜索设备表达式
*
*/
//"USB?*INSTR";
#define SEARCH_USB_DEVICE_EXPR	"USB[0-9]*::?*::INSTR"	//Hantek USB连接的手持频谱分析仪
#define SEARCH_LAN_DEVICE_EXPR	"TCPIP[0-9]*::?*::5025::SOCKET" //"TCPIP0::?*::5025::SOCKET"	//_T("TCPIP0::anolis.local.::5025::SOCKET");

//
#define INPUT_R 				50.0 	// 输入阻抗
#define MAX_RECIVE_BUF_SIZE		10240//最大接收缓冲区
#define MAX_LAN_PACKAGE_SIZE	1024//参考Aglient Visa，每个包1024个字节 

enum _COMM_TYPE
{
	COMM_TYPE_USB = 0,
	COMM_TYPE_LAN,
	COMM_TYPE_NUM
};


enum _CATEGORY
{
	CATEGORY_PRODUCT = 0,
	CATEGORY_CHECK,
	CATEGORY_REPAIR,
	CATEGORY_QUERY,
	CATEGORY_MANAGE,
	CATEGORY_ACCOUNT,
	CATEGORY_OUTSTOCK,
};

enum _OTHERS
{
	OTHERS_1 = 0,
	OTHERS_2,
	OTHERS_3,
	OTHERS_4,
	OTHERS_NUM,
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

