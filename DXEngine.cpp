// 6022SelfCheck.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "DXEngine.h"

#define MAX_LOADSTRING 100

using namespace std;
// ȫ�ֱ���: 

// ��ǰʵ��
/*WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
*/
/*
ID3D11Device* md3dDevice;
ID3D11DeviceContext* md3dImmediateContext;
IDXGISwapChain* mSwapChain;
ID3D11Texture2D* mDepthStencilBuffer;
ID3D11RenderTargetView* mRenderTargetView;
ID3D11DepthStencilView* mDepthStencilView;
D3D11_VIEWPORT mScreenViewport;
*/

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

	HANDLE m_MenuThread;//��������߳�
	HWND m_MenuHwnd;
	bool Init();
	void SetUpToolWindows();
	//void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

	
	//void OnMouseDown(WPARAM btnState, int x, int y);
	//void OnMouseUp(WPARAM btnState, int x, int y);
	//void OnMouseMove(WPARAM btnState, int x, int y);

	static DWORD WINAPI MenuThread(LPVOID lParam);//�̺߳���;
private:
	//float GetHillHeight(float x, float z)const;
	//XMFLOAT3 GetHillNormal(float x, float z)const;
	//void BuildLandGeometryBuffers();
	//void BuildWaveGeometryBuffers();
	//void BuildCrateGeometryBuffers();

private:
	ID3D11Buffer* mLandVB;
	ID3D11Buffer* mLandIB;

	ID3D11Buffer* mWavesVB;
	ID3D11Buffer* mWavesIB;

	ID3D11Buffer* mBoxVB;
	ID3D11Buffer* mBoxIB;

	ID3D11ShaderResourceView* mGrassMapSRV;
	ID3D11ShaderResourceView* mWavesMapSRV;
	ID3D11ShaderResourceView* mBoxMapSRV;

	Waves mWaves;

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
	engineApp->SetUpToolWindows();
	HINSTANCE hInstance = engineApp->AppInst();
	WindowManager* windowManager = WindowManager::getInstance();
	windowManager->Init(hInstance);
	engineApp->toolswbar = new NormalWindow();
	engineApp->toolswbar->title = L"���ߴ���";
	engineApp->toolswbar->position_x = 100;
	engineApp->toolswbar->position_y = 200;
	engineApp->toolswbar->window_height = 800;
	engineApp->toolswbar->window_width = 400;
	engineApp->toolswbar->color = RGB(255,255,255);
	engineApp->toolswbar->userdata = (void*)engineApp;
	engineApp->toolswbar->child_controls.clear();

	CreatePlaneButton* cpb = new CreatePlaneButton();
	cpb->x = 30;
	cpb->y = 40;
	cpb->width = 130;
	cpb->height = 50;
	cpb->title = L"����ƽ��";
	//cpb->parent = engineApp->toolswbar;
	engineApp->toolswbar->child_controls.push_back(cpb);

	CreateBoxButton* cbb = new CreateBoxButton();
	cbb->x = 180;
	cbb->y = 40;
	cbb->width = 130;
	cbb->height = 50;
	cbb->title = L"��������";
	//cbb->parent = engineApp->toolswbar;
	engineApp->toolswbar->child_controls.push_back(cbb);

	CreateSphereButton* chb = new CreateSphereButton();
	chb->x = 30;
	chb->y = 100;
	chb->width = 130;
	chb->height = 50;
	chb->title = L"��������";
	//chb->parent = engineApp->toolswbar;
	engineApp->toolswbar->child_controls.push_back(chb);

	CreateCylinderButton* ccb = new CreateCylinderButton();
	ccb->x = 180;
	ccb->y = 100;
	ccb->width = 130;
	ccb->height = 50;
	ccb->title = L"����Բ��";
	//ccb->parent = engineApp->toolswbar;
	engineApp->toolswbar->child_controls.push_back(ccb);

	windowManager->RegisterWindow(engineApp->toolswbar);
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
		MessageBox(NULL, L"�����˵��߳�ʧ�ܣ�", L"Error", MB_ICONERROR);
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

