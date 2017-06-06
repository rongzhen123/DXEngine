// 6022SelfCheck.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "DXEngine.h"
#include "ColorButton.h"
#include "TextControl.h"
#include "EditBox.h"
#include "GeometryGenerator.h"
#define MAX_LOADSTRING 100
ULONG_PTR m_gdiplusToken;

DXEngineApp* engineApp;
/*
ID3D11Device* md3dDevice;
ID3D11DeviceContext* md3dImmediateContext;
IDXGISwapChain* mSwapChain;
ID3D11Texture2D* mDepthStencilBuffer;
ID3D11RenderTargetView* mRenderTargetView;
ID3D11DepthStencilView* mDepthStencilView;
D3D11_VIEWPORT mScreenViewport;
*/
int set_position_x(int x)
{
	engineApp->position_x = x;
	return 0;
}
int set_position_y(int y)
{
	engineApp->position_y = y;
	return 0;
}
int set_position_z(int z)
{
	engineApp->position_z = z;
	return 0;
}
int set_scale_x(int x)
{
	engineApp->scale_x = x;
	return 0;
}
int set_scale_y(int y)
{
	engineApp->scale_y = y;
	return 0;
}
int set_scale_z(int z)
{
	engineApp->scale_z = z;
	return 0;
}
int set_plane_width(int w)
{
	CString tip;
	tip.Format(L"set_plane_width w=%d",w);
//	AfxMessageBox(tip);
	engineApp->plane_width = w;
	return 0;
}
int set_plane_depth(int d)
{
	CString tip;
	tip.Format(L"set_plane_depth d=%d", d);
	//AfxMessageBox(tip);
	engineApp->plane_depth = d;
	return 0;
}
int set_plane_m(int m)
{
	CString tip;
	tip.Format(L"set_plane_m m=%d", m);
	//AfxMessageBox(tip);
	engineApp->m = m;
	return 0;
}
int set_plane_n(int n)
{
	CString tip;
	tip.Format(L"set_plane_n n=%d", n);
	//AfxMessageBox(tip);
	engineApp->n = n;
	return 0;
}
int set_box_width(int w)
{
	engineApp->box_width = w;
	return 0;
}
int set_box_height(int h)
{
	engineApp->box_height = h;
	return 0;
}
int set_box_depth(int d)
{
	engineApp->box_depth = d;
	return 0;
}
int set_sphere_radius(int sr)
{
	engineApp->sphere_radius = sr;
	return 0;
}
int set_sphere_slice_count(int sc)
{
	engineApp->sphere_slice_count = sc;
	return 0;
}
int set_sphere_stack_count(int stc)
{
	engineApp->sphere_stack_count = stc;
	return 0;
}

