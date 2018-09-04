// LianDianQi.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LianDianQi.h"

#define MAX_LOADSTRING 100
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
static WCHAR szSysTime[MAX_LOADSTRING];
static WCHAR szDateTimeFormat[MAX_LOADSTRING] = { L"HH:mm:ss" };
static CHAR szShutdown[MAX_LOADSTRING];
static WCHAR szPosOfCursor[MAX_LOADSTRING];
static WCHAR szStatusBarText[MAX_LOADSTRING];
static POINT pointofCursor;     //Screen Coordinate System
static SYSTEMTIME st;
static RECT rect = {45, 215, 144, 232};
static SYSTEMTIME stShutdown;
static HDC hdcStatus;
static WORD xPosOfCursor, yPosOfCursor;
static WORD cxClient, cyClient;
static WORD cxScreen, cyScreen;
//controls
static HWND hWndStatus;
static HWND hWndGroupBox_1;
static HWND hWndGroupBox_2;
static HWND hWndGroupBox_3;
static HWND hWndCheckBox_1;
static HWND hWndCheckBox_2;
static HWND hWndCheckBox_3;
static HWND hWndCheckBox_4;
static HWND hWndCheckBox_5;
static HWND hWndCheckBox_6;
static HWND hWndStatic_1;
static HWND hWndStatic_2;
static HWND hWndStatic_3;
static HWND hWndStatic_4;
static HWND hWndStatic_5;
static HWND hWndStatic_6;
static HWND hWndStatic_7;
static HWND hWndStatic_8;
static HWND hWndStatic_9;
static HWND hWndStatic_10;
static HWND hWndStatic_11;
static HWND hWndStatic_12;
static HWND hWndStatic_13;
static HWND hWndStatic_14;
static HWND hWndStatic_15;
static HWND hWndStatic_16;
static HWND hWndEdit_2;
static HWND hWndEdit_4;
static HWND hWndEdit_6;
static HWND hWndEdit_8;
static HWND hWndEdit_9;
static HWND hWndEdit_10;
static HWND hWndSpinBox_1;
static HWND hWndSpinBox_2;
static HWND hWndSpinBox_3;
static HWND hWndSpinBox_4;
static HWND hWndSpinBox_5;
static HWND hWndSpinBox_6;
static HWND hWndDateTime;
static HWND hWndButtonStartUp;
static HWND hWndButtonUndo;
//EditTime
static UINT editTime_1 = 1;
static UINT editTime_2 = 1;
static UINT editTime_3 = 1;
static UINT editTime_4 = 1;
static UINT editTime_5 = 1;
static UINT editTime_6 = 1;
//HOTKEY
static HWND hWndHotKeyStart;
static HWND hWndHotKeyStop;
static HWND hWndHotKey_1;
static HWND hWndHotKey_2;
static HWND hWndHotKey_3;
static HWND hWndHotKey_4;
//
static WORD hWndHotKey_1Value;
static WORD hWndHotKey_2Value;
static WORD hWndHotKey_3Value;
static WORD hWndHotKey_4Value;
//
static BYTE VK_1;
static BYTE VK_2;
static BYTE VK_3;
static BYTE VK_4;
//
static WORD hWndHotKeyStartValue;
static WORD hWndHotKeyStopValue;
//HOTKEYID
static ATOM hotKeyId = GlobalAddAtomW(L"hotKeyId_Shift_Z");
static ATOM hotKeyIdStart = GlobalAddAtomW(L"hotKeyId_StartHotkey");
static ATOM hotKeyIdStop = GlobalAddAtomW(L"hotKeyId_StopHotkey");
static ATOM hotKeyId_1 = GlobalAddAtomW(L"hotKeyId_1");
static ATOM hotKeyId_2 = GlobalAddAtomW(L"hotKeyId_2");
static ATOM hotKeyId_3 = GlobalAddAtomW(L"hotKeyId_3");
static ATOM hotKeyId_4 = GlobalAddAtomW(L"hotKeyId_4");

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
HWND DoCreateStatusBar(HWND hWndParent, int idStatus, HINSTANCE hInst, int cParts);
//
void leftMouseButtonUpDown(void);
void rightMouseButtonUpDown(void);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global Variables
	cxClient = 410;
	cyClient = 300;
	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LIANDIANQI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LIANDIANQI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	//
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LIANDIANQI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(240,240,240));
    wcex.lpszMenuName   = nullptr;  //MAKEINTRESOURCEW(IDC_LIANDIANQI)
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
      cxScreen/2, cyScreen/2, cxClient, cyClient, nullptr, nullptr, hInstance, nullptr);

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
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_HOTKEY:
	{
		if ((HIBYTE(hWndHotKeyStartValue) == (UINT)LOWORD(lParam)) && (LOBYTE(hWndHotKeyStartValue) == (UINT)HIWORD(lParam)))
		{
			if (SendMessageW(hWndCheckBox_1, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				VK_1 = (BYTE)hWndHotKey_1Value;
				SetTimer(hWnd, IDR_TIMER1, editTime_1, nullptr);
			}
			if (SendMessageW(hWndCheckBox_2, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				VK_2 = (BYTE)hWndHotKey_2Value;
				SetTimer(hWnd, IDR_TIMER2, editTime_2, nullptr);
			}
			if (SendMessageW(hWndCheckBox_3, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				VK_3 = (BYTE)hWndHotKey_3Value;
				SetTimer(hWnd, IDR_TIMER3, editTime_3, nullptr);
			}
			if (SendMessageW(hWndCheckBox_4, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				VK_4 = (BYTE)hWndHotKey_4Value;
				SetTimer(hWnd, IDR_TIMER4, editTime_4, nullptr);
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////
			if (SendMessageW(hWndCheckBox_5, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				SetTimer(hWnd, IDR_TIMER5, editTime_5, nullptr);
			}
			//
			if (SendMessageW(hWndCheckBox_6, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				SetTimer(hWnd, IDR_TIMER6, editTime_6, nullptr);
			}
			break;
		}
		//
		if ((HIBYTE(hWndHotKeyStopValue) == (UINT)LOWORD(lParam)) && (LOBYTE(hWndHotKeyStopValue) == (UINT)HIWORD(lParam)))
		{
			KillTimer(hWnd, IDR_TIMER1);
			//
			KillTimer(hWnd, IDR_TIMER2);
			//
			KillTimer(hWnd, IDR_TIMER3);
			//
			KillTimer(hWnd, IDR_TIMER4);
			//
			KillTimer(hWnd, IDR_TIMER5);
			KillTimer(hWnd, IDR_TIMER6);
			VK_1 = 0;
			VK_2 = 0;
			VK_3 = 0;
			VK_4 = 0;
			break;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (((UINT)LOWORD(lParam) == MOD_SHIFT) && ((UINT)HIWORD(lParam) == 'Z'))
		{
			GetCursorPos(&pointofCursor);
			InvalidateRect(hWnd, &rect, TRUE);
			break;
		}
		break;
	}
	case WM_CREATE:
	{
		HOTKEYF_SHIFT;
		//HOTKEY
		if (!RegisterHotKey(hWnd, hotKeyId, MOD_SHIFT, 'Z'))
			MessageBoxW(nullptr, L"Shift+Z has been occupied!", L"Warning", MB_OK | MB_ICONWARNING);
		//Timer
		SetTimer(hWnd, IDR_TIMERSTATUS, 100, nullptr);
		//StatusBar
		hWndStatus = DoCreateStatusBar(hWnd, IDR_STATUS, hInst, 3);
		hdcStatus = GetDC(hWndStatus);
		SetBkColor(hdcStatus, RGB(240, 240, 240));
		//GroupBox_1
		hWndGroupBox_1 = CreateWindowW(L"Button", L"", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_GROUPBOX,
			0, 0, 0, 0, hWnd, (HMENU)IDR_GROUPBOX_1, hInst, nullptr);
		//GroupBox_2
		hWndGroupBox_2 = CreateWindowW(L"Button", L"", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_GROUPBOX,
			0, 0, 0, 0, hWnd, (HMENU)IDR_GROUPBOX_2, hInst, nullptr);
		//GroupBox_3
		hWndGroupBox_3 = CreateWindowW(L"Button", L"", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_GROUPBOX,
			0, 0, 0, 0, hWnd, (HMENU)IDR_GROUPBOX_3, hInst, nullptr);
		//CheckBox_1
		hWndCheckBox_1 = CreateWindowW(L"Button", L"Valid", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			0, 0, 0, 0, hWnd, (HMENU)IDR_CHECKBOX_1, hInst, nullptr);
		//CheckBox_2
		hWndCheckBox_2 = CreateWindowW(L"Button", L"Valid", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			0, 0, 0, 0, hWnd, (HMENU)IDR_CHECKBOX_2, hInst, nullptr);
		//CheckBox_3
		hWndCheckBox_3 = CreateWindowW(L"Button", L"Valid", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			0, 0, 0, 0, hWnd, (HMENU)IDR_CHECKBOX_3, hInst, nullptr);
		//CheckBox_4
		hWndCheckBox_4 = CreateWindowW(L"Button", L"Valid", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			0, 0, 0, 0, hWnd, (HMENU)IDR_CHECKBOX_4, hInst, nullptr);
		//CheckBox_5
		hWndCheckBox_5 = CreateWindowW(L"Button", L"Valid", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			0, 0, 0, 0, hWnd, (HMENU)IDR_CHECKBOX_5, hInst, nullptr);
		//CheckBox_6
		hWndCheckBox_6 = CreateWindowW(L"Button", L"Valid", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			0, 0, 0, 0, hWnd, (HMENU)IDR_CHECKBOX_6, hInst, nullptr);
		//Static_1
		hWndStatic_1 = CreateWindowW(L"static", L"Interval:", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_1, hInst, nullptr);
		//Static_2
		hWndStatic_2 = CreateWindow(L"static", L"ms", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_2, hInst, nullptr);
		//Static_3
		hWndStatic_3 = CreateWindow(L"static", L"Interval:", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_3, hInst, nullptr);
		//Static_4
		hWndStatic_4 = CreateWindow(L"static", L"ms", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_4, hInst, nullptr);
		//Static_5
		hWndStatic_5 = CreateWindow(L"static", L"Interval:", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_5, hInst, nullptr);
		//Static_6
		hWndStatic_6 = CreateWindow(L"static", L"ms", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_6, hInst, nullptr);
		//Static_7
		hWndStatic_7 = CreateWindow(L"static", L"Interval:", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_7, hInst, nullptr);
		//Static_8
		hWndStatic_8 = CreateWindow(L"static", L"ms", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_8, hInst, nullptr);
		//Static_9
		hWndStatic_9 = CreateWindow(L"static", L"Left   Button:", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_9, hInst, nullptr);
		//Static_10
		hWndStatic_10 = CreateWindow(L"static", L"Right Button:", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_10, hInst, nullptr);
		//Static_11
		hWndStatic_11 = CreateWindow(L"static", L"ms", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_11, hInst, nullptr);
		//Static_12
		hWndStatic_12 = CreateWindow(L"static", L"ms", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_12, hInst, nullptr);
		//Static_13
		hWndStatic_13 = CreateWindow(L"static", L"Get By Shift+Z", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_13, hInst, nullptr);
		//Static_14
		hWndStatic_14 = CreateWindow(L"static", L"Timing Poweroff:", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_14, hInst, nullptr);
		//Static_15
		hWndStatic_15 = CreateWindow(L"static", L"Start Hotkey:", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_15, hInst, nullptr);
		//Static_16
		hWndStatic_16 = CreateWindow(L"static", L"Stop Hotkey:", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_STATIC_16, hInst, nullptr);
		//HotKey_1
		hWndHotKey_1 = CreateWindowW(HOTKEY_CLASSW, L"", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_HOTKEY_1, hInst, nullptr);
		//HotKey_2
		hWndHotKey_2 = CreateWindowW(HOTKEY_CLASSW, L"", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_HOTKEY_2, hInst, nullptr);
		//HotKey_3
		hWndHotKey_3 = CreateWindowW(HOTKEY_CLASSW, L"", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_HOTKEY_3, hInst, nullptr);
		//HotKey_4
		hWndHotKey_4 = CreateWindowW(HOTKEY_CLASSW, L"", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_HOTKEY_4, hInst, nullptr);
		SendMessageW(hWndHotKey_1, HKM_SETRULES, 
			HKCOMB_A | HKCOMB_C | HKCOMB_CA | HKCOMB_S | HKCOMB_SA | HKCOMB_SC | HKCOMB_SCA, 0);
		//Edit_2
		hWndEdit_2 = CreateWindowW(WC_EDITW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_UPPERCASE | ES_LEFT | ES_NUMBER,
			0, 0, 0, 0, hWnd, (HMENU)IDR_EDIT_2, hInst, nullptr);
		SendMessageW(hWndHotKey_2, HKM_SETRULES,
			HKCOMB_A | HKCOMB_C | HKCOMB_CA | HKCOMB_S | HKCOMB_SA | HKCOMB_SC | HKCOMB_SCA, 0);
		//Edit_4
		hWndEdit_4 = CreateWindowW(WC_EDITW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_UPPERCASE | ES_LEFT | ES_NUMBER,
			0, 0, 0, 0, hWnd, (HMENU)IDR_EDIT_4, hInst, nullptr);
		SendMessageW(hWndHotKey_3, HKM_SETRULES,
			HKCOMB_A | HKCOMB_C | HKCOMB_CA | HKCOMB_S | HKCOMB_SA | HKCOMB_SC | HKCOMB_SCA, 0);
		//Edit_6
		hWndEdit_6 = CreateWindowW(WC_EDITW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_UPPERCASE | ES_LEFT | ES_NUMBER,
			0, 0, 0, 0, hWnd, (HMENU)IDR_EDIT_6, hInst, nullptr);
		SendMessageW(hWndHotKey_4, HKM_SETRULES,
			HKCOMB_A | HKCOMB_C | HKCOMB_CA | HKCOMB_S | HKCOMB_SA | HKCOMB_SC | HKCOMB_SCA, 0);
		//Edit_8
		hWndEdit_8 = CreateWindowW(WC_EDITW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_UPPERCASE | ES_LEFT | ES_NUMBER,
			0, 0, 0, 0, hWnd, (HMENU)IDR_EDIT_8, hInst, nullptr);
		//Edit_9
		hWndEdit_9 = CreateWindowW(WC_EDITW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_UPPERCASE | ES_LEFT | ES_NUMBER,
			0, 0, 0, 0, hWnd, (HMENU)IDR_EDIT_9, hInst, nullptr);
		//Edit_10
		hWndEdit_10 = CreateWindowW(WC_EDITW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_UPPERCASE | ES_LEFT | ES_NUMBER,
			0, 0, 0, 0, hWnd, (HMENU)IDR_EDIT_10, hInst, nullptr);
		//SpinBox_1
		hWndSpinBox_1 = CreateUpDownControl(WS_VISIBLE | WS_CHILDWINDOW | UDS_SETBUDDYINT | UDS_ALIGNLEFT | UDS_NOTHOUSANDS | UDS_ARROWKEYS,
			0, 0, 0, 0, hWnd, IDR_SPINBOX_1, hInst, hWndEdit_2, 9999, 1, 0);
		//SpinBox_2
		hWndSpinBox_2 = CreateUpDownControl(WS_VISIBLE | WS_CHILDWINDOW | UDS_SETBUDDYINT | UDS_ALIGNLEFT | UDS_NOTHOUSANDS | UDS_ARROWKEYS,
			0, 0, 0, 0, hWnd, IDR_SPINBOX_2, hInst, hWndEdit_4, 9999, 1, 0);
		//SpinBox_3
		hWndSpinBox_3 = CreateUpDownControl(WS_VISIBLE | WS_CHILDWINDOW | UDS_SETBUDDYINT | UDS_ALIGNLEFT | UDS_NOTHOUSANDS | UDS_ARROWKEYS,
			0, 0, 0, 0, hWnd, IDR_SPINBOX_2, hInst, hWndEdit_6, 9999, 1, 0);
		//SpinBox_4
		hWndSpinBox_4 = CreateUpDownControl(WS_VISIBLE | WS_CHILDWINDOW | UDS_SETBUDDYINT | UDS_ALIGNLEFT | UDS_NOTHOUSANDS | UDS_ARROWKEYS,
			0, 0, 0, 0, hWnd, IDR_SPINBOX_2, hInst, hWndEdit_8, 9999, 1, 0);
		//SpinBox_5
		hWndSpinBox_5 = CreateUpDownControl(WS_VISIBLE | WS_CHILDWINDOW | UDS_SETBUDDYINT | UDS_ALIGNLEFT | UDS_NOTHOUSANDS | UDS_ARROWKEYS,
			0, 0, 0, 0, hWnd, IDR_SPINBOX_2, hInst, hWndEdit_9, 9999, 1, 0);
		//SpinBox_6
		hWndSpinBox_6 = CreateUpDownControl(WS_VISIBLE | WS_CHILDWINDOW | UDS_SETBUDDYINT | UDS_ALIGNLEFT | UDS_NOTHOUSANDS | UDS_ARROWKEYS,
			0, 0, 0, 0, hWnd, IDR_SPINBOX_2, hInst, hWndEdit_10, 9999, 1, 0);
		//DateTime
		hWndDateTime = CreateWindowW(DATETIMEPICK_CLASSW, L"", WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT,
			0, 0, 0, 0, hWnd, (HMENU)IDR_DATETIME, hInst, nullptr);
		//StartUp
		hWndButtonStartUp = CreateWindowW(WC_BUTTONW, L"Start up", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 0, 0, hWnd, (HMENU)IDR_BUTTONSTARTUP, hInst, nullptr);
		//Undo
		hWndButtonUndo = CreateWindowW(WC_BUTTONW, L"Undo", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 0, 0, hWnd, (HMENU)IDR_BUTTONUNDO, hInst, nullptr);
		//HotKeyStart
		hWndHotKeyStart = CreateWindowW(HOTKEY_CLASSW, L"", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_HOTKEYSTART, hInst, nullptr);
		SendMessageW(hWndHotKeyStart, HKM_SETRULES,
			HKCOMB_A | HKCOMB_C | HKCOMB_CA | HKCOMB_S | HKCOMB_SA | HKCOMB_SC | HKCOMB_SCA, 0);
		//HotKeyStop
		hWndHotKeyStop = CreateWindowW(HOTKEY_CLASSW, L"", WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU)IDR_HOTKEYSTOP, hInst, nullptr);
		SendMessageW(hWndHotKeyStop, HKM_SETRULES,
			HKCOMB_A | HKCOMB_C | HKCOMB_CA | HKCOMB_S | HKCOMB_SA | HKCOMB_SC | HKCOMB_SCA, 0);
		break;
	}
	case WM_TIMER:
	{
		if (wParam == IDR_TIMERSTATUS)
		{
			TextOutW(hdcStatus, 5, 5, L"Version: 1.0.0", wcslen(L"Version: 1.0.0"));
			//
			GetLocalTime(&st);
			TextOutW(hdcStatus, 320, 5, szSysTime, wcslen(szSysTime));
			if (st.wSecond % 2 == 0)
				wsprintfW(szSysTime, L"%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
			else
				wsprintfW(szSysTime, L"%02d:%02d %02d", st.wHour, st.wMinute, st.wSecond);
			break;
		}
		if (wParam == IDR_TIMER1)
		{
			static INPUT input[2];
			memset(input, 0, 2 * sizeof(INPUT));
			input[0].type = INPUT_KEYBOARD;
			input[0].ki.wVk = VK_1;
			SendInput(1, &input[0], sizeof(INPUT));
			input[1].type = INPUT_KEYBOARD;
			input[1].ki.wVk = VK_1;
			input[1].ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &input[1], sizeof(INPUT));
			break;
		}
		if (wParam == IDR_TIMER2)
		{
			static INPUT input[2];
			memset(input, 0, 2 * sizeof(INPUT));
			input[0].type = INPUT_KEYBOARD;
			input[0].ki.wVk = VK_2;
			SendInput(1, &input[0], sizeof(INPUT));
			input[1].type = INPUT_KEYBOARD;
			input[1].ki.wVk = VK_2;
			input[1].ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &input[1], sizeof(INPUT));
			break;
		}
		if (wParam == IDR_TIMER3)
		{
			static INPUT input[2];
			memset(input, 0, 2 * sizeof(INPUT));
			input[0].type = INPUT_KEYBOARD;
			input[0].ki.wVk = VK_3;
			SendInput(1, &input[0], sizeof(INPUT));
			input[1].type = INPUT_KEYBOARD;
			input[1].ki.wVk = VK_3;
			input[1].ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(2, input, sizeof(INPUT));
			SendInput(1, &input[1], sizeof(INPUT));
			break;
		}
		if (wParam == IDR_TIMER4)
		{
			static INPUT input[2];
			memset(input, 0, 2 * sizeof(INPUT));
			input[0].type = INPUT_KEYBOARD;
			input[0].ki.wVk = VK_4;
			SendInput(1, &input[0], sizeof(INPUT));
			input[1].type = INPUT_KEYBOARD;
			input[1].ki.wVk = VK_4;
			input[1].ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(2, input, sizeof(INPUT));
			SendInput(1, &input[1], sizeof(INPUT));
			break;
		}
		if (wParam == IDR_TIMER5)
		{
			leftMouseButtonUpDown();
			break;
		}
		if (wParam == IDR_TIMER6)
		{
			rightMouseButtonUpDown();
			break;
		}
		break;
	}
	case WM_SIZE:
	{
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		//
		MoveWindow(hWndStatus, 0, 0, 0, 0, TRUE);
		//
		MoveWindow(hWndGroupBox_1, 243, 0, 1, 235, TRUE);
		MoveWindow(hWndGroupBox_2, 245, 120, 145, 9, TRUE);
		MoveWindow(hWndGroupBox_3, 2, 130, 235, 9, TRUE);
		//
		MoveWindow(hWndCheckBox_1, 10, 14, 53, 18, TRUE);
		MoveWindow(hWndCheckBox_2, 10, 45, 53, 18, TRUE);
		MoveWindow(hWndCheckBox_3, 10, 76, 53, 18, TRUE);
		MoveWindow(hWndCheckBox_4, 10, 107, 53, 18, TRUE);
		MoveWindow(hWndCheckBox_5, 10, 153, 53, 18, TRUE);
		MoveWindow(hWndCheckBox_6, 10, 184, 53, 18, TRUE);
		//
		MoveWindow(hWndHotKey_1, 67, 12, 25, 24, TRUE);
		MoveWindow(hWndEdit_2, 154, 12, 40, 24, TRUE);
		MoveWindow(hWndHotKey_2, 67, 43, 25, 24, TRUE);
		MoveWindow(hWndEdit_4, 154, 43, 40, 24, TRUE);
		MoveWindow(hWndHotKey_3, 67, 74, 25, 24, TRUE);
		MoveWindow(hWndEdit_6, 154, 74, 40, 24, TRUE);
		MoveWindow(hWndHotKey_4, 67, 105, 25, 24, TRUE);
		MoveWindow(hWndEdit_8, 154, 105, 40, 24, TRUE);
		MoveWindow(hWndEdit_9, 154, 151, 40, 24, TRUE);
		MoveWindow(hWndEdit_10, 154, 182, 40, 24, TRUE);
		//
		MoveWindow(hWndStatic_1, 96, 14, 54, 20, TRUE);
		MoveWindow(hWndStatic_2, 214, 14, 20, 20, TRUE);
		MoveWindow(hWndStatic_3, 96, 45, 54, 20, TRUE);
		MoveWindow(hWndStatic_4, 214, 45, 20, 20, TRUE);
		MoveWindow(hWndStatic_5, 96, 76, 54, 20, TRUE);
		MoveWindow(hWndStatic_6, 214, 76, 20, 20, TRUE);
		MoveWindow(hWndStatic_7, 96, 107, 54, 20, TRUE);
		MoveWindow(hWndStatic_8, 214, 107, 20, 20, TRUE);
		MoveWindow(hWndStatic_9, 67, 153, 84, 20, TRUE);
		MoveWindow(hWndStatic_10, 67, 184, 84, 20, TRUE);
		MoveWindow(hWndStatic_11, 214, 153, 20, 20, TRUE);
		MoveWindow(hWndStatic_12, 214, 184, 20, 20, TRUE);
		MoveWindow(hWndStatic_13, 144, 215, 95, 18, TRUE);
		MoveWindow(hWndStatic_14, 250, 14, 110, 20, TRUE);
		MoveWindow(hWndStatic_15, 250, 138, 110, 20, TRUE);
		MoveWindow(hWndStatic_16, 250, 192, 110, 20, TRUE);
		//
		MoveWindow(hWndSpinBox_1, 194, 12, 15, 26, TRUE);
		MoveWindow(hWndSpinBox_2, 194, 43, 15, 26, TRUE);
		MoveWindow(hWndSpinBox_3, 194, 74, 15, 26, TRUE);
		MoveWindow(hWndSpinBox_4, 194, 105, 15, 26, TRUE);
		MoveWindow(hWndSpinBox_5, 194, 151, 15, 26, TRUE);
		MoveWindow(hWndSpinBox_6, 194, 182, 15, 26, TRUE);
		//
		MoveWindow(hWndButtonStartUp, 250, 90, 60, 30, TRUE);
		MoveWindow(hWndButtonUndo, 320, 90, 60, 30, TRUE);
		//
		MoveWindow(hWndHotKeyStart, 250, 162, 140, 25, TRUE);
		MoveWindow(hWndHotKeyStop, 250, 215, 140, 25, TRUE);
		//
		MoveWindow(hWndDateTime, 250, 50, 140, 25, TRUE);
		SendMessageW(hWndDateTime, DTM_SETFORMAT, 0, (UINT)szDateTimeFormat);
		break;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case IDR_EDIT_2:
			{
				if (HIWORD(wParam) == EN_CHANGE)
				{
					static BOOL bl;
					editTime_1 = GetDlgItemInt(hWnd, IDR_EDIT_2, &bl, FALSE);
				}
				break;
			}
			case IDR_EDIT_4:
			{
				if (HIWORD(wParam) == EN_CHANGE)
				{
					static BOOL bl;
					editTime_2 = GetDlgItemInt(hWnd, IDR_EDIT_4, &bl, FALSE);
				}
				break;
			}
			case IDR_EDIT_6:
			{
				if (HIWORD(wParam) == EN_CHANGE)
				{
					static BOOL bl;
					editTime_3 = GetDlgItemInt(hWnd, IDR_EDIT_6, &bl, FALSE);
				}
				break;
			}
			case IDR_EDIT_8:
			{
				if (HIWORD(wParam) == EN_CHANGE)
				{
					static BOOL bl;
					editTime_4 = GetDlgItemInt(hWnd, IDR_EDIT_8, &bl, FALSE);
				}
				break;
			}
			case IDR_EDIT_9:
			{
				if (HIWORD(wParam) == EN_CHANGE)
				{
					static BOOL bl;
					editTime_5 = GetDlgItemInt(hWnd, IDR_EDIT_9, &bl, FALSE);
				}
				break;
			}
			case IDR_EDIT_10:
			{
				if (HIWORD(wParam) == EN_CHANGE)
				{
					static BOOL bl;
					editTime_6 = GetDlgItemInt(hWnd, IDR_EDIT_10, &bl, FALSE);
				}
				break;
			}
			case IDR_HOTKEYSTART:
			{
				hWndHotKeyStartValue = LOWORD(SendMessageW(hWndHotKeyStart, HKM_GETHOTKEY, 0, 0)); //SendMessage return 4 bytes
				UnregisterHotKey(hWnd, hotKeyIdStart);
				if (!RegisterHotKey(hWnd, hotKeyIdStart, 0, LOBYTE(hWndHotKeyStartValue)))
					MessageBoxW(hWnd, L"HotKey has been occupied!", L"Warning", MB_OK | MB_ICONWARNING);
				break;
			}
			case IDR_HOTKEYSTOP:
			{
				hWndHotKeyStopValue = LOWORD(SendMessageW(hWndHotKeyStop, HKM_GETHOTKEY, 0, 0));
				UnregisterHotKey(hWnd, hotKeyIdStop);
				if(!RegisterHotKey(hWnd, hotKeyIdStop, 0, LOBYTE(hWndHotKeyStopValue)))
					MessageBoxW(hWnd, L"HotKey has been occupied!", L"Wraning", MB_OK | MB_ICONWARNING);
				break;
			}
			case IDR_HOTKEY_1:
			{
				hWndHotKey_1Value = LOWORD(SendMessageW(hWndHotKey_1, HKM_GETHOTKEY, 0, 0));
				break;
			}
			case IDR_CHECKBOX_1:
			{
				if (SendMessageW(hWndCheckBox_1, BM_GETCHECK, 0, 0) == BST_CHECKED)
					SendMessageW(hWndCheckBox_1, BM_SETCHECK, BST_UNCHECKED, 0);
				else
					SendMessageW(hWndCheckBox_1, BM_SETCHECK, BST_CHECKED, 0);
				break;
			}
			case IDR_HOTKEY_2:
			{
				hWndHotKey_2Value = LOWORD(SendMessageW(hWndHotKey_2, HKM_GETHOTKEY, 0, 0));
				break;
			}
			case IDR_CHECKBOX_2:
			{
				if (SendMessageW(hWndCheckBox_2, BM_GETCHECK, 0, 0) == BST_CHECKED)
					SendMessageW(hWndCheckBox_2, BM_SETCHECK, BST_UNCHECKED, 0);
				else
					SendMessageW(hWndCheckBox_2, BM_SETCHECK, BST_CHECKED, 0);
				break;
			}
			case IDR_HOTKEY_3:
			{
				hWndHotKey_3Value = LOWORD(SendMessageW(hWndHotKey_3, HKM_GETHOTKEY, 0, 0));
				break;
			}
			case IDR_CHECKBOX_3:
			{
				if (SendMessageW(hWndCheckBox_3, BM_GETCHECK, 0, 0) == BST_CHECKED)
					SendMessageW(hWndCheckBox_3, BM_SETCHECK, BST_UNCHECKED, 0);
				else
					SendMessageW(hWndCheckBox_3, BM_SETCHECK, BST_CHECKED, 0);
				break;
			}
			case IDR_HOTKEY_4:
			{
				hWndHotKey_4Value = LOWORD(SendMessageW(hWndHotKey_4, HKM_GETHOTKEY, 0, 0));
				break;
			}
			case IDR_CHECKBOX_4:
			{
				if (SendMessageW(hWndCheckBox_4, BM_GETCHECK, 0, 0) == BST_CHECKED)
					SendMessageW(hWndCheckBox_4, BM_SETCHECK, BST_UNCHECKED, 0);
				else
					SendMessageW(hWndCheckBox_4, BM_SETCHECK, BST_CHECKED, 0);
				break;
			}
			case IDR_CHECKBOX_5:
			{
				if (SendMessageW(hWndCheckBox_5, BM_GETCHECK, 0, 0) == BST_CHECKED)
					SendMessageW(hWndCheckBox_5, BM_SETCHECK, BST_UNCHECKED, 0);
				else
					SendMessageW(hWndCheckBox_5, BM_SETCHECK, BST_CHECKED, 0);
				break;
			}
			case IDR_CHECKBOX_6:
			{
				if (SendMessageW(hWndCheckBox_6, BM_GETCHECK, 0, 0) == BST_CHECKED)
					SendMessageW(hWndCheckBox_6, BM_SETCHECK, BST_UNCHECKED, 0);
				else
					SendMessageW(hWndCheckBox_6, BM_SETCHECK, BST_CHECKED, 0);
				break;
			}
			case IDR_BUTTONSTARTUP:
			{
				if (SendMessageW(hWndDateTime, DTM_GETSYSTEMTIME, 0, (UINT)&stShutdown) == GDT_VALID)
				{
					int stSecondsToShutdown = (stShutdown.wHour - st.wHour) * 3600 + (stShutdown.wMinute - st.wMinute) * 60 + (stShutdown.wSecond - st.wSecond);
					sprintf_s(szShutdown, sizeof(szShutdown), "shutdown -f -s -t %d", (stSecondsToShutdown+24*3600)%(24*3600));
					system("net start Task Scheduler");
					system(szShutdown);
				}
				break;
			}
			case IDR_BUTTONUNDO:
			{
				system("net start Task Scheduler");
				system("shutdown -a");
				break;
			}
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here..
			SetBkColor(hdc, RGB(240,240,240));
			wsprintfW(szPosOfCursor, L"(%d,%d)", pointofCursor.x, pointofCursor.y);
			TextOutW(hdc, 45, 215, szPosOfCursor, wcslen(szPosOfCursor));
			//
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
	{
		ReleaseDC(hWndStatus, hdcStatus);
		KillTimer(hWnd, IDR_TIMERSTATUS);
		//
		GlobalDeleteAtom(hotKeyId);
		GlobalDeleteAtom(hotKeyIdStart);
		GlobalDeleteAtom(hotKeyIdStop);
		//
		UnregisterHotKey(hWnd, hotKeyId);
		UnregisterHotKey(hWnd, hotKeyIdStart);
		UnregisterHotKey(hWnd, hotKeyIdStop);
		//
		PostQuitMessage(0);
		break;
	}
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HWND DoCreateStatusBar(HWND hWndParent, int idStatus, HINSTANCE hInst, int cParts)
{
	HWND hwndStatus;
	HLOCAL hloc;
	PINT paParts;

	// Ensure that the common control DLL is loaded.
	InitCommonControls();

	// Create the status bar.
	hwndStatus = CreateWindowEx(
		0,                       // no extended styles
		STATUSCLASSNAME,         // name of status bar class
		(PCTSTR)NULL,           // no text when first created       
		WS_CHILD | WS_VISIBLE,   // creates a visible child window
		0, 0, 0, 0,              // ignores size and position
		hWndParent,              // handle to parent window
		(HMENU)idStatus,       // child window identifier
		hInst,                   // handle to application instance
		NULL);                   // no window creation data

								 // Get the coordinates of the parent window's client area.

	// Allocate an array for holding the right edge coordinates.
	hloc = LocalAlloc(LHND, sizeof(int) * cParts);
	paParts = (PINT)LocalLock(hloc);
	//
	paParts[0] = cxClient / 4;
	paParts[1] = cxClient / 4 * 3;
	paParts[2] = cxClient;

	// Tell the status bar to create the window parts.
	SendMessage(hwndStatus, SB_SETPARTS, (WPARAM)cParts, (LPARAM)paParts);

	// Free the array, and return.
	LocalUnlock(hloc);
	LocalFree(hloc);
	return hwndStatus;
}

void leftMouseButtonUpDown(void)
{
	static INPUT input[2];
	memset(input, 0, 2 * sizeof(INPUT));
	input[0].type = INPUT_MOUSE;
	input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input[0], sizeof(INPUT));
	input[1].type = INPUT_MOUSE;
	input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input[1], sizeof(INPUT));
}

void rightMouseButtonUpDown(void)
{
	static INPUT input[2];
	memset(input, 0, 2 * sizeof(INPUT));
	input[0].type = INPUT_MOUSE;
	input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &input[0], sizeof(INPUT));
	input[1].type = INPUT_MOUSE;
	input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &input[0], sizeof(INPUT));
}
