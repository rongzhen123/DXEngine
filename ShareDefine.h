/*
//与DLL共享自定义全局变量或宏
*/
#pragma once

#ifdef DSO1092
	#define DELETE_20MV		//删除20mV档
#endif

#ifdef PENDSO
	#define ATT_X10	//有10倍衰减
#endif

//
#define BUF_LEN_DEL				1024	
#define BUF_LEN_1K				(1024 - 8)
#define BUF_LEN_2K				(2048 - 16)
#define BUF_LEN_1M				(1048576 - BUF_LEN_DEL)
#define BUF_LEN_512K			(524288 - BUF_LEN_DEL)
#define BUF_LEN_256K			(262144 - BUF_LEN_DEL)
#define BUF_LEN_128K			(131072 - BUF_LEN_DEL)



//
#define MAX_DRIVER_NAME			64			//最大设备名称长度
#define USB_PACK_SIZE			2097152		//USB上传数据包大小
#define CMD_BUFFER_LEN			84			//LA命令缓冲区的长度
#define FFT_DATA_LEN			512			//FFT数据长度
//
#define VERTICAL_8BIT		8

#ifdef VERTICAL_8BIT
	#define MIN_DATA		0
	#define MID_DATA		128
	#define MAX_DATA		255
	#define F127_DATA		-127
#endif

#define MAX_HORI_POS		100	//
//物理通道个数.../////////////////////////////////////////////////////////
typedef enum ENUM_CH_NUM{
	CH1 = 0,
	CH2,
	MAX_CH_NUM
};

//VoltDIV
#ifdef ATT_X10
	typedef enum ENUM_VOLTDIV{
		VOLTDIV_20MV = 0,
		VOLTDIV_50MV,
		VOLTDIV_100MV,
		VOLTDIV_200MV,
		VOLTDIV_500MV,
		VOLTDIV_1V,
		VOLTDIV_2V,
		VOLTDIV_5V,
		VOLTDIV_10V,
		VOLTDIV_20V,
		VOLTDIV_NUM
	};
#else
	#ifdef DELETE_20MV
	typedef enum ENUM_VOLTDIV{
		VOLTDIV_20MV = 0,
		VOLTDIV_50MV = 0,
		VOLTDIV_100MV,
		VOLTDIV_200MV,
		VOLTDIV_500MV,
		VOLTDIV_1V,
		VOLTDIV_2V,
		VOLTDIV_5V,
		VOLTDIV_NUM
	};
	#else
	typedef enum ENUM_VOLTDIV{
		VOLTDIV_20MV = 0,
		VOLTDIV_50MV,
		VOLTDIV_100MV,
		VOLTDIV_200MV,
		VOLTDIV_500MV,
		VOLTDIV_1V,
		VOLTDIV_2V,
		VOLTDIV_5V,
		VOLTDIV_NUM
	};
	#endif
#endif

typedef enum ENUM_VOLTDIV_FFT{
	FFT_VOLTDIV_1MV = 0,
	FFT_VOLTDIV_2MV,
	FFT_VOLTDIV_5MV,
	FFT_VOLTDIV_10MV,
	FFT_VOLTDIV_20MV,
	FFT_VOLTDIV_50MV,
	FFT_VOLTDIV_100MV,
	FFT_VOLTDIV_200MV,
	FFT_VOLTDIV_500MV,
	FFT_VOLTDIV_1V,
	FFT_VOLTDIV_2V,
	FFT_VOLTDIV_5V,
	FFT_VOLTDIV_NUM
};

typedef enum ENUM_DBDIV_FFT{
	FFT_DBDIV_1DB = 0,
	FFT_DBDIV_2DB,
	FFT_DBDIV_5DB,
	FFT_DBDIV_10DB,
	FFT_DBDIV_20DB,
	FFT_DBDIV_50DB,
	FFT_DBDIV_100DB,
	FFT_DBDIV_NUM,
};

//TimeDIV
typedef enum ENUM_TIMEDIV{
	TIMEDIV_1ns = 0,
	TIMEDIV_2ns,
	TIMEDIV_5ns,
	TIMEDIV_10ns,
	TIMEDIV_20ns,
	TIMEDIV_50ns,
	TIMEDIV_100ns,
	TIMEDIV_200ns,
	TIMEDIV_500ns,
	TIMEDIV_1us,
	TIMEDIV_2us,
	TIMEDIV_5us,
	TIMEDIV_10us,
	TIMEDIV_20us,
	TIMEDIV_50us,
	TIMEDIV_100us,
	TIMEDIV_200us,
	TIMEDIV_500us,
	TIMEDIV_1ms,
	TIMEDIV_2ms,
	TIMEDIV_5ms,
	TIMEDIV_10ms,
	TIMEDIV_20ms,
	TIMEDIV_50ms,
	TIMEDIV_100ms,
	TIMEDIV_200ms,
	TIMEDIV_500ms,
	TIMEDIV_1s,
	TIMEDIV_2s,
	TIMEDIV_5s,
	TIMEDIV_10s,
	TIMEDIV_20s,
	TIMEDIV_50s,
	TIMEDIV_100s,
	TIMEDIV_200s,
	TIMEDIV_500s,
	TIMEDIV_1000s,
	TIMEDIV_2000s,
	TIMEDIV_5000s,
	TIMEDIV_NUM
};