int set_cylinder_top_radius(int ctr)
{
	engineApp->cylinder_top_radius = ctr;
	return 0;
}
int set_cylinder_bottom_radius(int ctr)
{
	engineApp->cylinder_bottom_radius = ctr;
	return 0;
}
int set_cylinder_slice_count(int ctr)
{
	engineApp->cylinder_slice_count = ctr;
	return 0;
}
int set_cylinder_stack_count(int ctr)
{
	engineApp->cylinder_stack_count = ctr;
	return 0;
}
DWORD DXEngineApp::MenuThread(LPVOID lParam)
{
	//DXEngineApp* engineApp = (DXEngineApp*)lParam;
	if (engineApp == NULL)
	{
		AfxMessageBox(L"MenuThread engineApp is null");
		return 1;
	}
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	HINSTANCE hInstance = engineApp->AppInst();
	WindowManager* windowManager = WindowManager::getInstance();
	windowManager->Init(hInstance);
	engineApp->toolswbar = new NormalWindow();
	engineApp->toolswbar->title = L"工具窗口";
	engineApp->toolswbar->position_x = 100;
	engineApp->toolswbar->position_y = 200;
	engineApp->toolswbar->window_height = 800;
	engineApp->toolswbar->window_width = 400;
	engineApp->toolswbar->color = RGB(255,255,255);
	engineApp->toolswbar->userdata = (void*)engineApp;
	engineApp->toolswbar->child_controls.clear();
	engineApp->toolswbar->hwnd = windowManager->RegisterWindow(engineApp->toolswbar);
	CreatePlaneButton* cpb = new CreatePlaneButton();
	cpb->x = 30;
	cpb->y = 40;
	cpb->width = 130;
	cpb->height = 50;
	cpb->title = L"平 面";
	cpb->app = engineApp;
	engineApp->toolswbar->child_controls.push_back(cpb);

	CreateBoxButton* cbb = new CreateBoxButton();
	cbb->x = 180;
	cbb->y = 40;
	cbb->width = 130;
	cbb->height = 50;
	cbb->title = L"方 体";
	cbb->app = engineApp;
	engineApp->toolswbar->child_controls.push_back(cbb);

	CreateSphereButton* chb = new CreateSphereButton();
	chb->x = 30;
	chb->y = 100;
	chb->width = 130;
	chb->height = 50;
	chb->title = L"球 体";
	chb->app = engineApp;
	engineApp->toolswbar->child_controls.push_back(chb);

	CreateCylinderButton* ccb = new CreateCylinderButton();
	ccb->x = 180;
	ccb->y = 100;
	ccb->width = 130;
	ccb->height = 50;
	ccb->title = L"圆 柱";
	ccb->app = engineApp;
	engineApp->toolswbar->child_controls.push_back(ccb);

	TextControl* tc1 = new TextControl(L"方体参数");
	tc1->x = 30;
	tc1->y = 300;
	tc1->width = 150;
	tc1->height = 40;
	tc1->font_size = 18;
	tc1->color = RGB( 60,60,60);
	tc1->owner = L"box";
	tc1->hide = TRUE;
	engineApp->toolswbar->child_controls.push_back(tc1);

	EditBox* eb_width = new EditBox();
	eb_width->x = 40;
	eb_width->y = 340;
	eb_width->width = 100;
	eb_width->height = 20;
	eb_width->title = L"长";
	eb_width->owner = L"box";
	eb_width->hide = TRUE;
	eb_width->font_size = 18;
	eb_width->text_font_size = 15;
	eb_width->text_color = RGB(10,10,10);
	eb_width->color = RGB(10, 10, 250);
	eb_width->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_width->UpdateTargetValueFunc = set_box_width;
	eb_width->content_type = Content_Type_Digit_Int;
	eb_width->Create();
	engineApp->toolswbar->child_controls.push_back(eb_width);

	EditBox* eb_depth = new EditBox();
	eb_depth->x = 40;
	eb_depth->y = 380;
	eb_depth->width = 100;
	eb_depth->height = 20;
	eb_depth->title = L"宽";
	eb_depth->owner = L"box";
	eb_depth->content_type = Content_Type_Digit_Int;
	eb_depth->hide = TRUE;
	eb_depth->font_size = 18;
	eb_depth->text_font_size = 15;
	eb_depth->text_color = RGB(10, 10, 10);
	eb_depth->color = RGB(10, 10, 250);
	eb_depth->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_depth->UpdateTargetValueFunc = set_box_depth;
	eb_depth->Create();
	engineApp->toolswbar->child_controls.push_back(eb_depth);

	EditBox* eb_height = new EditBox();
	eb_height->x = 40;
	eb_height->y = 420;
	eb_height->width = 100;
	eb_height->height = 20;
	eb_height->title = L"高";
	eb_height->owner = L"box";
	eb_height->content_type = Content_Type_Digit_Int;
	eb_height->hide = TRUE;
	eb_height->font_size = 18;
	eb_height->text_font_size = 15;
	eb_height->text_color = RGB(10, 10, 10);
	eb_height->color = RGB(10, 10, 250);
	eb_height->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_height->UpdateTargetValueFunc = set_box_height;
	eb_height->Create();
	engineApp->toolswbar->child_controls.push_back(eb_height);

	CreateBox* cb_button = new CreateBox();
	cb_button->x = 100;
	cb_button->y = 480;
	cb_button->width = 100;
	cb_button->height = 40;
	cb_button->owner = L"box";
	cb_button->title = L"创建方体";
	cb_button->hide = TRUE;
	cb_button->font_size = 18;
	cb_button->app = engineApp;
	cb_button->parent_hwnd = engineApp->toolswbar->hwnd;
	cb_button->parent = engineApp->toolswbar;
	engineApp->toolswbar->child_controls.push_back(cb_button);

	TextControl* tc11 = new TextControl(L"位置参数");
	tc11->x = 30;
	tc11->y = 170;
	tc11->width = 150;
	tc11->height = 40;
	tc11->font_size = 18;
	tc11->color = RGB(60, 60, 60);
	tc11->owner = L"create_common";
	engineApp->toolswbar->child_controls.push_back(tc11);

	TextControl* tc12 = new TextControl(L"Position");
	tc12->x = 20;
	tc12->y = 210;
	tc12->width = 150;
	tc12->height = 40;
	tc12->font_size = 16;
	tc12->color = RGB(10, 10, 250);
	tc12->owner = L"create_common";
	engineApp->toolswbar->child_controls.push_back(tc12);

	EditBox* position_x = new EditBox();
	position_x->x = 100;
	position_x->y = 210;
	position_x->width = 50;
	position_x->height = 20;
	position_x->ref_pos = 20;
	position_x->title = L"X";
	position_x->owner = L"create_common";
	position_x->content_type = Content_Type_Digit_Int;
	position_x->font_size = 16;
	position_x->text_font_size = 15;
	position_x->text_color = RGB(10, 10, 10);
	position_x->color = RGB(10, 10, 250);
	position_x->UpdateTargetValueFunc = set_position_x;
	position_x->parent_hwnd = engineApp->toolswbar->hwnd;
	position_x->Create();
	engineApp->toolswbar->child_controls.push_back(position_x);

	EditBox* position_y = new EditBox();
	position_y->x = 180;
	position_y->y = 210;
	position_y->width = 50;
	position_y->height = 20;
	position_y->ref_pos = 20;
	position_y->title = L"Y";
	position_y->owner = L"create_common";
	position_y->content_type = Content_Type_Digit_Int;
	position_y->font_size = 16;
	position_y->text_font_size = 15;
	position_y->text_color = RGB(10, 10, 10);
	position_y->color = RGB(10, 10, 250);
	position_y->UpdateTargetValueFunc = set_position_y;
	position_y->parent_hwnd = engineApp->toolswbar->hwnd;
	position_y->Create();
	engineApp->toolswbar->child_controls.push_back(position_y);

	EditBox* position_z = new EditBox();
	position_z->x = 260;
	position_z->y = 210;
	position_z->width = 50;
	position_z->height = 20;
	position_z->ref_pos = 20;
	position_z->title = L"Z";
	position_z->owner = L"create_common";
	position_z->content_type = Content_Type_Digit_Int;
	position_z->font_size = 16;
	position_z->text_font_size = 15;
	position_z->text_color = RGB(10, 10, 10);
	position_z->color = RGB(10, 10, 250);
	position_z->UpdateTargetValueFunc = set_position_z;
	position_z->parent_hwnd = engineApp->toolswbar->hwnd;
	position_z->Create();
	engineApp->toolswbar->child_controls.push_back(position_z);

	TextControl* tc2 = new TextControl(L"平面参数");
	tc2->x = 30;
	tc2->y = 330;
	tc2->width = 150;
	tc2->height = 40;
	tc2->font_size = 18;
	tc2->color = RGB(60, 60, 60);
	tc2->owner = L"plane";
	engineApp->toolswbar->child_controls.push_back(tc2);

	EditBox* eb_plane_width = new EditBox();
	eb_plane_width->x = 40;
	eb_plane_width->y = 370;
	eb_plane_width->width = 100;
	eb_plane_width->height = 20;
	eb_plane_width->title = L"长";
	eb_plane_width->owner = L"plane";
	eb_plane_width->content_type = Content_Type_Digit_Int;
	eb_plane_width->font_size = 18;
	eb_plane_width->text_font_size = 15;
	eb_plane_width->text_color = RGB(10, 10, 10);
	eb_plane_width->color = RGB(10, 10, 250);
	eb_plane_width->UpdateTargetValueFunc = set_plane_width;
	eb_plane_width->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_plane_width->Create();
	engineApp->toolswbar->child_controls.push_back(eb_plane_width);

	EditBox* eb_plane_depth = new EditBox();
	eb_plane_depth->x = 40;
	eb_plane_depth->y = 410;
	eb_plane_depth->width = 100;
	eb_plane_depth->height = 20;
	eb_plane_depth->title = L"宽";
	eb_plane_depth->owner = L"plane";
	eb_plane_depth->content_type = Content_Type_Digit_Int;
	eb_plane_depth->font_size = 18;
	eb_plane_depth->text_font_size = 15;
	eb_plane_depth->text_color = RGB(10, 10, 10);
	eb_plane_depth->color = RGB(10, 10, 250);
	eb_plane_depth->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_plane_depth->UpdateTargetValueFunc = set_plane_depth;
	eb_plane_depth->Create();
	engineApp->toolswbar->child_controls.push_back(eb_plane_depth);

	EditBox* eb_plane_width_divide = new EditBox();
	eb_plane_width_divide->x = 40;
	eb_plane_width_divide->y = 450;
	eb_plane_width_divide->width = 100;
	eb_plane_width_divide->height = 20;
	eb_plane_width_divide->title = L"列数";
	eb_plane_width_divide->owner = L"plane";
	eb_plane_width_divide->content_type = Content_Type_Digit_Int;
	eb_plane_width_divide->font_size = 18;
	eb_plane_width_divide->text_font_size = 15;
	eb_plane_width_divide->text_color = RGB(10, 10, 10);
	eb_plane_width_divide->color = RGB(10, 10, 250);
	eb_plane_width_divide->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_plane_width_divide->UpdateTargetValueFunc = set_plane_m;
	eb_plane_width_divide->Create();
	engineApp->toolswbar->child_controls.push_back(eb_plane_width_divide);

	EditBox* eb_plane_depth_divide = new EditBox();
	eb_plane_depth_divide->x = 40;
	eb_plane_depth_divide->y = 490;
	eb_plane_depth_divide->width = 100;
	eb_plane_depth_divide->height = 20;
	eb_plane_depth_divide->title = L"行数";
	eb_plane_depth_divide->owner = L"plane";
	eb_plane_depth_divide->content_type = Content_Type_Digit_Int;
	eb_plane_depth_divide->font_size = 18;
	eb_plane_depth_divide->text_font_size = 15;
	eb_plane_depth_divide->text_color = RGB(10, 10, 10);
	eb_plane_depth_divide->color = RGB(10, 10, 250);
	eb_plane_depth_divide->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_plane_depth_divide->UpdateTargetValueFunc = set_plane_n;
	eb_plane_depth_divide->Create();
	engineApp->toolswbar->child_controls.push_back(eb_plane_depth_divide);

	CreatePlane* cp_button = new CreatePlane();
	cp_button->x = 90;
	cp_button->y = 540;
	cp_button->width = 120;
	cp_button->height = 40;
	cp_button->owner = L"plane";
	cp_button->title = L"创建平面";
	//cp_button->hide = TRUE;
	cp_button->font_size = 18;
	cp_button->parent_hwnd = engineApp->toolswbar->hwnd;
	cp_button->app = engineApp;
	cp_button->parent = engineApp->toolswbar;
	engineApp->toolswbar->child_controls.push_back(cp_button);

	windowManager->MessageLoop();
	GdiplusShutdown(m_gdiplusToken);
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	DXEngineApp theApp(hInstance);
	if (!theApp.Init())
	{
		return 0;
	}
	engineApp = &theApp;
	theApp.m_MenuThread = CreateThread(NULL, 0, DXEngineApp::MenuThread, (LPVOID)&theApp, 0, NULL);
	if (theApp.m_MenuThread == NULL)
	{
		MessageBox(NULL, L"创建菜单线程失败！", L"Error", MB_ICONERROR);
		return FALSE;
	}
	theApp.Run();
	return 1;
}


