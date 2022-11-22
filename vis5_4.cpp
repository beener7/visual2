#include <windows.h>
#include <TCHAR.h>
#include "resource.h"

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG		 msg;
	WNDCLASS WndClass;

	WndClass.lpszMenuName = NULL;

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	hInst = hInstance;
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);  	// 커서 지정

	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	static HBITMAP hBitmap;
	static RECT rectView;
	static int x, y;
	static int stepx, stepy;
	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		x = 0; y = 0;
		stepx = 10;
		stepy = 10;
		return 0;

	case WM_PAINT:
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDOK));
		hdc = BeginPaint(hwnd, &ps);
		memdc = CreateCompatibleDC(hdc);

		GetClientRect(hwnd, &rectView);

		SelectObject(memdc, hBitmap);
		StretchBlt(hdc, x, y, 150,75, memdc, 0, 0, 1280, 720, SRCCOPY);
		if (x+150 > rectView.right)
			stepx *= -1;
		if (x < rectView.left)
			stepx *= -1;
		if (y+75 > rectView.bottom)
			stepy *= -1;
		if (y < rectView.top)
			stepy *= -1;
		DeleteDC(memdc); 
		EndPaint(hwnd, &ps);
		break;


	case WM_LBUTTONDOWN:
		SetTimer(hwnd, 1, 10, NULL);
		break;

	case WM_TIMER:
		x += stepx;
		y += stepy;
		InvalidateRect(hwnd, NULL, TRUE);

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
