#include "stdafx.h"
#include "Shapes.h"


CShapes::CShapes()
{
	pen = new Pen(Color(255, 0, 150, 255));
	brush = new SolidBrush(Color(255, 0, 0, 0));
	Start.x = 0;
	Start.y = 0;
	End.x = 0;
	End.y = 0;
}



CShapes::~CShapes()
{
	delete(pen);
	delete(brush);
}



