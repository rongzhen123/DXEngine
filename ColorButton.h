#pragma once
#include "stdafx.h"
#ifndef COLORBUTTON
#define COLORBUTTON
//#include "DXEngine.h"

#include "ControlBase.h"

class DXEngine;
class ColorButton : public ControlBase
{
public:
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

#endif