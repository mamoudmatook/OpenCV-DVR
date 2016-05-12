// Win32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <iostream>
#include "Win32.h"
#include "VideoRecorder.h"

#define MAX_LOADSTRING 100

#define IDC_RECORD_BUTTON 110
#define IDC_PLAY_BUTTON 111
#define IDC_REWIND_BUTTON 112
#define IDC_FORWARD_BUTTON 113
#define IDC_STOP_BUTTON 114
#define IDC_EQUALIZE_RADIO 115
#define IDC_COLOR_BUTTON 116
#define IDC_GRAY_BUTTON 117

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

VideoRecorder* vr;
bool IsOk;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

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

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
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

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32);
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 110, 200, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   IsOk = false;
   std::string filepath = "C:\\users\\david\\";
   std::string fileExtension = ".avi";
   std::string fileName = "test";
   
   vr = new VideoRecorder();
   vr->SetVideo(filepath + fileName + fileExtension, 20, vr->GetFrameSize());
   SetTimer(hWnd, 100, 33, (TIMERPROC)NULL);
   

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
	{
		HWND hWndRecordButton = CreateWindowEx(NULL,
			L"BUTTON",
			L"Record",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			5,
			5,
			100,
			24,
			hWnd,
			(HMENU)IDC_RECORD_BUTTON,
			GetModuleHandle(NULL),
			NULL);
		HWND hWndRewindButton = CreateWindowEx(NULL,
			L"BUTTON",
			L"Rewind",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			5,
			30,
			100,
			24,
			hWnd,
			(HMENU)IDC_REWIND_BUTTON,
			GetModuleHandle(NULL),
			NULL);
		HWND hWndForwardButton = CreateWindowEx(NULL,
			L"BUTTON",
			L"Forward",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			5,
			55,
			100,
			24,
			hWnd,
			(HMENU)IDC_FORWARD_BUTTON,
			GetModuleHandle(NULL),
			NULL);
		HWND hWndPlayButton = CreateWindowEx(NULL,
			L"BUTTON",
			L"Play",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			5,
			80,
			100,
			24,
			hWnd,
			(HMENU)IDC_PLAY_BUTTON,
			GetModuleHandle(NULL),
			NULL);
		HWND hWndStopButton = CreateWindowEx(NULL,
			L"BUTTON",
			L"Stop",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			5,
			105,
			100,
			24,
			hWnd,
			(HMENU)IDC_STOP_BUTTON,
			GetModuleHandle(NULL),
			NULL);
		HWND hWndColorButton = CreateWindowEx(NULL,
			L"BUTTON",
			L"Color",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			5,
			130,
			100,
			24,
			hWnd,
			(HMENU)IDC_COLOR_BUTTON,
			GetModuleHandle(NULL),
			NULL);
		HWND hWndBlackButton = CreateWindowEx(NULL,
			L"BUTTON",
			L"Blanco y negro",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			5,
			155,
			100,
			24,
			hWnd,
			(HMENU)IDC_GRAY_BUTTON,
			GetModuleHandle(NULL),
			NULL);
		HWND hWndEqualizeCheckbox = CreateWindowEx(NULL,
			L"BUTTON",
			L"Equalizar",
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
			5,
			180,
			100,
			24,
			hWnd,
			(HMENU)IDC_EQUALIZE_RADIO,
			GetModuleHandle(NULL),
			NULL);
		CheckDlgButton(hWnd, IDC_EQUALIZE_RADIO, BST_UNCHECKED);
	}
		break;
	case WM_COMMAND:
	{
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_RECORD_BUTTON:
		{
			if (vr->Command == VideoRecorder::eRecord) {
				vr->Command = VideoRecorder::eNothing;
			}
			else{
				vr->Command = VideoRecorder::eRecord;
			}
		}
			break;
		case IDC_PLAY_BUTTON:
			vr->Command = VideoRecorder::ePlay;
			break;
		case IDC_REWIND_BUTTON:
			vr->Command = VideoRecorder::eRewind;
			break;
		case IDC_FORWARD_BUTTON:
			vr->Command = VideoRecorder::eForward;
			break;
		case IDC_COLOR_BUTTON:
			vr->IsColored = true;
			break;
		case IDC_GRAY_BUTTON:
			vr->IsColored = false;
			break;
		case IDC_EQUALIZE_RADIO:
		{
			BOOL checked = IsDlgButtonChecked(hWnd, IDC_EQUALIZE_RADIO);
			if (checked)
			{
				vr->IsEqualized = false;
				CheckDlgButton(hWnd, IDC_EQUALIZE_RADIO, BST_UNCHECKED);
			}
			else
			{
				vr->IsEqualized = true;
				CheckDlgButton(hWnd, IDC_EQUALIZE_RADIO, BST_CHECKED);
			}
		}
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		delete vr;
		PostQuitMessage(0);
		KillTimer(hWnd, 100);
		break;
	case WM_TIMER: 
	{
		if (vr->Command == VideoRecorder::eRecord || vr->Command == VideoRecorder::eNothing) {
			if (vr->Capture())
			{
				IsOk = true;
			}
		}

		switch (vr->Command)
		{
		case VideoRecorder::eRecord:
			vr->Record();
			break;
		case VideoRecorder::eRewind:
			vr->Rewind();
			break;
		case VideoRecorder::eForward:
			vr->FastForward();
			break;
		case VideoRecorder::ePlay:
			vr->Play();
			break;
		default:
			break;
		}

		if (IsOk) 
		{
			vr->Show();
		}
		break;
	}
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