//...//////////////////////////////////////////////////////////////////////////////////////////////////////////


//设置参数宏
typedef enum ENUM_YTMODE{
	YT_NORMAL = 0,
	YT_SCAN,
	YT_ROLL,
	YTMODE_NUM
};

typedef enum ENUM_HORI_FORMAT{
	HORI_FORMAT_YT = 0,
	HORI_FORMAT_XY,
	HORI_FORMAT_NUM
};

typedef enum ENUM_ENABLE{
	ENABLE_OFF = 0,
	ENABLE_ON,
	ENABLE_NUM
};

typedef enum ENUM_COUPLING{
	DC = 0,
	AC,
	GND,
	COUPLING_NUM
};

typedef enum ENUM_PROBE{
	X1 = 0,
	X10,
	X100,
	X1000,
	X10000,
	PROBE_NUM
};

typedef enum ENUM_TRIG_MODE{
	TRIG_MODE_EDGE = 0,
	TRIG_MODE_PULSE,
	TRIG_MODE_NUM
};

typedef enum ENUM_TRIG_SWEEP{
	TRIG_SWEEP_AUTO = 0,
	TRIG_SWEEP_NORMAL,
	TRIG_SWEEP_SINGLE,
	TRIG_SWEEP_NUM
};

typedef enum ENUM_TRIG_SRC{
	TRIG_SRC_CH1 = 0,
	TRIG_SRC_CH2,
	TRIG_SRC_NUM
};

typedef enum ENUM_TRIG_SLOPE{
	TRIG_SLOPE_RISE = 0,
	TRIG_SLOPE_FALL,
	TRIG_SLOPE_NUM
};

typedef enum ENUM_CURSOR_TYPE{
	CURSOR_TYPE_NONE = 0,
	CURSOR_TYPE_CROSS,
	CURSOR_TYPE_TRACE,
	CURSOR_TYPE_VERTICAL,
	CURSOR_TYPE_HORIZONTAL,
	CURSOR_TYPE_NUM
};

typedef enum ENUM_DIS_TYPE{
	DIS_TYPE_LINE = 0,
	DIS_TYPE_DOT
};

typedef enum ENUM_SAVE_FILE{
	SAVE_FILE_DATA = 0,
	SAVE_FILE_SETUP,
	SAVE_FILE_NUM
};

typedef enum ENUM_SAVE_FILE_TYPE{
	SAVE_FILE_TXT = 0,
	SAVE_FILE_DOC,
	SAVE_FILE_XLS,
	SAVE_FILE_CSV,
	SAVE_FILE_REF,
	SAVE_FILE_WMS,
	SAVE_FILE_BMP,
	SAVE_FILE_JPG,
	SAVE_FILE_TYPE_NUM
};

typedef enum ENUM_MATH{
	MATH_ADD = 0,
	MATH_SUB,
	MATH_MUL,
	MATH_DIV,
	MATH_FFT
};

typedef enum ENUM_FFT_HORI{
	FFT_HORI_X1 = 0,
	FFT_HORI_X2,
	FFT_HORI_X5,
	FFT_HORI_X10,
	FFT_HORI_NUM
};

typedef enum ENUM_FFT_WIN{
	FFT_WIN_RECTANGLE = 0,
	FFT_WIN_HANNING,
	FFT_WIN_HAMMING,
	FFT_WIN_BLACKMAN,
	FFT_WIN_NUM
};

typedef enum ENUM_FFT_SCALE{
	FFT_SCALE_VRMS = 0,
	FFT_SCALE_DBRMS,
	FFT_SCALE_NUM
};

typedef enum ENUM_INSERT_MODE{
	INSERT_MODE_STEP = 0,
	INSERT_MODE_LINE,
	INSERT_MODE_SIN,
	INSERT_MODE_NUM
};

