#include <windows.h>
#include <TCHAR.h>
#include "resource.h"

#define LINE 1
#define ELLIPSE 2
#define RECTANGLE 3

Object *inform[200];
static int i;
class Point
{
private:
	int x;
	int y;
public:
	Point() :x(0), y(0) {}
	Point(int xx, int yy) :x(xx), y(yy) {}
	int GetX() { return x; }
	int GetY() { return y; }
	void Set(int x1, int y1) { x = x1; y = y1; }
};

class Object
{

public:
	Point sp, ep;
	Object() {}
	Object(int x1, int y1, int x2, int y2) { sp.Set(x1, y1); ep.Set(x2, y2); }
	virtual void Draw(HDC hdc){}
};

class Line : public Object
{
private:

public:
	Line():Object(0,0,0,0){}
	Line(int x1, int y1, int x2, int y2) :Object(x1, y1, x2, y2) {}
	void inputsp(int x1, int y1) { sp.Set(x1, y1); }
	void inputep(int x1, int y1) { ep.Set(x1, y1); }
	void Draw(HDC hdc);
	void set(int x1,int y1, int x2,int y2){}
};

class Circle : public Object
{
private:

public:
	Circle(int x1, int y1, int x2, int y2) :Object(x1, y1, x2, y2) {}
	void Draw();
};

void Line::Draw(HDC hdc)
{
	MoveToEx(hdc, sp.GetX(), sp.GetY(), NULL);
	LineTo(hdc, ep.GetX(), ep.GetY());
}

void Circle::Draw()
{
}


COLORREF ColorSelection(HWND hwnd, COLORREF oldColor)
{
	COLORREF tmp[16];
	CHOOSECOLOR COLOR;
	for (int i = 0; i < 16; i++)
		tmp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);

	memset(&COLOR, 0, sizeof(CHOOSECOLOR));
	COLOR.lStructSize = sizeof(CHOOSECOLOR);
	COLOR.hwndOwner = hwnd;
	COLOR.lpCustColors = tmp;
	COLOR.Flags = CC_FULLOPEN;

	if (ChooseColor(&COLOR) != 0)
		return COLOR.rgbResult;
	else
		return oldColor;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG		 msg;
	WNDCLASS WndClass;

	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

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
	HDC hdc;
	PAINTSTRUCT ps;
	CHOOSECOLOR PENCOLOR, BRUSHCOLOR;
	static COLORREF pen, brush;
	static int object_mode;
	static COLORREF tmp[16], color = 0;
	static HBRUSH hBrush, OldBrush;
	static HPEN hPen, oldPen;
	static BOOL Drag;
	static int startX, startY,oldX,oldY;
	int endX, endY;
	int answer;
	Line a;

	switch (iMsg)
	{
	case WM_CREATE:
		i = 0;
		pen = 0x00FFFFFF;
		brush = 0x00000000;
		Drag = FALSE;
		return 0;

	case WM_PAINT:
		return 0;


	case WM_COMMAND:
		hdc = BeginPaint(hwnd, &ps);
		switch (LOWORD(wParam))
		{
		case ID_LINE:
			object_mode = LINE;
			break;

		case ID_ELLIPSE:
			object_mode = ELLIPSE;
			break;
		case ID_RECTANGLE:
			object_mode = RECTANGLE;
			break;

		case ID_PENCOLOR:
			color = ColorSelection(hwnd, pen);
			hPen = CreatePen(LINECAPS, 2, color);
			oldPen = (HPEN)SelectObject(hdc, hPen);
			break;

		case ID_FACECOLOR:
			color = ColorSelection(hwnd, brush);
			hBrush = CreateSolidBrush(color);
			OldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			break;

		case ID_FILENEW:
			MessageBox(hwnd, _T("새 파일을 열겠습니까 ? "), _T("새파일 선택"), MB_OKCANCEL);
			break;
		case ID_EXIT:
			answer = MessageBox(hwnd, _T("파일을 저장하고 끝내겠습니까 ?"), _T("끝내기 선택"), MB_YESNOCANCEL);
			if (answer == IDYES || answer == IDNO)
				PostQuitMessage(0);;
			break;


		}
		break;

	case WM_LBUTTONDOWN:
		a.inputsp(LOWORD(lParam), HIWORD(lParam));
		Drag = TRUE;
		oldX = startX = LOWORD(lParam);
		oldY = startY = HIWORD(lParam);

		break;


	case WM_MOUSEMOVE:
		if (Drag)
		{
			hdc = GetDC(hwnd);
			SetROP2(hdc, R2_NOTXORPEN);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			switch (object_mode)
			{
			case LINE:

				endX = LOWORD(lParam);
				endY = HIWORD(lParam);

				MoveToEx(hdc, startX, startY, NULL);
				LineTo(hdc, oldX, oldY);

				MoveToEx(hdc, startX, startY, NULL);
				LineTo(hdc, endX, endY);

				oldX = endX;
				oldY = endY;

				break;
			case ELLIPSE:

				endX = LOWORD(lParam);
				endY = HIWORD(lParam);

				Ellipse(hdc, startX, startY, oldX, oldY);

				Ellipse(hdc, startX, startY, endX, endY);

				oldX = endX;
				oldY = endY;
				break;
			case RECTANGLE:
				endX = LOWORD(lParam);
				endY = HIWORD(lParam);

				Rectangle(hdc, startX, startY, oldX, oldY);

				Rectangle(hdc, startX, startY, endX, endY);

				oldX = endX;
				oldY = endY;

				break;
			}
			ReleaseDC(hwnd, hdc);
		}
		return 0;




	case WM_LBUTTONUP:
		a.inputep(LOWORD(lParam), HIWORD(lParam));
		Drag = FALSE;

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
