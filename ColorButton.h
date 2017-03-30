#pragma once
#include "stdafx.h"
#ifndef COLORBUTTON
#define COLORBUTTON
#include "ControlBase.h"
#include "DXEngine.h"
class ColorButton : public ControlBase
{
public:
	DXEngineApp* app;
	ColorButton();
	int draw(HDC hdc);//控件的绘制函数
	int event(int eventtype, int x, int y);
};

class CreatePlaneButton : public ColorButton
{
public:
	CreatePlaneButton();
	int event(int eventtype, int x, int y);
};
class CreateBoxButton : public ColorButton
{
public:
	CreateBoxButton();
	int event(int eventtype, int x, int y);
};
class CreateSphereButton : public ColorButton
{
public:
	CreateSphereButton();
	int event(int eventtype, int x, int y);
};

class CreateCylinderButton : public ColorButton
{
public:
	CreateCylinderButton();
	int event(int eventtype, int x, int y);
};

class CreateCylinder : public ColorButton
{
public:
	CreateCylinder();
	int event(int eventtype, int x, int y);
};
class CreatePlane : public ColorButton
{
public:
	CreatePlane();
	int event(int eventtype, int x, int y);
};
class CreateBox : public ColorButton
{
public:
	CreateBox();
	int event(int eventtype, int x, int y);
};
class CreateSphere : public ColorButton
{
public:
	CreateSphere();
	int event(int eventtype, int x, int y);
};

#endif