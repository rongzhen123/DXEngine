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
#include "Common/Camera.h"
#include "Effects.h"
#include "Vertex.h"
#include "RenderStates.h"
#include "WindowManager.h"
#include "NormalWindow.h"
#include "Renderable.h"
#include "SceneManager.h"
using namespace std;

enum RenderOptions
{
	Lighting = 0,
	Textures = 1,
	TexturesAndFog = 2
};

class DXEngineApp : public D3DApp
{
public:
	NormalWindow* toolswbar;
public:
	DXEngineApp(HINSTANCE hInstance);
	~DXEngineApp();

	SceneManager* mSceneMgr;
	static int m_NumberPlaneCreated;
	static int m_NumberBoxCreated;
	static int m_NumberSphereCreated;
	static int m_NumberCylinderCreated;
	static int m_NumberStaticMeshCreated;
	static int m_NumberSkinnedMeshCreated;
	static int m_NumberNodeCreated;
	HANDLE m_MenuThread;//具体检测的线程
	HWND m_MenuHwnd;
	bool Init();
	//void SetUpToolWindows();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();
	void DrawBackground();
	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);

	//创建几何体相关参数
	int position_x, position_y, position_z;
	float scale_x, scale_y, scale_z;
	float rotation_x, rotation_y, rotation_z;
//	float scale_x, scale_y, scale_z;
	int plane_width, plane_depth, m, n;
	int box_width, box_height, box_depth;
	int sphere_radius, sphere_slice_count, sphere_stack_count;
	int cylinder_top_radius, cylinder_bottom_radius, cylinder_slice_count, cylinder_stack_count;
	int color_r, color_g, color_b,color_a;
	CString texture_filename;
	void SetupPlane(int width,int depth,int m,int n,float posx,float posy,float posz,float scalex,float scaley,float scalez);
	void SetupBox(int width,int height,int depth);
	void SetupSphere(int radius,int slicecount,int stackcount);
	void SetupCylinder(int topradius,int bottomradius,int slicecount,int stackcount);
	float GetHillHeight(float x, float z)const;
	//vector<Renderable*> mRenderQueue;
	static DWORD WINAPI MenuThread(LPVOID lParam);//线程函数;

private:
	Camera mCam;
	DirectionalLight mDirLights[3];
	Material mLandMat;
	Material mWavesMat;
	Material mBoxMat;

	XMFLOAT4X4 mGrassTexTransform;
	XMFLOAT4X4 mWaterTexTransform;
	XMFLOAT4X4 mLandWorld;
	XMFLOAT4X4 mWavesWorld;
	XMFLOAT4X4 mBoxWorld;

	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;
	UINT mLandIndexCount;
	XMFLOAT2 mWaterTexOffset;
	RenderOptions mRenderOptions;
	XMFLOAT3 mEyePosW;
	float mTheta;
	float mPhi;
	float mRadius;
	POINT mLastMousePos;
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


//#endif
