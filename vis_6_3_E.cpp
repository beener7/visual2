#include <windows.h>
#include <TCHAR.h>
#include"resource.h"

#define IDD_DIALOG1 101

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_2Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_3Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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


/*BOOL CALLBACK Dlg6_2Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	switch (iMessage) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) { // msg 발생한 컨트롤 ID
		case ID_START:
			hdc = GetDC(hDlg); // 대화상자(hDlg)에 출력하는 dc 생성
			TextOut(hdc, 0, 0, _T("start World"), 11);
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
*/
/*BOOL CALLBACK Dlg6_3Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HWND hButton; // 버튼 컨트롤 핸들 저장용
	switch(iMsg){
	case WM_INITDIALOG:
		hButton = GetDlgItem(hDlg, ID_PAUSE);
		EnableWindow(hButton, FALSE); // 최초 정지 버튼은 비활성화break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			case ID_START: // 시작 버튼
				hButton = GetDlgItem(hDlg, ID_START);
				EnableWindow(hButton, FALSE); // 시작버튼 비활성화
				hButton = GetDlgItem(hDlg, ID_PAUSE);
				EnableWindow(hButton, TRUE); // 정지버튼 활성화
				break;
			case ID_PAUSE: // 정지 버튼
				hButton = GetDlgItem(hDlg, ID_START);
				EnableWindow(hButton, TRUE); // 시작버튼 활성화
				hButton = GetDlgItem(hDlg, ID_PAUSE);
				EnableWindow(hButton, FALSE); // 정지버튼 비활성화
				break;
			case ID_CLOSE: // 종료 버튼
				EndDialog(hDlg, 0); break;
			case IDCANCEL:
				EndDialog(hDlg, 0); break;
			}
			break;
		}
	return 0;
}*/

BOOL CALLBACK DIgEx6_3Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR num1[20], num2[20], answer[20]; double number1, number2, result;
	switch(iMsg)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_PLUS:
			GetDlgItemText(hDlg, IDC_EDIT_NUM1, num1, 20);
			GetDlgItemText(hDlg, IDC_EDIT_NUM2, num2, 20);
			number1 = _ttof(num1); number2 = _ttof(num2); result = number1 + number2;
			_stprintf_s(answer, _T("%f"), result);
			SetDlgItemText(hDlg, IDC_EDIT_ANSWER, answer);
			break;
		case ID_MINUS:
			GetDlgItemText(hDlg, IDC_EDIT_NUM1, num1, 20);
			GetDlgItemText(hDlg, IDC_EDIT_NUM2, num2, 20);
			number1 = _ttof(num1); number2 = _ttof(num2); result = number1 - number2;
			_stprintf_s(answer, _T("%f"), result);
			SetDlgItemText(hDlg, IDC_EDIT_ANSWER, answer);
			break;
		case ID_MULTI:
			GetDlgItemText(hDlg, IDC_EDIT_NUM1, num1, 20);
			GetDlgItemText(hDlg, IDC_EDIT_NUM2, num2, 20);
			number1 = _ttof(num1); number2 = _ttof(num2); result = number1 * number2;
			_stprintf_s(answer, _T("%f"), result);
			SetDlgItemText(hDlg, IDC_EDIT_ANSWER, answer);
			break;
		case ID_DIVIDE:
			GetDlgItemText(hDlg, IDC_EDIT_NUM1, num1, 20);
			GetDlgItemText(hDlg, IDC_EDIT_NUM2, num2, 20);
			number1 = _ttof(num1); number2 = _ttof(num2); result = number1 / number2;
			_stprintf_s(answer, _T("%f"), result);
			SetDlgItemText(hDlg, IDC_EDIT_ANSWER, answer);
			break;
		case IDCLOSE:
		case IDCANCEL: EndDialog(hDlg, 0); break;
		}
		break;
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	switch (iMsg) {
	case WM_CREATE: break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_6_3_MENU: // 메뉴 한 항목 ID
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DIgEx6_3Proc);
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
