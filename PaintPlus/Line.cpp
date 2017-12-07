#include "stdafx.h"
#include "Shapes.h"


CLine::CLine()
{
}

CLine::CLine(POINT x, POINT y)
{
	pen = new Pen(Color(255, 0, 0, 0));
	brush = new SolidBrush(Color(255, 0, 0, 0));
	this->Start = x;
	this->End = y;
}
CLine::~CLine()
{
	delete(pen);
	delete(brush);
}

void CLine::Draw(Graphics* graphics)
{
	graphics->DrawLine(pen, Start.x, Start.y, End.x,End.y);
}