DXEngineApp::DXEngineApp(HINSTANCE hInstance)
	: D3DApp(hInstance),
	mWaterTexOffset(0.0f, 0.0f), mEyePosW(0.0f, 0.0f, 0.0f), mLandIndexCount(0), mRenderOptions(RenderOptions::TexturesAndFog),
	mTheta(1.3f*MathHelper::Pi), mPhi(0.4f*MathHelper::Pi), mRadius(80.0f)
{
	mMainWndCaption = L"Blend Demo";
	mEnable4xMsaa = false;

	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	mCam.SetPosition(0.0f, 2.0f, -15.0f);

	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mLandWorld, I);
	XMStoreFloat4x4(&mWavesWorld, I);
	XMStoreFloat4x4(&mView, I);
	XMStoreFloat4x4(&mProj, I);

	XMMATRIX boxScale = XMMatrixScaling(15.0f, 15.0f, 15.0f);
	XMMATRIX boxOffset = XMMatrixTranslation(8.0f, 5.0f, -15.0f);
	XMStoreFloat4x4(&mBoxWorld, boxScale*boxOffset);

	XMMATRIX grassTexScale = XMMatrixScaling(5.0f, 5.0f, 0.0f);
	XMStoreFloat4x4(&mGrassTexTransform, grassTexScale);

	mDirLights[0].Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mDirLights[0].Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mDirLights[0].Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mDirLights[0].Direction = XMFLOAT3(0.57735f, -0.57735f, 0.57735f);

	mDirLights[1].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[1].Diffuse = XMFLOAT4(0.20f, 0.20f, 0.20f, 1.0f);
	mDirLights[1].Specular = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
	mDirLights[1].Direction = XMFLOAT3(-0.57735f, -0.57735f, 0.57735f);

	mDirLights[2].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[2].Diffuse = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mDirLights[2].Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[2].Direction = XMFLOAT3(0.0f, -0.707f, -0.707f);

	mLandMat.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mLandMat.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mLandMat.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f);

	mWavesMat.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mWavesMat.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	mWavesMat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 32.0f);

	mBoxMat.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mBoxMat.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mBoxMat.Specular = XMFLOAT4(0.4f, 0.4f, 0.4f, 16.0f);

	//创建几何体相关参数
	 plane_width = plane_depth = m = n = 0;
	 box_width = box_height = box_depth = 0;
	 sphere_radius = sphere_slice_count = sphere_stack_count = 0;
	 cylinder_top_radius = cylinder_bottom_radius = cylinder_slice_count = cylinder_stack_count = 0;

	 mRenderQueue.clear();
}

