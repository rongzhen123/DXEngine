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


/*
ID3D11Device* md3dDevice;
ID3D11DeviceContext* md3dImmediateContext;
IDXGISwapChain* mSwapChain;
ID3D11Texture2D* mDepthStencilBuffer;
ID3D11RenderTargetView* mRenderTargetView;
ID3D11DepthStencilView* mDepthStencilView;
D3D11_VIEWPORT mScreenViewport;
*/


DWORD DXEngineApp::MenuThread(LPVOID lParam)
{
	DXEngineApp* engineApp = (DXEngineApp*)lParam;
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
	eb_width->Create();
	engineApp->toolswbar->child_controls.push_back(eb_width);
	
	EditBox* eb_depth = new EditBox();
	eb_depth->x = 40;
	eb_depth->y = 380;
	eb_depth->width = 100;
	eb_depth->height = 20;
	eb_depth->title = L"宽";
	eb_depth->owner = L"box";
	eb_depth->hide = TRUE;
	eb_depth->font_size = 18;
	eb_depth->text_font_size = 15;
	eb_depth->text_color = RGB(10, 10, 10);
	eb_depth->color = RGB(10, 10, 250);
	eb_depth->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_depth->Create();
	engineApp->toolswbar->child_controls.push_back(eb_depth);

	EditBox* eb_height = new EditBox();
	eb_height->x = 40;
	eb_height->y = 420;
	eb_height->width = 100;
	eb_height->height = 20;
	eb_height->title = L"高";
	eb_height->owner = L"box";
	eb_height->hide = TRUE;
	eb_height->font_size = 18;
	eb_height->text_font_size = 15;
	eb_height->text_color = RGB(10, 10, 10);
	eb_height->color = RGB(10, 10, 250);
	eb_height->parent_hwnd = engineApp->toolswbar->hwnd;
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
	cb_button->parent_hwnd = engineApp->toolswbar->hwnd;
	engineApp->toolswbar->child_controls.push_back(cb_button);

	TextControl* tc2 = new TextControl(L"平面参数");
	tc2->x = 30;
	tc2->y = 300;
	tc2->width = 150;
	tc2->height = 40;
	tc2->font_size = 18;
	tc2->color = RGB(60, 60, 60);
	tc2->owner = L"plane";
	engineApp->toolswbar->child_controls.push_back(tc2);

	EditBox* eb_plane_width = new EditBox();
	eb_plane_width->x = 40;
	eb_plane_width->y = 340;
	eb_plane_width->width = 100;
	eb_plane_width->height = 20;
	eb_plane_width->title = L"长";
	eb_plane_width->owner = L"plane";
	eb_plane_width->font_size = 18;
	eb_plane_width->text_font_size = 15;
	eb_plane_width->text_color = RGB(10, 10, 10);
	eb_plane_width->color = RGB(10, 10, 250);
	eb_plane_width->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_plane_width->Create();
	engineApp->toolswbar->child_controls.push_back(eb_plane_width);

	EditBox* eb_plane_depth = new EditBox();
	eb_plane_depth->x = 40;
	eb_plane_depth->y = 380;
	eb_plane_depth->width = 100;
	eb_plane_depth->height = 20;
	eb_plane_depth->title = L"宽";
	eb_plane_depth->owner = L"plane";
	eb_plane_depth->font_size = 18;
	eb_plane_depth->text_font_size = 15;
	eb_plane_depth->text_color = RGB(10, 10, 10);
	eb_plane_depth->color = RGB(10, 10, 250);
	eb_plane_depth->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_plane_depth->Create();
	engineApp->toolswbar->child_controls.push_back(eb_plane_depth);

	EditBox* eb_plane_width_divide = new EditBox();
	eb_plane_width_divide->x = 40;
	eb_plane_width_divide->y = 420;
	eb_plane_width_divide->width = 100;
	eb_plane_width_divide->height = 20;
	eb_plane_width_divide->title = L"列数";
	eb_plane_width_divide->owner = L"plane";
	eb_plane_width_divide->font_size = 18;
	eb_plane_width_divide->text_font_size = 15;
	eb_plane_width_divide->text_color = RGB(10, 10, 10);
	eb_plane_width_divide->color = RGB(10, 10, 250);
	eb_plane_width_divide->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_plane_width_divide->Create();
	engineApp->toolswbar->child_controls.push_back(eb_plane_width_divide);

	EditBox* eb_plane_depth_divide = new EditBox();
	eb_plane_depth_divide->x = 40;
	eb_plane_depth_divide->y = 460;
	eb_plane_depth_divide->width = 100;
	eb_plane_depth_divide->height = 20;
	eb_plane_depth_divide->title = L"行数";
	eb_plane_depth_divide->owner = L"plane";
	eb_plane_depth_divide->font_size = 18;
	eb_plane_depth_divide->text_font_size = 15;
	eb_plane_depth_divide->text_color = RGB(10, 10, 10);
	eb_plane_depth_divide->color = RGB(10, 10, 250);
	eb_plane_depth_divide->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_plane_depth_divide->Create();
	engineApp->toolswbar->child_controls.push_back(eb_plane_depth_divide);

	CreatePlane* cp_button = new CreatePlane();
	cp_button->x = 90;
	cp_button->y = 510;
	cp_button->width = 120;
	cp_button->height = 40;
	cp_button->owner = L"plane";
	cp_button->title = L"创建平面";
	//cp_button->hide = TRUE;
	cp_button->font_size = 18;
	cp_button->parent_hwnd = engineApp->toolswbar->hwnd;
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
	: D3DApp(hInstance), mLandVB(0), mLandIB(0), mWavesVB(0), mWavesIB(0), mBoxVB(0), mBoxIB(0), mGrassMapSRV(0), mWavesMapSRV(0), mBoxMapSRV(0),
	mWaterTexOffset(0.0f, 0.0f), mEyePosW(0.0f, 0.0f, 0.0f), mLandIndexCount(0), mRenderOptions(RenderOptions::TexturesAndFog),
	mTheta(1.3f*MathHelper::Pi), mPhi(0.4f*MathHelper::Pi), mRadius(80.0f)
{
	mMainWndCaption = L"Blend Demo";
	mEnable4xMsaa = false;

	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

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
}

DXEngineApp::~DXEngineApp()
{
	md3dImmediateContext->ClearState();
	ReleaseCOM(mLandVB);
	ReleaseCOM(mLandIB);
	ReleaseCOM(mWavesVB);
	ReleaseCOM(mWavesIB);
	ReleaseCOM(mBoxVB);
	ReleaseCOM(mBoxIB);
	ReleaseCOM(mGrassMapSRV);
	ReleaseCOM(mWavesMapSRV);
	ReleaseCOM(mBoxMapSRV);

	//Effects::DestroyAll();
	//InputLayouts::DestroyAll();
	//RenderStates::DestroyAll();
}

bool DXEngineApp::Init()
{
	if (!D3DApp::Init())
		return false;

	mWaves.Init(160, 160, 1.0f, 0.03f, 5.0f, 0.3f);

	// Must init Effects first since InputLayouts depend on shader signatures.
	Effects::InitAll(md3dDevice);
	InputLayouts::InitAll(md3dDevice);
	RenderStates::InitAll(md3dDevice);

	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice,
		L"Textures/grass.dds", 0, 0, &mGrassMapSRV, 0));

	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice,
		L"Textures/circle011.dds", 0, 0, &mWavesMapSRV, 0));

	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice,
		L"Textures/circle011.dds", 0, 0, &mBoxMapSRV, 0));

	//BuildLandGeometryBuffers();
	//BuildWaveGeometryBuffers();
	//BuildCrateGeometryBuffers();

	return true;
}

