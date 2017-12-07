#pragma once
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

class CShapes
{
protected:
	POINT Start;
	POINT End;
	Brush *brush;
	Pen *pen;
public:
	CShapes();
	~CShapes();
	virtual void Draw(Graphics*)=0;
};

class CLine :public CShapes
{
public:
	CLine();
	CLine(POINT, POINT);
	~CLine();
	void Draw(Graphics*);
};

class CRectangle :public CShapes
{
public:
	CRectangle();
	CRectangle(POINT, POINT);
	~CRectangle();
	void Draw(Graphics*);
};

class CEllipse :public CShapes
{
public:
	CEllipse();
	CEllipse(POINT,POINT);
	~CEllipse();
	void Draw(Graphics*);
};