DXEngineApp::~DXEngineApp()
{
	md3dImmediateContext->ClearState();
	mRenderQueue.clear();

	Effects::DestroyAll();
	//InputLayouts::DestroyAll();
	//RenderStates::DestroyAll();
}

bool DXEngineApp::Init()
{
	if (!D3DApp::Init())
		return false;
	
	Effects::InitAll(md3dDevice);
/*
	mWaves.Init(160, 160, 1.0f, 0.03f, 5.0f, 0.3f);
	// Must init Effects first since InputLayouts depend on shader signatures.
	InputLayouts::InitAll(md3dDevice);
	RenderStates::InitAll(md3dDevice);

	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice,L"Textures/grass.dds", 0, 0, &mGrassMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice,L"Textures/circle011.dds", 0, 0, &mWavesMapSRV, 0));
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice,L"Textures/circle011.dds", 0, 0, &mBoxMapSRV, 0));
	//BuildLandGeometryBuffers();
	//BuildWaveGeometryBuffers();
	//BuildCrateGeometryBuffers();
	*/
	return true;
}

void DXEngineApp::OnResize()
{
	D3DApp::OnResize();

	mCam.SetLens(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
}

void DXEngineApp::UpdateScene(float dt)
{
	// Control the camera.
	if (GetAsyncKeyState('W') & 0x8000)
		mCam.Walk(10.0f*dt);

	if (GetAsyncKeyState('S') & 0x8000)
		mCam.Walk(-10.0f*dt);

	if (GetAsyncKeyState('A') & 0x8000)
		mCam.Strafe(-10.0f*dt);

	if (GetAsyncKeyState('D') & 0x8000)
		mCam.Strafe(10.0f*dt);
}

void DXEngineApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Black));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	mCam.UpdateViewMatrix();

	XMMATRIX view = mCam.View();
	XMMATRIX proj = mCam.Proj();
	XMMATRIX viewProj = mCam.ViewProj();

	for (unsigned int i = 0; i < mRenderQueue.size(); i++)
	{
		XMMATRIX world = XMMatrixIdentity();// XMMatrixTranslation(1.0f, 1.5f, 1.0f);
		XMMATRIX worldViewProj =world *viewProj;
		mRenderQueue[i]->mEffectWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));
		UINT stride = mRenderQueue[i]->mVertexStride;
		UINT offset = 0;
		md3dImmediateContext->IASetInputLayout(mRenderQueue[i]->mInputLayout);
		md3dImmediateContext->IASetVertexBuffers(0, 1, &mRenderQueue[i]->mVB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(mRenderQueue[i]->mIB, DXGI_FORMAT_R32_UINT, 0);
		D3DX11_TECHNIQUE_DESC techDesc;
		mRenderQueue[i]->mEffectTech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			mRenderQueue[i]->mEffectTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
			md3dImmediateContext->DrawIndexed(mRenderQueue[i]->m_Indices.size(), 0, 0);
		}
	}

	HR(mSwapChain->Present(0, 0));
}
float DXEngineApp::GetHillHeight(float x, float z)const
{
	return 0.3f*(z*sinf(0.1f*x) + x*cosf(0.1f*z));
}

void DXEngineApp::SetupPlane(int width, int depth, int m, int n)
{
	CString tip;
	tip.Format(L"SetupPlane width=%d,depth=%d,m=%d,n=%d",width,depth,m,n);
	//AfxMessageBox(tip);
	GeometryGenerator geoGen;
	GeometryGenerator::MeshData plane;
	
	geoGen.CreateGrid(width, depth, m, n, plane);
	
	ManualMesh_Color* mesh1 = new ManualMesh_Color(Plane);
	mesh1->Init(md3dDevice,plane,Effects::mEffectPosColor, Effects::mEffectTechPosColor, Effects::mInputLayout_PosColor,Effects::mEffectWorldViewProj_PosColor,Effects::mRS,Effects::mBS);
	mRenderQueue.push_back(mesh1);
}

void DXEngineApp::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void DXEngineApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void DXEngineApp::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		mCam.Pitch(dy);
		mCam.RotateY(dx);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}

void DXEngineApp::SetupBox(int width, int height, int depth)
{

}

void DXEngineApp::SetupSphere(int radius, int slicecount, int stackcount)
{

}

void DXEngineApp::SetupCylinder(int topradius, int bottomradius, int slicecount, int stackcount)
{

}