void DXEngineApp::UpdateScene(float dt)
{
	// Convert Spherical to Cartesian coordinates.
	float x = mRadius*sinf(mPhi)*cosf(mTheta);
	float z = mRadius*sinf(mPhi)*sinf(mTheta);
	float y = mRadius*cosf(mPhi);

	mEyePosW = XMFLOAT3(x, y, z);

	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, V);
/*
	//
	// Every quarter second, generate a random wave.
	//
	static float t_base = 0.0f;
	if ((mTimer.TotalTime() - t_base) >= 0.1f)
	{
		t_base += 0.1f;

		DWORD i = 5 + rand() % (mWaves.RowCount() - 10);
		DWORD j = 5 + rand() % (mWaves.ColumnCount() - 10);

		float r = MathHelper::RandF(0.5f, 1.0f);

		mWaves.Disturb(i, j, r);
	}

	mWaves.Update(dt);

	//
	// Update the wave vertex buffer with the new solution.
	//

	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(md3dImmediateContext->Map(mWavesVB, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));

	Vertex::Basic32* v = reinterpret_cast<Vertex::Basic32*>(mappedData.pData);
	for (UINT i = 0; i < mWaves.VertexCount(); ++i)
	{
		v[i].Pos = mWaves[i];
		v[i].Normal = mWaves.Normal(i);

		// Derive tex-coords in [0,1] from position.
		v[i].Tex.x = 0.5f + mWaves[i].x / mWaves.Width();
		v[i].Tex.y = 0.5f - mWaves[i].z / mWaves.Depth();
	}

	md3dImmediateContext->Unmap(mWavesVB, 0);

	//
	// Animate water texture coordinates.
	//

	// Tile water texture.
	XMMATRIX wavesScale = XMMatrixScaling(5.0f, 5.0f, 0.0f);

	// Translate texture over time.
	mWaterTexOffset.y += 0.05f*dt;
	mWaterTexOffset.x += 0.1f*dt;
	XMMATRIX wavesOffset = XMMatrixTranslation(mWaterTexOffset.x, mWaterTexOffset.y, 0.0f);

	// Combine scale and translation.
	XMStoreFloat4x4(&mWaterTexTransform, wavesScale*wavesOffset);

	//
	// Switch the render mode based in key input.
	//
	if (GetAsyncKeyState('1') & 0x8000)
		mRenderOptions = RenderOptions::Lighting;

	if (GetAsyncKeyState('2') & 0x8000)
		mRenderOptions = RenderOptions::Textures;

	if (GetAsyncKeyState('3') & 0x8000)
		mRenderOptions = RenderOptions::TexturesAndFog;*/
}

void DXEngineApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Black));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	/*md3dImmediateContext->IASetInputLayout(InputLayouts::Basic32);
	md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	UINT stride = sizeof(Vertex::Basic32);
	UINT offset = 0;

	XMMATRIX view = XMLoadFloat4x4(&mView);
	XMMATRIX proj = XMLoadFloat4x4(&mProj);
	XMMATRIX viewProj = view*proj;

	// Set per frame constants.
	Effects::BasicFX->SetDirLights(mDirLights);
	Effects::BasicFX->SetEyePosW(mEyePosW);
	Effects::BasicFX->SetFogColor(Colors::Silver);
	Effects::BasicFX->SetFogStart(15.0f);
	Effects::BasicFX->SetFogRange(175.0f);

	ID3DX11EffectTechnique* boxTech;
	ID3DX11EffectTechnique* landAndWavesTech;

	switch (mRenderOptions)
	{
	case RenderOptions::Lighting:
		boxTech = Effects::BasicFX->Light3Tech;
		landAndWavesTech = Effects::BasicFX->Light3Tech;
		break;
	case RenderOptions::Textures:
		boxTech = Effects::BasicFX->Light3TexAlphaClipTech;
		landAndWavesTech = Effects::BasicFX->Light3TexTech;
		break;
	case RenderOptions::TexturesAndFog:
		boxTech = Effects::BasicFX->Light3TexAlphaClipFogTech;
		landAndWavesTech = Effects::BasicFX->Light3TexFogTech;
		break;
	}

	D3DX11_TECHNIQUE_DESC techDesc;



	//
	// Draw the hills and water with texture and fog (no alpha clipping needed).
	//

	landAndWavesTech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		//
		// Draw the hills.
		//
		md3dImmediateContext->IASetVertexBuffers(0, 1, &mLandVB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(mLandIB, DXGI_FORMAT_R32_UINT, 0);

		// Set per object constants.
		XMMATRIX world = XMLoadFloat4x4(&mLandWorld);
		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
		XMMATRIX worldViewProj = world*view*proj;

		Effects::BasicFX->SetWorld(world);
		Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::BasicFX->SetWorldViewProj(worldViewProj);
		Effects::BasicFX->SetTexTransform(XMLoadFloat4x4(&mGrassTexTransform));
		Effects::BasicFX->SetMaterial(mLandMat);
		Effects::BasicFX->SetDiffuseMap(mGrassMapSRV);

		landAndWavesTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(mLandIndexCount, 0, 0);

		//
		// Draw the waves.
		//
		md3dImmediateContext->IASetVertexBuffers(0, 1, &mWavesVB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(mWavesIB, DXGI_FORMAT_R32_UINT, 0);

		// Set per object constants.
		world = XMLoadFloat4x4(&mWavesWorld);
		worldInvTranspose = MathHelper::InverseTranspose(world);
		worldViewProj = world*view*proj;

		Effects::BasicFX->SetWorld(world);
		Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::BasicFX->SetWorldViewProj(worldViewProj);
		Effects::BasicFX->SetTexTransform(XMLoadFloat4x4(&mWaterTexTransform));
		Effects::BasicFX->SetMaterial(mWavesMat);
		Effects::BasicFX->SetDiffuseMap(mWavesMapSRV);

		md3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
		landAndWavesTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(3 * mWaves.TriangleCount(), 0, 0);

		// Restore default blend state
		md3dImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);
	}

	//
	// Draw the box with alpha clipping.
	// 

	boxTech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		md3dImmediateContext->IASetVertexBuffers(0, 1, &mBoxVB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(mBoxIB, DXGI_FORMAT_R32_UINT, 0);

		// Set per object constants.
		XMMATRIX world = XMLoadFloat4x4(&mBoxWorld);
		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
		XMMATRIX worldViewProj = world*view*proj;

		Effects::BasicFX->SetWorld(world);
		Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::BasicFX->SetWorldViewProj(worldViewProj);
		Effects::BasicFX->SetTexTransform(XMMatrixIdentity());
		Effects::BasicFX->SetMaterial(mBoxMat);
		Effects::BasicFX->SetDiffuseMap(mBoxMapSRV);

		md3dImmediateContext->RSSetState(RenderStates::NoCullRS);
		md3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
		boxTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(36, 0, 0);

		// Restore default render state.
		md3dImmediateContext->RSSetState(0);

		// Restore default blend state
		md3dImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);
	}
	*/
	HR(mSwapChain->Present(0, 0));
}

void DXEngineApp::SetupPlane(int width, int depth, int m, int n)
{

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