void DXEngineApp::SetUpToolWindows()
{
	toolsubitems.clear();
	/*menuitem_width = 150;
	menuitem_height = 50;
	menuitem_interval = 15;
	first_column_menuitem_left_margin = 30;
	colorbutton *planebutton = new colorbutton();
	planebutton->title = L"ƽ��";
	planebutton->always_show = TRUE;
	planebutton->type = Button;
	planebutton->subview = NULL;
	planebutton->enabled = TRUE;
	planebutton->color = RGB(255, 0, 0);
	planebutton->x = first_column_menuitem_left_margin;
	planebutton->y = 0 * (menuitem_height + menuitem_interval) + 50;
	planebutton->width = menuitem_width;
	planebutton->height = menuitem_height;
	planebutton->event_func = create_plane_button_hit;
	toolsubitems.push_back(planebutton);

	colorbutton *boxbutton = new colorbutton();
	boxbutton->title = L"������";
	boxbutton->always_show = TRUE;
	boxbutton->type = Button;
	boxbutton->subview = NULL;
	boxbutton->enabled = TRUE;
	boxbutton->color = RGB(255, 0, 0);
	boxbutton->x = first_column_menuitem_left_margin;
	boxbutton->y = 1 * (menuitem_height + menuitem_interval) + 50;
	boxbutton->width = menuitem_width;
	boxbutton->height = menuitem_height;
	boxbutton->event_func = create_box_button_hit;
	toolsubitems.push_back(boxbutton);

	colorbutton *spherebutton = new colorbutton();
	spherebutton->title = L"����";
	spherebutton->always_show = TRUE;
	spherebutton->type = Button;
	spherebutton->subview = NULL;
	spherebutton->enabled = TRUE;
	spherebutton->color = RGB(255, 0, 0);
	spherebutton->x = first_column_menuitem_left_margin;
	spherebutton->y = 2 * (menuitem_height + menuitem_interval) + 50;
	spherebutton->width = menuitem_width;
	spherebutton->height = menuitem_height;
	spherebutton->event_func = create_sphere_button_hit;
	toolsubitems.push_back(spherebutton);

	colorbutton *cylinderbutton = new colorbutton();
	cylinderbutton->title = L"Բ����";
	cylinderbutton->always_show = TRUE;
	cylinderbutton->type = Button;
	cylinderbutton->subview = NULL;
	cylinderbutton->enabled = TRUE;
	cylinderbutton->color = RGB(255, 0, 0);
	cylinderbutton->x = first_column_menuitem_left_margin;
	cylinderbutton->y = 3 * (menuitem_height + menuitem_interval) + 50;
	cylinderbutton->width = menuitem_width;
	cylinderbutton->height = menuitem_height;
	cylinderbutton->event_func = create_cylinder_button_hit;
	toolsubitems.push_back(cylinderbutton);*/
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
/*
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY6022SELFCHECK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_MY6022SELFCHECK);
    wcex.lpszClassName  = L"MenuWindow";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
	int screen_width = 	GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN) - 80;
   HWND hWnd = CreateWindowEx(WS_EX_LAYERED, szWindowClass, L"6022SelfCheck_Main_Window_2016_12_16", WS_OVERLAPPED, 0, 0, screen_width, screen_height, nullptr, NULL, hInstance, (LPVOID)NULL);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   SetLayeredWindowAttributes(hWnd, 0, 250, LWA_ALPHA);
   ghwnd = hWnd;
   return TRUE;
}*/


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	HPEN pen;
	HPEN oldpen;
	HBRUSH hBrush, hBrush2;
	HBITMAP hbm;
	HBITMAP comdcoldbitmap;
	DXEngineApp* engineApp = NULL;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (wmEvent == CBN_SELCHANGE)
		{
			HWND hwnd = (HWND)lParam;
			if (hwnd == product_type)
			{
				//SetupCaliParameters();
				CString path1 = GetAppPath() + "\\6022BE_config.ini";
				CString path2 = GetAppPath() + "\\6022BL_config.ini";
				int cur_product = SendMessage(product_type, CB_GETCURSEL, 0, 0);
				if (cur_product == 0)//BE
				{
					//EnumIniFile(path1);
				}
				else if (cur_product == 1)
				{
					//EnumIniFile(path2);
				}
				//SetUpWindowItems();
			}
		}
		break;
	case WM_CHAR:
	{
		char ascii_code = wParam;
		unsigned int key_state = lParam;
		if (ascii_code == 'q' || ascii_code == 'Q')
		{
			if (has_error == TRUE && running == TRUE && dev_lost == FALSE)
			{
				//mylog("ǿ��ͨ��\r\n");
				has_error = FALSE;
			}
		}
	}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		HDC comdc = CreateCompatibleDC(hdc);
		HFONT font = CreateFont(27, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("����"));
		HFONT comdcoldfont = (HFONT)::SelectObject(comdc, font);
		hBrush = CreateSolidBrush(rgbBackgroundColor);

		hBrush2 = CreateSolidBrush(LIGHT_BLUE_COLOR);
		pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		oldpen = (HPEN)SelectObject(comdc, pen);
		GetClientRect(hWnd, &rect);
		hbm = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
		comdcoldbitmap = (HBITMAP)SelectObject(comdc, hbm);
		FillRect(comdc, &rect, hBrush);
		SetBkMode(comdc, TRANSPARENT);
		SetTextColor(comdc, COLORREF(RGB(255, 255, 255)));
		int i = 0;
		
		vector<windowitem*>::iterator it;
		for (it = toolsubitems.begin(); it != toolsubitems.end(); it++)
		{
			(*it)->draw(comdc);
		}
		
		Graphics g(comdc);
		CString path = GetAppPath();
		
		
		FontFamily fontFamily(L"����");
		SolidBrush brush(Color(255, 0, 0, 0));
		Gdiplus::Font font2(&fontFamily, 16, FontStyleBold, UnitPixel);
		Gdiplus::PointF point11((rect.right - rect.left) / 2 + (rect.right - rect.left) / 3 - 60, (rect.bottom - rect.top)/12+3);
	//	g.DrawString(L"�ͺ�:", -1, &font2, point11, &brush);
		BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top - 20, comdc, 0, 0, SRCCOPY);
		SelectObject(comdc, comdcoldbitmap);
		SelectObject(comdc, comdcoldfont);
		DeleteObject(font);
		DeleteObject(hbm);
		SelectObject(comdc, oldpen);
		DeleteObject(pen);
		DeleteObject(hBrush);
		DeleteObject(hBrush2);
		DeleteObject(oldpen);
		DeleteDC(comdc);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONUP:
	{
		int x_pos = LOWORD(lParam);
		int y_pos = HIWORD(lParam);
		vector<windowitem*>::iterator it;
		for (it = toolsubitems.begin(); it != toolsubitems.end(); it++)
		{
			if (abs(y_pos - old_pos_y) <= 5)
			{
				if ((*it)->event(EVENT_LBUTTON_UP, x_pos, y_pos) == 1)//event����1��ʾ�ÿؼ��������˸��¼����Ϳ�������ѭ����
				{
					if ((*it)->event_func != NULL)
					{
						(*it)->event_func((int)(*it));
					}
					break;
				}
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		old_mouse_pos_x = LOWORD(lParam);
		old_mouse_pos_y = HIWORD(lParam);
		old_pos_y = old_mouse_pos_y;
		POINT pt;
		pt.x = old_mouse_pos_x;
		pt.y = old_mouse_pos_y;
		ClientToScreen(hWnd, &pt);
		old_mouse_pos_x = pt.x;
		old_mouse_pos_y = pt.y;
		RECT rect;
		GetWindowRect(hWnd, &rect);
		old_window_pos_x = rect.left;
		old_window_pos_y = rect.top;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (wParam == MK_LBUTTON)
		{
			int x_pos = LOWORD(lParam);
			int y_pos = HIWORD(lParam);
			POINT pt;
			pt.x = x_pos;
			pt.y = y_pos;
			ClientToScreen(hWnd, &pt);
			int x_diff = pt.x - old_mouse_pos_x;
			int y_diff = pt.y - old_mouse_pos_y;
			int new_window_pos_x = old_window_pos_x + x_diff;
			int new_window_pos_y = old_window_pos_y + y_diff;
		}
	}
	break;
	case WM_SIZE:
		return 1;
	case WM_TIMER:
		if (wParam == UPDATE_CURRENT_STATE_TIMER)
		{
			InvalidateRect(ghwnd, NULL, FALSE);
		}
		else if (ERROR_UPDATE_TIMER == wParam)
		{
			InvalidateRect(ghwnd, NULL, FALSE);
		}
		break;
	case WM_DESTROY:
		PostMessage(ghwnd, WM_QUIT, 0, 0);
		break;

	case WM_RBUTTONDOWN:
	break;
	case WM_CREATE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		
		CREATESTRUCT *cs;
		cs = (CREATESTRUCT *)lParam;
		engineApp = (DXEngineApp*)cs->lpCreateParams;
		if (engineApp == NULL)
		{
			AfxMessageBox(L"ToolWnd engineApp IS null!");
		}
		InvalidateRect(hWnd, NULL, FALSE);
		//SendMessage(hWnd, WM_LBUTTONUP, 10, 10);
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
    return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int mini_button_hit(int x)
{
	ShowWindow(ghwnd, SW_SHOWMINIMIZED);
	return 0;
}

int menu_button_hit(int x)
{
	stChooseColor.lStructSize = sizeof(CHOOSECOLOR);
	stChooseColor.hwndOwner = ghwnd;
	stChooseColor.rgbResult = rgbBackgroundColor;
	stChooseColor.lpCustColors = (LPDWORD)crCustColors;
	stChooseColor.Flags = CC_RGBINIT;
	stChooseColor.lCustData = 0;
	stChooseColor.lpfnHook = NULL;
	stChooseColor.lpTemplateName = NULL;
	if (ChooseColor(&stChooseColor))
	{
		rgbBackgroundColor = stChooseColor.rgbResult;
	}
	return 0;
}

int close_button_hit(int x)
{
	if (IDYES == MessageBox(ghwnd, L"ȷ��Ҫ�رձ������", L"�ر����", MB_YESNO))
	{
		if (IsWindow(targethwnd))
		{
			SendMessage(targethwnd,WM_SHUTDOWN_YOURSELF,0,0);
		}
		if (IsWindow(targethwnd_LA))
		{
			SendMessage(targethwnd_LA, WM_SHUTDOWN_YOURSELF, 0, 0);
		}

		DestroyWindow(ghwnd);
	}
	return 0;
}
int update_config_button_hit(int x)
{

	return 0;
}
int test_this_step(int x)
{
	
	current_step_index = ((windowitem*)x)->step_index;
	return 0;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	wchar_t title[256];
	GetWindowText(hwnd, title, 256);
	CStringW str = title;
	int cur_product = SendMessage(product_type, CB_GETCURSEL, 0, 0);
	if (cur_product == 0)//BE
	{
		int index = str.Find(L"Hantek6022BE---��������ר��");
		if (index != -1)
		{
			targethwnd = hwnd;
			return FALSE;//����falseֹͣö��
		}
	}
	else //BL
	{
		int index = str.Find(L"Hantek6022BLʾ����---��������ר��");
		if (index != -1)
		{
			targethwnd = hwnd;
			SendMessage(targethwnd, WM_SET_DEVMODE, 0, DEVMODE_6022_BE);
			return FALSE;//����falseֹͣö��
		}
	}

	return TRUE;
}


int start_check_button_hit(int x)
{
	quittest = FALSE;
	EnableWindow(product_type, FALSE);
	if (running == FALSE && dev_lost == FALSE)
	{
		if (IsWindow(targethwnd))
		{

		}
		else
		{
			int cur_product = SendMessage(product_type, CB_GETCURSEL, 0, 0);
			if (cur_product == 0)//BE
			{
				targethwnd = FindWindow(NULL, L"Hantek6022BE---��������ר��");
			}
			else
			{
				targethwnd = FindWindow(NULL, L"Hantek6022BLʾ����---��������ר��");
			}
		}
		if (IsWindow(targethwnd_LA))
		{

		}
		else
		{
			targethwnd_LA = FindWindow(NULL, L"Logic-Multi function virtual signal analyzer --- ��������ר��");
		}
		
		running = TRUE;
		error_step_index = 1000;
		for (int i = 0; i < SELF_CHECK_STEP_NUMBER; i++)
		{
			check_result[i] = 0;
		}
		InvalidateRect(ghwnd, NULL, FALSE);
		SetTimer(ghwnd, UPDATE_CURRENT_STATE_TIMER, 100, (TIMERPROC)NULL);
	}
	return 0;
}

int single_check_button_hit(int x)
{
	return 0;
}

int force_pass_button_hit(int x)
{
	if (has_error == TRUE && running == TRUE && dev_lost == FALSE)
	{
		//if (IDYES == MessageBox(ghwnd, L"ȷ��Ҫǿ��ͨ��������", L"ǿ��ͨ������", MB_YESNO))
		{
			has_error = FALSE;
			//mylog("ǿ��ͨ��\r\n");
		}	
	}
	return 0;
}

int check_fail_button_hit(int x)
{
	if (IDYES == MessageBox(ghwnd, L"ȷ������������", L"����ʧ��", MB_YESNO))
	{
		running = FALSE;
		quittest = TRUE;
		//has_error = FALSE;
		error_step_index = 1000;
		for (int i = 0; i < SELF_CHECK_STEP_NUMBER; i++)
		{
			check_result[i] = 0;
		}
		EnableWindow(product_type, TRUE);
		InvalidateRect(ghwnd, NULL, FALSE);
	}
	return 0;
}
