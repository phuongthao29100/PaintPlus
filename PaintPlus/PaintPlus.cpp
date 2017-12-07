// PaintPlus.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PaintPlus.h"
#include "Shapes.h"
#include <windowsx.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include "RibbonFramework.h"
#include "RibbonIDs.h"
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
using namespace std;



#define MAX_LOADSTRING 100
#define LINE 1
#define RECTANGLE 2
#define ELLIPSE 3

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


void ModeShift(POINT &start, POINT &last);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	HRESULT hr = CoInitialize(NULL);
	if (FALSE(hr)){
		return FALSE;
	}
		

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PAINTPLUS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINTPLUS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	CoUninitialize();

	return (int) msg.wParam;
}

void ModeShift(POINT &start, POINT &last)
{
	int x = last.x - start.x;
	int y = last.y - start.y;

	int absX = abs(x);
	int absY = abs(y);
	if (absX > absY)
	{
		if (last.x<start.x)
			last.x = start.x - absY;
		else
			last.x = start.x + absY;
	}
	else
	{
		if (last.y < start.y)
			last.y = start.y - absX;
		else
			last.y = start.y + absX;
	}
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= 0;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINTPLUS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PAINTPLUS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

//Bien cuc bo
POINT current, start, last;
bool drawing = false;
int options = LINE;
CShapes* object=NULL;
vector <CShapes*> listShapes;
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	bool initSuccess;

	switch (message)
	{
	case WM_CREATE:
	{
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		initSuccess = InitializeFramework(hWnd);
		if (!initSuccess){
			return -1;
		}
	}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BTN_LINE:
			options = LINE;
			break;
		case ID_BTN_RECTANGLE:
			options = RECTANGLE;
			break;
		case ID_BTN_ELLIPSE:
			options = ELLIPSE;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
	{
						   current.x = GET_X_LPARAM(lParam);
						   current.y = GET_Y_LPARAM(lParam);
						   start.x = current.x;
						   start.y = current.y;

						   drawing = true;

						   break;
	}
	case WM_MOUSEMOVE:
	{
						 current.x = GET_X_LPARAM(lParam);
						 current.y = GET_Y_LPARAM(lParam);
						 

						 if (drawing)
						 {
							 last.x = current.x;
							 last.y = current.y;
							 if (wParam & MK_SHIFT)
							 {
								 //object.setPressShift(1);
								 ModeShift(start,last);
							 }
							 
							 InvalidateRect(hWnd, NULL, TRUE);
						 }
						 break;
	}
	case WM_LBUTTONUP:
	{
						 current.x = GET_X_LPARAM(lParam);
						 current.y = GET_Y_LPARAM(lParam);
						 last.x = current.x;
						 last.y = current.y;
						 listShapes.push_back(object);
						 drawing = false;
						 break;
	}
	case WM_PAINT:
	{
					 PAINTSTRUCT ps;
					 HDC hdc = BeginPaint(hWnd, &ps);
					 Graphics* graphics = new Graphics(hdc);

					 //SelectObject(hdc, GetStockObject(NULL_BRUSH));	//Trong suot
					 for (int i = 0; i < listShapes.size(); i++)
					 {
						 listShapes[i]->Draw(graphics);
					 }
					 switch (options)
					 {
					 case LINE:
					 {
								  
								  object = new CLine(start,last);
								  object->Draw(graphics);

								  break;
					 }
					 case RECTANGLE:
					 {
									   object = new CRectangle(start,last);
									   object->Draw(graphics);

									   break;
					 }
					 case ELLIPSE:
					 {
									 object = new CEllipse(start,last);
									 object->Draw(graphics);

									 break;
					 }
					 }
					 delete graphics;
					 EndPaint(hWnd, &ps);
					 break;
	}
	case WM_DESTROY:
		GdiplusShutdown(gdiplusToken);
		DestroyFramework();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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
