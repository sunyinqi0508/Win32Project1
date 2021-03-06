// Win32Project1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Win32Project1.h"
#include <deque>
#include <cstring>

#define MAX_LOADSTRING 100

#define ID_ButtonC 3311
#define ID_ButtonQ 3310
#define ID_Button1 3312
#define ID_Edit 3313
#define ID_Editx2 3313
#define ID_Edity1 3314
#define ID_Edity2 3315
std::deque<int> x1s, y1s, x2s, y2s;
// 全局变量: 
HINSTANCE hInst;                                // 当前实例
HWND hButton, hEditx1, hEditx2, hEdity1, hEdity2, hButtonC, hButtonQ, hWindow;
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

inline int stepper_p(int x) {
	return x++;
}
inline int stepper_n(int x) {
	return x--;
}
inline void _SetPixel_p(HDC hDC, int x1, int y1, COLORREF color) {
	SetPixelV(hDC, x1, y1, color);
}
inline void _SetPixel_n(HDC hDC, int y1, int x1, COLORREF color){
	SetPixelV(hDC, x1, y1, color);
}
inline void _DrawLine(HDC hdc, int x1, int y1, int dx, int dy, int stepper_x(int x), int stepper_y(int y), void DrawPixel(HDC hDC, int y1, int x1, COLORREF color)) {
	int d1 = 2 * dy - 2 * dx, d2 = 2 * dy;
	int seg = d1 + dx;
	int x2 = x1 + dx;
	while (x1 < x2)
	{
		x1++;
		if (seg > 0) {
			seg += d1;
			y1++;
		}
		else
			seg += d2;
		DrawPixel(hdc, x1, y1, COLORREF(RGB(0, 0, 0)));
	}
}
void DrawLine(HDC hDC, int x1, int x2, int y1, int y2){
	int dx = x2 - x1, dy = y2 - y1;
	if (fabs(dx) > fabs(dy))
		if(dx > 0 )
			if(dy > 0)
				_DrawLine(hDC, x1, y1,dx, dy, stepper_p, stepper_p, _SetPixel_p);
			else
				_DrawLine(hDC, x1, y1, dx, dy, stepper_p, stepper_n, _SetPixel_p);
		else
			if(dy > 0)
				_DrawLine(hDC, x1, y1, dx, dy, stepper_n, stepper_p, _SetPixel_p);
			else
				_DrawLine(hDC, x1, y1, dx, dy, stepper_n, stepper_n, _SetPixel_p);
	else
		if (dx > 0)
			if (dy > 0)
				_DrawLine(hDC, y1, x1, dx, dy, stepper_p, stepper_p, _SetPixel_n);
			else
				_DrawLine(hDC, y1, x1, dx, dy, stepper_p, stepper_n, _SetPixel_n);
		else
			if (dy > 0)
				_DrawLine(hDC, y1, x1, dx, dy, stepper_n, stepper_p, _SetPixel_n);
			else
				_DrawLine(hDC, y1, x1, dx, dy, stepper_n, stepper_n, _SetPixel_n);
}
inline int myatoi(LPWSTR str) {
	int i = -1, ans = 0;
	while (str[++i]) {
		ans *= 10;
		ans += str[i] - '0';
	}
	return ans;
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   hWindow = hWnd;
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		LOGFONT LogFont, LogFont1;
		memset(&LogFont, 0, sizeof(LOGFONT));
		lstrcpy(LogFont.lfFaceName, L"Segoe UI Light");
		LogFont.lfWeight = FW_BLACK;//FW_NORMAL; 
		LogFont.lfCharSet = 134;
		LogFont.lfOutPrecision = 3;
		LogFont.lfClipPrecision = 2;
		LogFont.lfOrientation = 45;
		LogFont.lfHeight = -24;
		LogFont.lfQuality = ANTIALIASED_QUALITY| PROOF_QUALITY;
		LogFont.lfPitchAndFamily = 2;
		
		memset(&LogFont1, 0, sizeof(LOGFONT));
		lstrcpy(LogFont1.lfFaceName, L"Segoe UI");
		LogFont1.lfWeight = FW_NORMAL;//FW_NORMAL; 
		LogFont1.lfCharSet = 134;
		LogFont1.lfOutPrecision = 3;
		LogFont1.lfClipPrecision = 2;
		LogFont1.lfOrientation = 45;
		LogFont.lfHeight = -18;  
		LogFont1.lfQuality = ANTIALIASED_QUALITY| PROOF_QUALITY;
		LogFont1.lfPitchAndFamily = 2;
		HFONT hFont = CreateFontIndirect(&LogFont), hFont1 = CreateFontIndirect(&LogFont1);
		
		hButton = CreateWindow(L"Button", L"Draw.", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 900, 600, 160, 65, hWnd, (HMENU)ID_Button1, hInst, NULL);
		hButtonC = CreateWindow(L"Button", L"Clear", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 1070, 600, 160, 65, hWnd, (HMENU)ID_ButtonC, hInst, NULL);
		hButtonQ = CreateWindow(L"Button", L"Quit", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 1240, 600, 160, 65, hWnd, (HMENU)ID_ButtonQ, hInst, NULL);
		hEditx1 = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 800, 600, 80, 30, hWnd, (HMENU)ID_Edit, hInst, NULL);
		hEditx2 = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 800, 635, 80, 30, hWnd, (HMENU)ID_Editx2, hInst, NULL);
		hEdity1 = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 700, 600, 80, 30, hWnd, (HMENU)ID_Edity1, hInst, NULL);
		hEdity2 = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 700, 635, 80, 30, hWnd, (HMENU)ID_Edity2, hInst, NULL);

		SendMessage(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(hButtonQ, WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(hButtonC, WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(hEditx1, WM_SETFONT, (WPARAM)hFont1, TRUE);
		SendMessage(hEditx2, WM_SETFONT, (WPARAM)hFont1, TRUE);
		SendMessage(hEdity1, WM_SETFONT, (WPARAM)hFont1, TRUE);
		SendMessage(hEdity2, WM_SETFONT, (WPARAM)hFont1, TRUE);
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_Button1:
			{
				WCHAR *str = new WCHAR[10000];
				GetWindowText(hEditx1, str, 10000);
				x1s.push_back(myatoi(str));
				GetWindowText(hEditx2, str, 10000);
				x2s.push_back(myatoi(str));
				GetWindowText(hEdity1, str, 10000);
				y1s.push_back(myatoi(str));
				GetWindowText(hEdity2, str, 10000);
				y2s.push_back(myatoi(str));

				RECT rect;
				GetWindowRect(hWnd, &rect);
				InvalidateRect(hWnd, &rect, true);
				UpdateWindow(hWnd);
			}
			break;
			case ID_ButtonC: {
				x1s.clear();
				x2s.clear();
				y1s.clear();
				y2s.clear();
				RECT rect;
				GetWindowRect(hWnd, &rect);
				InvalidateRect(hWnd, &rect, true);
				UpdateWindow(hWnd);
			}
			break;
			case ID_ButtonQ:
			{
				SendMessage(hWindow, WM_COMMAND, IDM_EXIT, NULL);
			}
				break;
			default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
	        PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
    
			std::deque<int>::iterator itx1 = x1s.begin(), ity1 = y1s.begin(), itx2 = x2s.begin(), ity2 = y2s.begin();
			while (itx1 != x1s.end()) {
				DrawLine(hdc, *itx1, *itx2, *ity1, *ity2);
				itx2++;
				ity2++;
				itx1++;
				ity1++;
			}
			
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
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
