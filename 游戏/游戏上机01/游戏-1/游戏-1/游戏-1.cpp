// 游戏-1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "游戏-1.h"
#include "SimpleFile.h"
#include <commdlg.h>  //OPNEFILENAME 需要的头文件
#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst; 

//创建文本框代码
RECT rect;

//窗口全局变量
HWND hWnd;

// 当前实例句柄
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

//设置一个flag记录是否第一次保存
int flag = 1;

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//新添加上的三个变量声明
vecLinesContainer fileLines;// 读取的文件内容
HWND hWndEdit;// 文本框句柄
WCHAR currentFile[260];      //  文件名 

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
    LoadStringW(hInstance, IDC_MY1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	int x = rect.left;
	int y = rect.right;
	int z = rect.top;
	int u = rect.bottom;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		//获得窗口的大小
		GetClientRect(hWnd, &rect);
		if (rect.left != x || rect.right != y || rect.top != z || rect.bottom != u)
		{
			//更新当前坐标
			x = rect.left;
			y = rect.right;
			z = rect.top;
			u = rect.bottom;
			//更新当前的文本框的大小
			MoveWindow(hWndEdit, rect.left + 5, rect.top+5, rect.right - 10, rect.bottom - 10, TRUE);
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1);
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

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   GetClientRect(hWnd, &rect); 
   hWndEdit = CreateWindowW(
	   L"EDIT", L"这是一个简单的文本编辑器。（用来理解WIN32 API 方式下的消息机制）",
	   WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE | 
	   ES_WANTRETURN | WS_VSCROLL | ES_AUTOVSCROLL,
	   rect.left + 5, rect.top + 5, 
	   rect.right - 10, rect.bottom - 10, 
	   hWnd, nullptr, hInstance, nullptr);
   HFONT hFont = CreateFont(
	   24, 0, 0, 0, 300, false, false, false,
	   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
	   CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
	   DEFAULT_PITCH, L"微软雅黑"); 
   //
   SendMessage(hWndEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
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
	OPENFILENAME ofn;   // OpenFile通用结构体 
	WCHAR szFile[260] = { 0 };  // 文件名 
	int cTxtLen;      // 文本长度 
	WCHAR* allFileLines; //文本内容
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
			case IDM_OPEN:
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFile = currentFile;
				ofn.nMaxFile = sizeof(currentFile);
				ofn.lpstrFilter = _T("ALL\0*.*\0Text\0*.TXT\0");
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
				if (GetOpenFileName(&ofn) == TRUE)
				{
					SetWindowText(hWnd, ofn.lpstrFile);
					SimpleFile simplefile;
					fileLines = simplefile.getFileLines(ofn.lpstrFile);

					vecLinesContainer::iterator it;
					std::wstring allLines = L"";
					for (it = fileLines.begin(); it != fileLines.end(); it++)
					{
						allLines.append(*it);
						allLines.append(L"\r\n");
					}
					SetWindowText(hWndEdit, allLines.c_str());
				}
				flag = 0;
				break;
			case IDM_SAVE:
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = _T("ALL\0*.*\0Text\0*.TXT\0");
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
				if (flag == 1)
				{
					MessageBox(NULL, L"由于还没有文件位置，请您添加您的文件保存位置", L"保存提示", MB_OK);  //通用对话框
					if (GetSaveFileName(&ofn) == TRUE)
					{
						cTxtLen = GetWindowTextLength(hWndEdit);
						allFileLines = (LPWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1),
							MEM_COMMIT, PAGE_READWRITE);
						GetWindowText(hWndEdit, allFileLines, cTxtLen + 1);
						if (allFileLines != NULL)
						{
							SimpleFile simplefile;
							simplefile.WriteFile(ofn.lpstrFile, allFileLines);
							flag = 0;
						}
					}
				}else {
					SetWindowText(hWnd, currentFile);
					cTxtLen = GetWindowTextLength(hWndEdit);
					allFileLines = (LPWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1),
						MEM_COMMIT, PAGE_READWRITE);
					GetWindowText(hWndEdit, allFileLines, cTxtLen + 1);
					if (allFileLines != NULL)
					{
						SimpleFile simplefile;
						simplefile.WriteFile(currentFile, allFileLines);
					}
				}
				break;
			case IDM_NEW: {
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = _T("ALL\0*.*\0Text\0*.TXT\0");
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
				//保存当前的文件，如果当前的文件还没有文件路径对当前的文件进行保存
				if (flag == 1)
				{
					MessageBox(NULL, L"由于还没有文件位置，请您添加您的文件保存位置，才可以新建文件", L"新建的保存提示", MB_OK);  //通用对话框
					if (GetSaveFileName(&ofn) == TRUE)
					{
						cTxtLen = GetWindowTextLength(hWndEdit);
						allFileLines = (LPWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1),
							MEM_COMMIT, PAGE_READWRITE);
						GetWindowText(hWndEdit, allFileLines, cTxtLen + 1);
						if (allFileLines != NULL)
						{
							SimpleFile simplefile;
							simplefile.WriteFile(ofn.lpstrFile, allFileLines);
							flag = 0;
						}
					}
				}
				//保存当前的文件，如果当前文件是有路径的，就直接对当前的文件进行保存
				else {
					SetWindowText(hWnd, currentFile);
					cTxtLen = GetWindowTextLength(hWndEdit);
					allFileLines = (LPWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1),
						MEM_COMMIT, PAGE_READWRITE);
					GetWindowText(hWndEdit, allFileLines, cTxtLen + 1);
					if (allFileLines != NULL)
					{
						SimpleFile simplefile;
						simplefile.WriteFile(currentFile, allFileLines);
					}
				}
				//保存完成之后将当前的文本清空
				SetWindowText(hWndEdit, _T(""));
				//接下来选择需要保存的地方
				MessageBox(NULL, L"保存完成，接下来请您选择你新建的文件位置", L"选择新建位置", MB_OK);  //通用对话框
				if (GetSaveFileName(&ofn) == TRUE)
				{
					cTxtLen = GetWindowTextLength(hWndEdit);
					allFileLines = (LPWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1),
						MEM_COMMIT, PAGE_READWRITE);
					GetWindowText(hWndEdit, allFileLines, cTxtLen + 1);
					if (allFileLines != NULL)
					{
						SimpleFile simplefile;
						simplefile.WriteFile(ofn.lpstrFile, allFileLines);
					}
				}
				flag = 0;  //设置当前的文件是有位置的
			}
				break;
			case IDM_SAVEAS:
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = _T("ALL\0*.*\0Text\0*.TXT\0");
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
				if (GetSaveFileName(&ofn) == TRUE)
				{
					cTxtLen = GetWindowTextLength(hWndEdit);
					allFileLines = (LPWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1),
						MEM_COMMIT, PAGE_READWRITE);
					GetWindowText(hWndEdit, allFileLines, cTxtLen + 1);
					if (allFileLines != NULL)
					{
						SimpleFile simplefile;
						simplefile.WriteFile(ofn.lpstrFile, allFileLines);
					}
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
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
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
