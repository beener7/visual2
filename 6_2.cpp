#include <windows.h>
#include <TCHAR.h>
#include"resource.h"

#define IDD_DIALOG1 101

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam); 
BOOL CALLBACK Dlg6_2Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG		 msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	hInst = hInstance;
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);  	// 커서 지정

	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
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


BOOL CALLBACK Dlg6_2Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	switch (iMessage) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) { // msg 발생한 컨트롤 ID
		case ID_START:
			hdc = GetDC(hDlg); // 대화상자(hDlg)에 출력하는 dc 생성
			TextOut(hdc, 0, 0,_T("start World"), 11);
			ReleaseDC(hDlg, hdc);
			break;
		case ID_PAUSE:
			hdc = GetDC(hDlg); // 대화상자(hDlg)에 출력하는 dc 생성
			TextOut(hdc, 0, 0, _T("pause World"), 11);
			ReleaseDC(hDlg, hdc);
			break;
		case ID_CLOSE:
			EndDialog(hDlg, 0); // 대화상자 종료
			break;
		}
		break;
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	switch (iMsg) {
	case WM_CREATE: break;
	case WM_LBUTTONDOWN:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, Dlg6_2Proc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
