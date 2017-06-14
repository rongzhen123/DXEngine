// 6022SelfCheck.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "DXEngine.h"
#include "ColorButton.h"
#include "TextControl.h"
#include "EditBox.h"
#include "GeometryGenerator.h"
#include "Commdlg.h"
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
int set_rotation_x(int x)
{
	engineApp->rotation_x= x;
	return 0;
}
int set_rotation_y(int y)
{
	engineApp->rotation_y = y;
	return 0;
}
int set_rotation_z(int z)
{
	engineApp->rotation_z = z;
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
int set_color_r(int r)
{
	engineApp->color_r = r;
	return 0;
}
int set_color_g(int g)
{
	engineApp->color_g = g;
	return 0;
}
int set_color_b(int b)
{
	engineApp->color_b = b;
	return 0;
}
int set_color_a(int a)
{
	engineApp->color_a = a;
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
int choose_textrue(int a)
{
	//AfxMessageBox(L"choose texture");
	HWND target = (HWND)a;
	OPENFILENAME ofn = { 0 };
	TCHAR strFileName[MAX_PATH] = { 0 };
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = engineApp->toolswbar->hwnd;
	ofn.lpstrFilter = TEXT("所有文件\0*.*\0图像文件\0*.dds;*.jpg;*.png;*.bmp\0\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = strFileName;
	ofn.nMaxFile = sizeof(strFileName);
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = TEXT("选择纹理图片");
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	if (GetOpenFileName(&ofn))
	{
		CString filename = strFileName;
		engineApp->texture_filename = strFileName;
		int length = filename.GetLength();
		CString path;
		int pos = filename.ReverseFind('\\');
		path = filename.Left(pos+1);
		filename = filename.Right(length - pos-1);
	//	AfxMessageBox(filename + path);
		SetWindowText(target, filename);
	}
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

	TextControl* tc11 = new TextControl(L"Common");
	tc11->x = 30;
	tc11->y = 170;
	tc11->width = 150;
	tc11->height = 40;
	tc11->font_size = 18;
	tc11->color = RGB(60, 60, 60);
	tc11->owner = L"create_common";
	engineApp->toolswbar->child_controls.push_back(tc11);

	TextControl* tc12 = new TextControl(L"Position:");
	tc12->x = 20;
	tc12->y = 212;
	tc12->width = 150;
	tc12->height = 40;
	tc12->font_size = 16;
	tc12->color = RGB(10, 10, 250);
	tc12->owner = L"create_common";
	engineApp->toolswbar->child_controls.push_back(tc12);

	EditBox* position_x = new EditBox();
	position_x->x = 115;
	position_x->y = 210;
	position_x->width = 50;
	position_x->height = 20;
	position_x->ref_pos = 20;
	position_x->title = L"X";
	position_x->owner = L"create_common";
	position_x->content_type = Content_Type_Digit_Int;
	position_x->font_size = 16;
	position_x->text_font_size = 10;
	position_x->text_color = RGB(10, 10, 10);
	position_x->color = RGB(10, 10, 250);
	position_x->UpdateTargetValueFunc = set_position_x;
	position_x->parent_hwnd = engineApp->toolswbar->hwnd;
	position_x->Create();
	engineApp->toolswbar->child_controls.push_back(position_x);

	EditBox* position_y = new EditBox();
	position_y->x = 195;
	position_y->y = 210;
	position_y->width = 50;
	position_y->height = 20;
	position_y->ref_pos = 20;
	position_y->title = L"Y";
	position_y->owner = L"create_common";
	position_y->content_type = Content_Type_Digit_Int;
	position_y->font_size = 16;
	position_y->text_font_size = 10;
	position_y->text_color = RGB(10, 10, 10);
	position_y->color = RGB(10, 10, 250);
	position_y->UpdateTargetValueFunc = set_position_y;
	position_y->parent_hwnd = engineApp->toolswbar->hwnd;
	position_y->Create();
	engineApp->toolswbar->child_controls.push_back(position_y);

	EditBox* position_z = new EditBox();
	position_z->x = 275;
	position_z->y = 210;
	position_z->width = 50;
	position_z->height = 20;
	position_z->ref_pos = 20;
	position_z->title = L"Z";
	position_z->owner = L"create_common";
	position_z->content_type = Content_Type_Digit_Int;
	position_z->font_size = 16;
	position_z->text_font_size = 10;
	position_z->text_color = RGB(10, 10, 10);
	position_z->color = RGB(10, 10, 250);
	position_z->UpdateTargetValueFunc = set_position_z;
	position_z->parent_hwnd = engineApp->toolswbar->hwnd;
	position_z->Create();
	engineApp->toolswbar->child_controls.push_back(position_z);

	TextControl* tc_color = new TextControl(L"Color:");
	tc_color->x = 20;
	tc_color->y = 240;
	tc_color->width = 100;
	tc_color->height = 40;
	tc_color->font_size = 16;
	tc_color->color = RGB(10, 10, 250);
	tc_color->owner = L"create_common";
	engineApp->toolswbar->child_controls.push_back(tc_color);

	EditBox* color_r = new EditBox();
	color_r->x = 85;
	color_r->y = 240;
	color_r->width = 40;
	color_r->height = 20;
	color_r->ref_pos = 20;
	color_r->title = L"R";
	color_r->owner = L"create_common";
	color_r->content_type = Content_Type_Digit_Int;
	color_r->font_size = 18;
	color_r->text_font_size = 15;
	color_r->text_color = RGB(10, 10, 10);
	color_r->color = RGB(10, 10, 250);
	color_r->parent_hwnd = engineApp->toolswbar->hwnd;
	color_r->UpdateTargetValueFunc = set_color_r;
	color_r->Create();
	engineApp->toolswbar->child_controls.push_back(color_r);

	EditBox* color_g = new EditBox();
	color_g->x = 155;
	color_g->y = 240;
	color_g->width = 40;
	color_g->height = 20;
	color_g->ref_pos = 20;
	color_g->title = L"G";
	color_g->owner = L"create_common";
	color_g->content_type = Content_Type_Digit_Int;
	color_g->font_size = 18;
	color_g->text_font_size = 15;
	color_g->text_color = RGB(10, 10, 10);
	color_g->color = RGB(10, 10, 250);
	color_g->parent_hwnd = engineApp->toolswbar->hwnd;
	color_g->UpdateTargetValueFunc = set_color_g;
	color_g->Create();
	engineApp->toolswbar->child_controls.push_back(color_g);

	EditBox* color_b = new EditBox();
	color_b->x = 225;
	color_b->y = 240;
	color_b->width = 40;
	color_b->height = 20;
	color_b->ref_pos = 20;
	color_b->title = L"B";
	color_b->owner = L"create_common";
	color_b->content_type = Content_Type_Digit_Int;
	color_b->font_size = 18;
	color_b->text_font_size = 15;
	color_b->text_color = RGB(10, 10, 10);
	color_b->color = RGB(10, 10, 250);
	color_b->parent_hwnd = engineApp->toolswbar->hwnd;
	color_b->UpdateTargetValueFunc = set_color_b;
	color_b->Create();
	engineApp->toolswbar->child_controls.push_back(color_b);

	EditBox* color_a = new EditBox();
	color_a->x = 295;
	color_a->y = 240;
	color_a->width = 40;
	color_a->height = 20;
	color_a->ref_pos = 20;
	color_a->title = L"A";
	color_a->owner = L"create_common";
	color_a->content_type = Content_Type_Digit_Int;
	color_a->font_size = 18;
	color_a->text_font_size = 15;
	color_a->text_color = RGB(10, 10, 10);
	color_a->color = RGB(10, 10, 250);
	color_a->parent_hwnd = engineApp->toolswbar->hwnd;
	color_a->UpdateTargetValueFunc = set_color_a;
	color_a->Create();
	engineApp->toolswbar->child_controls.push_back(color_a);

	EditBox* texture = new EditBox();
	texture->x = 20;
	texture->y = 270;
	texture->width = 180;
	texture->height = 20;
	texture->ref_pos = 80;
	texture->title = L"Texture:";
	texture->owner = L"create_common";
	texture->content_type = Content_Type_Any;
	texture->ReadOnly = true;
	texture->font_size = 16;
	texture->text_font_size = 15;
	texture->text_color = RGB(10, 10, 10);
	texture->color = RGB(10, 10, 250);
	texture->parent_hwnd = engineApp->toolswbar->hwnd;
	texture->UpdateTargetValueFunc = set_color_a;
	texture->Create();
	engineApp->toolswbar->child_controls.push_back(texture);

	TextControl* tc_rotation = new TextControl(L"Rotation:");
	tc_rotation->x = 20;
	tc_rotation->y = 300;
	tc_rotation->width = 100;
	tc_rotation->height = 40;
	tc_rotation->font_size = 16;
	tc_rotation->color = RGB(10, 10, 250);
	tc_rotation->owner = L"create_common";
	engineApp->toolswbar->child_controls.push_back(tc_rotation);

	EditBox* rotation_x = new EditBox();
	rotation_x->x = 115;
	rotation_x->y = 300;
	rotation_x->width = 50;
	rotation_x->height = 20;
	rotation_x->ref_pos = 20;
	rotation_x->title = L"X";
	rotation_x->owner = L"create_common";
	rotation_x->content_type = Content_Type_Digit_Int;
	rotation_x->font_size = 16;
	rotation_x->text_font_size = 10;
	rotation_x->text_color = RGB(10, 10, 10);
	rotation_x->color = RGB(10, 10, 250);
	rotation_x->UpdateTargetValueFunc = set_rotation_x;
	rotation_x->parent_hwnd = engineApp->toolswbar->hwnd;
	rotation_x->Create();
	engineApp->toolswbar->child_controls.push_back(rotation_x);

	EditBox* rotation_y = new EditBox();
	rotation_y->x = 195;
	rotation_y->y = 300;
	rotation_y->width = 50;
	rotation_y->height = 20;
	rotation_y->ref_pos = 20;
	rotation_y->title = L"Y";
	rotation_y->owner = L"create_common";
	rotation_y->content_type = Content_Type_Digit_Int;
	rotation_y->font_size = 16;
	rotation_y->text_font_size = 10;
	rotation_y->text_color = RGB(10, 10, 10);
	rotation_y->color = RGB(10, 10, 250);
	rotation_y->UpdateTargetValueFunc = set_rotation_y;
	rotation_y->parent_hwnd = engineApp->toolswbar->hwnd;
	rotation_y->Create();
	engineApp->toolswbar->child_controls.push_back(rotation_y);

	EditBox* rotation_z = new EditBox();
	rotation_z->x = 275;
	rotation_z->y = 300;
	rotation_z->width = 50;
	rotation_z->height = 20;
	rotation_z->ref_pos = 20;
	rotation_z->title = L"Z";
	rotation_z->owner = L"create_common";
	rotation_z->content_type = Content_Type_Digit_Int;
	rotation_z->font_size = 16;
	rotation_z->text_font_size = 10;
	rotation_z->text_color = RGB(10, 10, 10);
	rotation_z->color = RGB(10, 10, 250);
	rotation_z->UpdateTargetValueFunc = set_rotation_z;
	rotation_z->parent_hwnd = engineApp->toolswbar->hwnd;
	rotation_z->Create();
	engineApp->toolswbar->child_controls.push_back(rotation_z);

	TextControl* tc_scale = new TextControl(L"Scale:");
	tc_scale->x = 20;
	tc_scale->y = 330;
	tc_scale->width = 100;
	tc_scale->height = 40;
	tc_scale->font_size = 16;
	tc_scale->color = RGB(10, 10, 250);
	tc_scale->owner = L"create_common";
	engineApp->toolswbar->child_controls.push_back(tc_scale);

	EditBox* scale_x = new EditBox();
	scale_x->x = 115;
	scale_x->y = 330;
	scale_x->width = 50;
	scale_x->height = 20;
	scale_x->ref_pos = 20;
	scale_x->title = L"X";
	scale_x->owner = L"create_common";
	scale_x->content_type = Content_Type_Digit_Int;
	scale_x->font_size = 16;
	scale_x->text_font_size = 10;
	scale_x->text_color = RGB(10, 10, 10);
	scale_x->color = RGB(10, 10, 250);
	scale_x->UpdateTargetValueFunc = set_scale_x;
	scale_x->parent_hwnd = engineApp->toolswbar->hwnd;
	scale_x->Create();
	engineApp->toolswbar->child_controls.push_back(scale_x);

	EditBox* scale_y = new EditBox();
	scale_y->x = 195;
	scale_y->y = 330;
	scale_y->width = 50;
	scale_y->height = 20;
	scale_y->ref_pos = 20;
	scale_y->title = L"Y";
	scale_y->owner = L"create_common";
	scale_y->content_type = Content_Type_Digit_Int;
	scale_y->font_size = 16;
	scale_y->text_font_size = 10;
	scale_y->text_color = RGB(10, 10, 10);
	scale_y->color = RGB(10, 10, 250);
	scale_y->UpdateTargetValueFunc = set_scale_y;
	scale_y->parent_hwnd = engineApp->toolswbar->hwnd;
	scale_y->Create();
	engineApp->toolswbar->child_controls.push_back(scale_y);

	EditBox* scale_z = new EditBox();
	scale_z->x = 275;
	scale_z->y = 330;
	scale_z->width = 50;
	scale_z->height = 20;
	scale_z->ref_pos = 20;
	scale_z->title = L"Z";
	scale_z->owner = L"create_common";
	scale_z->content_type = Content_Type_Digit_Int;
	scale_z->font_size = 16;
	scale_z->text_font_size = 10;
	scale_z->text_color = RGB(10, 10, 10);
	scale_z->color = RGB(10, 10, 250);
	scale_z->UpdateTargetValueFunc = set_scale_z;
	scale_z->parent_hwnd = engineApp->toolswbar->hwnd;
	scale_z->Create();
	engineApp->toolswbar->child_controls.push_back(scale_z);

	ColorButton* choosetexture = new ColorButton();
	choosetexture->x = 290;
	choosetexture->y = 270;
	choosetexture->width = 60;
	choosetexture->height = 19;
	choosetexture->owner = L"create_common";
	choosetexture->title = L"选择";
	choosetexture->color = RGB(10,250,50);
	choosetexture->text_color = RGB(10, 0, 5);
	//cp_button->hide = TRUE;
	choosetexture->font_size = 15;
	choosetexture->parent_hwnd = engineApp->toolswbar->hwnd;
	choosetexture->app = engineApp;
	choosetexture->event_func = choose_textrue;
	choosetexture->parent = engineApp->toolswbar;
	choosetexture->userdata = texture->hwnd;
	engineApp->toolswbar->child_controls.push_back(choosetexture);

	TextControl* tc2 = new TextControl(L"平面参数");
	tc2->x = 30;
	tc2->y = 400;
	tc2->width = 150;
	tc2->height = 40;
	tc2->font_size = 18;
	tc2->color = RGB(60, 60, 60);
	tc2->owner = L"plane";
	engineApp->toolswbar->child_controls.push_back(tc2);

	EditBox* eb_plane_width = new EditBox();
	eb_plane_width->x = 40;
	eb_plane_width->y = 440;
	eb_plane_width->width = 50;
	eb_plane_width->height = 20;
	eb_plane_width->title = L"长";
	eb_plane_width->owner = L"plane";
	eb_plane_width->content_type = Content_Type_Digit_Int;
	eb_plane_width->font_size = 18;
	eb_plane_width->text_font_size = 10;
	eb_plane_width->text_color = RGB(10, 10, 10);
	eb_plane_width->color = RGB(10, 10, 250);
	eb_plane_width->UpdateTargetValueFunc = set_plane_width;
	eb_plane_width->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_plane_width->Create();
	engineApp->toolswbar->child_controls.push_back(eb_plane_width);

	EditBox* eb_plane_depth = new EditBox();
	eb_plane_depth->x = 40;
	eb_plane_depth->y = 480;
	eb_plane_depth->width = 50;
	eb_plane_depth->height = 20;
	eb_plane_depth->title = L"宽";
	eb_plane_depth->owner = L"plane";
	eb_plane_depth->content_type = Content_Type_Digit_Int;
	eb_plane_depth->font_size = 18;
	eb_plane_depth->text_font_size = 10;
	eb_plane_depth->text_color = RGB(10, 10, 10);
	eb_plane_depth->color = RGB(10, 10, 250);
	eb_plane_depth->parent_hwnd = engineApp->toolswbar->hwnd;
	eb_plane_depth->UpdateTargetValueFunc = set_plane_depth;
	eb_plane_depth->Create();
	engineApp->toolswbar->child_controls.push_back(eb_plane_depth);

	EditBox* eb_plane_width_divide = new EditBox();
	eb_plane_width_divide->x = 40;
	eb_plane_width_divide->y = 520;
	eb_plane_width_divide->width = 50;
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
	eb_plane_depth_divide->y = 560;
	eb_plane_depth_divide->width = 50;
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
	cp_button->y = 610;
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

int DXEngineApp::m_NumberPlaneCreated = 0;
int DXEngineApp::m_NumberBoxCreated = 0;
int DXEngineApp::m_NumberSphereCreated = 0;
int DXEngineApp::m_NumberCylinderCreated = 0;
int DXEngineApp::m_NumberStaticMeshCreated = 0;
int DXEngineApp::m_NumberSkinnedMeshCreated = 0;
int DXEngineApp::m_NumberNodeCreated = 0;

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

	//创建几何体相关参数
	 plane_width = plane_depth = m = n = 0;
	 box_width = box_height = box_depth = 0;
	 sphere_radius = sphere_slice_count = sphere_stack_count = 0;
	 cylinder_top_radius = cylinder_bottom_radius = cylinder_slice_count = cylinder_stack_count = 0;
	// mRenderQueue.clear();
}
DXEngineApp::~DXEngineApp()
{
	md3dImmediateContext->ClearState();
//	mRenderQueue.clear();
	Effects::DestroyAll();
	//InputLayouts::DestroyAll();
	//RenderStates::DestroyAll();
}
bool DXEngineApp::Init()
{
	if (!D3DApp::Init())
		return false;
	
	if (Effects::InitAll(md3dDevice) == false)
	{
		AfxMessageBox(L"Effects::InitAll ERROR!");
	}
	mSceneMgr = new SceneManager("defaultSceneMgr", md3dDevice, md3dImmediateContext, mSwapChain);
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
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Silver));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mCam.UpdateViewMatrix();
	XMMATRIX view = mCam.View();
	XMMATRIX proj = mCam.Proj();
	XMMATRIX viewProj = mCam.ViewProj();
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	/*for (unsigned int i = 0; i < mRenderQueue.size(); i++)
	{
		XMMATRIX world = XMMatrixIdentity();// XMMatrixTranslation(1.0f, 1.5f, 1.0f);
		XMMATRIX trans = XMMatrixTranslation(mRenderQueue[i]->mPos.x, mRenderQueue[i]->mPos.y, mRenderQueue[i]->mPos.z);
		XMMATRIX scale = XMMatrixScaling(mRenderQueue[i]->mScale.x, mRenderQueue[i]->mScale.y, mRenderQueue[i]->mScale.z);
		XMMATRIX rotation_x = XMMatrixRotationX(mRenderQueue[i]->mRotation.x);
		XMMATRIX rotation_y = XMMatrixRotationY(mRenderQueue[i]->mRotation.y);
		XMMATRIX rotation_z = XMMatrixRotationZ(mRenderQueue[i]->mRotation.z);
		XMMATRIX rotation = rotation_x * rotation_y * rotation_z;
		XMMATRIX worldViewProj =world *rotation*scale*trans*viewProj;
		mRenderQueue[i]->mEffectWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));
		if (mRenderQueue[i]->mMaterialType == POS_TEX || mRenderQueue[i]->mMaterialType == POS_TEX_COLOR)
		{
			md3dImmediateContext->OMSetBlendState(((ManualMesh_Texture*)mRenderQueue[i])->mBS, blendFactor, 0xffffffff);
			md3dImmediateContext->RSSetState(((ManualMesh_Texture*)mRenderQueue[i])->mRS);
			((ManualMesh_Texture*)mRenderQueue[i])->mDiffuseMap->SetResource(((ManualMesh_Texture*)mRenderQueue[i])->m_TextureSRV);
		}
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
	}*/

	HR(mSwapChain->Present(0, 0));
}
void DXEngineApp::DrawBackground()
{

}
float DXEngineApp::GetHillHeight(float x, float z)const
{
	return 0.3f*(z*sinf(0.1f*x) + x*cosf(0.1f*z));
}

void DXEngineApp::SetupPlane(int width, int depth, int m, int n, float posx, float posy, float posz, float scalex, float scaley, float scalez)
{
/*
	GeometryGenerator geoGen;
	GeometryGenerator::MeshData plane;
	geoGen.CreateGrid(width, depth, m, n, plane);
	ManualMesh_Texture* mesh1 = new ManualMesh_Texture(ManualMeshType_Plane);
	mesh1->mPos = XMFLOAT3(posx, posy, posz);
	mesh1->mScale = XMFLOAT3(scalex, scaley, scalez);
	mesh1->mRotation = XMFLOAT3(rotation_x, rotation_y, rotation_z);
	mesh1->mColor = XMFLOAT4(color_r / 255.0, color_g / 255.0, color_b / 255.0, color_a / 255.0);
	mesh1->mDiffuseMap = Effects::mDiffuseMap_PosTex;
	ID3D11ShaderResourceView* m_TextureSRV;
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(md3dDevice, texture_filename, 0, 0, &m_TextureSRV, 0);
	mesh1->m_TextureSRV = m_TextureSRV;
	mesh1->Init(md3dDevice, plane, Effects::mEffectPosTex, Effects::mEffectTechPosTex, Effects::mInputLayout_PosTex,
		Effects::mEffectWorldViewProj_PosTex, Effects::mRS, Effects::TransparentBS);*/
//	mRenderQueue.push_back(mesh1);
	std::stringstream ss;
	ss << "node" << m_NumberNodeCreated;
	SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode(ss.str());
	ManualMeshParameter parameter;
	parameter.Reset();
	Entity* renderEntity = mSceneMgr->createEntityPlane(ss.str(), parameter, width, depth, m, n);
	node->attachObject(renderEntity);
	Vector3 position = {10,10,10};
	node->setPosition(position);
	m_NumberNodeCreated++;
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