typedef enum ENUM_STATUS{
	STATUS_RUN = 0,
	STATUS_STOP,
	STATUS_AUTO,
	STATUS_WAIT,
	STATUS_TRIG,
	STATUS_NUM
};
//For Display...//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define V_GRID_NUM					8//垂直8个大格
#define H_GRID_NUM					10//水平10个大格
//color
#define BLACK_COLOR					RGB(0,0,0)			//黑色
#define DEEPGRAY_COLOR				RGB(50,50,50)		//深灰色
#define WHITE_COLOR					RGB(255,255,255)	//白色
#define GREEN_COLOR					RGB(0,255,0)		//绿色
#define YELLOW_COLOR				RGB(255,255,0)		//黄色
#define BLUE_COLOR					RGB(0,0,200)		//蓝色
#define SKY_COLOR					RGB(0,255,255)		//天蓝色
#define BROWN_COLOR					RGB(255,128,0)		//棕色
#define XY_COLOR					RGB(0,218,236)
#define FRENCHGRAY_COLOR			RGB(155,155,155)	//浅灰色
#define PURPLE_COLOR				RGB(128,0,255)		//紫色
#define RED_COLOR					RGB(255,0,0)		//红色

#define MATH_COLOR					PURPLE_COLOR

//space
#define MIN_EACH_SIGNAL_HEIGHT			20	//每个信号的最小高度
#define SCALE_TEXT_HEIGHT				20	//屏幕顶端刻度文字的高度
#define SCALE_HEIGHT					15	//屏幕顶端刻度线的高度

typedef enum ENUM_DIRECTION{
	DIR_LEFT = 0,
	DIR_RIGHT,
	DIR_TOP,
	DIR_BOTTOM,
};
//...//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define STYLE_DIGITAL			0	//数字信号
#define STYEL_ANALOG			1	//模拟信号

//For control...//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define STATE_STOP				0	//暂停
#define STATE_RUN				1	//运行中


//...//////////////////////////////////////////////////////////////////////////////////////////////////////////
//引脚定义
enum ENUM_LOGIC_PIN{
	 D0 = 0,
	 D1,
	 D2,
	 D3,
	 D4,
	 D5,
	 D6,
	 D7,
	 D8,
	 D9,
	 D10,
	 D11,
	 D12,
	 D13,
	 D14,
	 D15,
	 D16,
	 D17,
	 D18,
	 D19,
	 D20,
	 D21,
	 D22,
	 D23,
	 D24,
	 D25,
	 D26,
	 D27,
	 D28,
	 D29,
	 D30,
	 D31
};


//上排引脚定义A
#define A1			D0
#define A2			D2
#define A3			D4
#define A4			D6
#define A5			D8
#define A6			D10
#define A7			D12
#define A8			D14
#define A9			D16
#define A10			D18
#define A11			D20
#define A12			D22
#define A13			D24
#define A14			D26
#define A15			D28
#define A16			D30

//下排引脚定义B
#define B1			D1
#define B2			D3
#define B3			D5
#define B4			D7
#define B5			D9
#define B6			D11
#define B7			D13
#define B8			D15
#define B9			D17
#define B10			D19
#define B11			D21
#define B12			D23
#define B13			D25
#define B14			D27
#define B15			D29
#define B16			D31

typedef struct STRUCT_LOGIC_TRIG{
	ULONG Equ_Sh;//触发器前端跳变触发设置 Sh为位屏蔽；Dat为给定数据；So为数据选择
	ULONG Equ_Dat;//触发器前端跳变触发设置 Sh为位屏蔽；Dat为给定数据；So为数据选择
	USHORT Equ_So;//触发器前端跳变触发设置 Sh为位屏蔽；Dat为给定数据；So为数据选择
	USHORT Clk_Num;//当需要使用沿触发时，Clk_Num选择从0到31的任意一路探头信号作为沿的来源
	USHORT Edg;	//当需要沿触发时，Edg设置所需的沿。
				//  0：上升沿
				//  1：下降沿
				//  2：上升或下降沿
				// 3：组合触发（与沿无关就可以触发，不需要沿同步时选择该参数
	ULONG Range_Max;	//当需要根据特定数据触发时，设置数据触发中的数据范围。
	ULONG Range_Min;	//Num为0时设置触发器A，为1时设置触发器B。
	ULONG Range_Sh;		//Max为区间最大值；Min为区间最小值；Sh为位屏蔽设置，该数值二进制的某一位为0屏蔽该位，为1时则参与比较。
	USHORT Range_Mo;	//Mo为比较方法：
						//	 00 ：D=Max 时触发           
						//	 01 ：D=Max  or  D=Min  时触发
						//	 10 ：D>Max  or  D<Min  时触发
						//	 11 ：Max>D>Min 时触发
	ULONG Time_Max;
	ULONG Time_Min;
	USHORT Time_Mo;
	//
	bool Intr_Equ;
	bool Intr_Time;
	bool Intr_Range;


}TRIG,*PTRIG;



