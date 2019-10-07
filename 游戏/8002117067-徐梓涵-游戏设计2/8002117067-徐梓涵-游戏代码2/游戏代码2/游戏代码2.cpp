// ��Ϸ����2.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "��Ϸ����2.h"
#include <ctime>

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������


												//����һ��ȫ�ֱ���HDC
HDC hdc;
HDC hdc2;//�����Ծ��
HBITMAP hmap;//λͼ
RECT rect; //��ȡ���ڴ�С
RECT rect2;//ˢ�´��ڵ��ж�
DWORD startY = 100;
DWORD startX = 200;

// �˴���ģ���а����ĺ�����ǰ������: 
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

	// TODO: �ڴ˷��ô��롣

	// ��ʼ��ȫ���ַ���
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2));

	MSG msg;

	// ����Ϣѭ��: 
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	//�ܹؼ��Ĵ���
	//��ȡ���ڵ�DC�ڴ��
	hdc = GetDC(hWnd);
	//�����ļ��ݵ�dc
	//
	hdc2 = CreateCompatibleDC(hdc);
	hmap = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	SelectObject(hdc2, hmap);
	return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
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
		// �����˵�ѡ��: 
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
		// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
		BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdc2, rect.left, rect.top, SRCCOPY);
		//EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc2);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//���������µĲ���
	case WM_LBUTTONDOWN:
	{
		//hdc;����һ���豸�����ĵľ��
		int IDI;
		//srand((int)time(0));//�����������
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
		//srand((int)time(0));//�����������
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
		srand((int)time(0));//�����������
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

// �����ڡ������Ϣ�������
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
