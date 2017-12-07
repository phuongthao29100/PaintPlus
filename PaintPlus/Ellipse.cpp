#include "stdafx.h"
#include "Shapes.h"


CEllipse::CEllipse()
{
}

CEllipse::CEllipse(POINT x, POINT y)
{
	pen = new Pen(Color(255, 0, 0, 0));
	brush = new SolidBrush(Color(255, 0, 0, 0));
	this->Start = x;
	this->End = y;
}

CEllipse::~CEllipse()
{
	delete(pen);
	delete(brush);
}

void CEllipse::Draw(Graphics* graphics)
{
	int x = Start.x;
	int y = Start.y;
	int width = abs(End.x - Start.x);
	int height = abs(End.y - Start.y);
	if (End.x < Start.x)
		x = Start.x - width;
	if (End.y < Start.y)
		y = Start.y - height;
	graphics->DrawEllipse(pen, x, y, width, height);
}