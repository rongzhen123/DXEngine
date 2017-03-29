#pragma once
//#ifndef DXENGINE
//#define DXENGINE
#include "resource.h"


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
#include "ShareDefine.h"
#include <vector>
#include "Common/d3dApp.h"
#include "Common/d3dx11Effect.h"
#include "Common/GeometryGenerator.h"
#include "Common/MathHelper.h"
#include "Common/LightHelper.h"
#include "Common/Waves.h"
#include "Effects.h"
#include "Vertex.h"
#include "RenderStates.h"
#include "WindowManager.h"
#include "NormalWindow.h"

using namespace std;
#define swap(x,y) int temp = x;x=y;y=temp;



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


//#endif
