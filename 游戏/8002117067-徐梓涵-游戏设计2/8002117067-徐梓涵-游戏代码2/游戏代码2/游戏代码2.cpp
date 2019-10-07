// 游戏代码2.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "游戏代码2.h"
#include <ctime>

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名


												//定义一个全局变量HDC
HDC hdc;
HDC hdc2;//兼容性句柄
HBITMAP hmap;//位图
RECT rect; //获取窗口大小
RECT rect2;//刷新窗口的判断
DWORD startY = 100;
DWORD startX = 200;

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
	LoadStringW(hInstance, IDC_MY2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHARK));
	wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_STARFISH));
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SHARK));

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

	if (!hWnd)
	{
		return FALSE;
	}
	//很关键的代码
	//获取窗口的DC内存的
	hdc = GetDC(hWnd);
	//上下文兼容的dc
	//
	hdc2 = CreateCompatibleDC(hdc);
	hmap = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	SelectObject(hdc2, hmap);
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
	
	srand((int)time(0));
	int ppap = rand() % 3;
	switch (message)
	{
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
		case IDA_Show:
			int IDI;
			hdc = GetDC(hWnd);

			for (int x = 0; x < 2000; x++)
			{
				for (int y = 0; y < 60; y++)
				{
					ppap = rand() % 3;
					if (ppap == 0) {
						IDI = IDI_ICON1;
					}
					if (ppap == 1) {
						IDI = IDI_ICON2;
					}
					if (ppap == 2) {
						IDI = IDI_ICON3;
					}
					
					DrawIcon(hdc2, x * 32, 32 * y, LoadIcon(hInst, MAKEINTRESOURCE(IDI)));
					
				}
				ReleaseDC(hWnd, hdc2);
				
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		//PAINTSTRUCT ps;
		//HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdc2, rect.left, rect.top, SRCCOPY);
		//EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc2);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//鼠标左键按下的操作
	case WM_LBUTTONDOWN:
	{
		//hdc;定义一个设备上下文的句柄
		int IDI;
		//srand((int)time(0));//生成随机种子
		if (ppap == 0) {
			IDI = IDI_ICON1;
		}
		if (ppap == 1) {
			IDI = IDI_ICON2;
		}
		if (ppap == 2) {
			IDI = IDI_ICON3;
		}
		//hdc = GetDC(hWnd);
		//hdc = GetDC(hWnd);
		DrawIcon(hdc2, LOWORD(lParam) - 16, HIWORD(lParam) - 16, LoadIcon(hInst, MAKEINTRESOURCE(IDI)));
		ReleaseDC(hWnd, hdc2);
	}
	break;
	case WM_MOUSEMOVE:
	{
		int IDI;
		//srand((int)time(0));//生成随机种子
		if (ppap == 0) {
			IDI = IDI_ICON1;
		}
		if (ppap == 1) {
			IDI = IDI_ICON2;
		}
		if (ppap == 2) {
			IDI = IDI_ICON3;
		}
		hdc = GetDC(hWnd);
		if (wParam == MK_LBUTTON)
		{
			DrawIcon(hdc2, LOWORD(lParam) - 16, HIWORD(lParam) - 16, LoadIcon(hInst, MAKEINTRESOURCE(IDI)));
		}
		ReleaseDC(hWnd, hdc2);
	}
	break;
	case WM_KEYDOWN:
	{
		int IDI;
		srand((int)time(0));//生成随机种子
		if (ppap == 0) {
			IDI = IDI_ICON1;
		}
		if (ppap == 1) {
			IDI = IDI_ICON2;
		}
		if (ppap == 2) {
			IDI = IDI_ICON3;
		}
		hdc = GetDC(hWnd);
		switch (wParam)
		{
		case VK_UP:
			startY -= 16;
			break;
		case VK_DOWN:
			startY += 16;
			break;
		case VK_LEFT:
			startX -= 16;
			break;
		case VK_RIGHT:
			startX += 16;
			break;
		}
		DrawIcon(hdc2, startX - 16, startY - 16, LoadIcon(hInst, MAKEINTRESOURCE(IDI)));
		ReleaseDC(hWnd, hdc2);
	}
	break;
	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		if (rect.right>rect2.right|| rect.bottom>rect2.bottom)
		{
			GetClientRect(hWnd, &rect2);
			BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdc2, rect.left, rect.top, SRCCOPY);
			hmap = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
			SelectObject(hdc2, hmap);
			BitBlt(hdc2, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdc, rect.left, rect.top, SRCCOPY);
		}
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
