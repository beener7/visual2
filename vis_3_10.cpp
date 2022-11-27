#include <windows.h>
#include <TCHAR.H>
#include <atlstr.h>
#include <time.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	hwnd;
	MSG 	msg;
	WNDCLASS	WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
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



#define ITEMNUM 5

int board[31][31];
int wormX[50], wormY[50];
int xDirect, yDirect, len;
int point = 48;
int size = 31;

void ItemGenerator()
{
	srand(time(NULL));
	int i, x, y;
	for (i = 0; i < ITEMNUM; i++)
	{
		x = rand() % (size-1) + 1;
		y = rand() % (size-1) + 1;
		if (board[y][x] == 0)
			board[y][x] = 2;
		else
		{
			i = i - 1;
			continue;
		}
	}
	return;
}


void DrawGameBoard(HDC hdc)
{
	int i, x, y;
	for (y = 0; y < size; y++) {
		for (x = 0; x < size; x++)
		{
			switch (board[y][x])
			{
			case -1:
				Rectangle(hdc, x * 20, y * 20, (x + 1) * 20, (y + 1) * 20);
				break;
			case 2:
				SelectObject(hdc, GetStockObject(BLACK_BRUSH));
				Ellipse(hdc, x * 20, y * 20, (x + 1) * 20, (y + 1) * 20);
				SelectObject(hdc, GetStockObject(WHITE_BRUSH));
				break;
			}
		}
	}

	SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(255, 0, 0)));
	Ellipse(hdc, wormX[0] * 20, wormY[0] * 20, (wormX[0] + 1) * 20, (wormY[0] + 1) * 20); //대가리
	SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(0, 0, 255)));

	for (i = 1; i < len; i++)
		Ellipse(hdc, wormX[i] * 20, wormY[i] * 20, (wormX[i] + 1) * 20, (wormY[i] + 1) * 20);
}


void GameInit()
{
	int i;
	for (i = 0; i < size; i++)
	{
		board[i][0] = -1;
		board[i][size-1] = -1;
		board[0][i] = -1;
		board[size-1][i] = -1;
	}
	wormX[0] = 2; wormY[0] = 1;
	wormX[1] = 1; wormY[1] = 1;
	board[wormY[0]][wormX[0]] = 3;
	board[wormY[1]][wormX[1]] = 3;

	ItemGenerator();

	len = 2;
	xDirect = 1; yDirect = 0;
}

void restart(HWND hwnd)
{
	int i,j;
	for(i = 0;i<size;i++ )
	{
		for(j = 0;j<size;j++)
		{
			board[j][i] = 0;
		}
	}
	for (i = 0; i < 50; i++) {
		wormX[i] = 0;
		wormY[i] = 0;
	}
	point = 0;
	GameInit();
	SetTimer(hwnd, 1, 100, NULL);
	SetTimer(hwnd, 2, 10000, NULL);
}

void DirectControl(int DirectKey)
{
	switch (DirectKey) {
	case VK_LEFT:
		if (xDirect == 1)
			break;
		if (board[wormY[0]][wormX[0] - 1] != -1)
		{
			xDirect = -1;
			yDirect = 0;
		}
		break;
	case VK_RIGHT:
		if (xDirect == -1)
			break;
		if (board[wormY[0]][wormX[0] + 1] != -1)
		{
			xDirect = 1;
			yDirect = 0;
		}
		break;
	case VK_UP:
		if (yDirect == 1)
			break;
		if (board[wormY[0] - 1][wormX[0]] != -1)
		{
			xDirect = 0;
			yDirect = -1;
		}
		break;
	case VK_DOWN:
		if (yDirect == -1)
			break;
		if (board[wormY[0] + 1][wormX[0]] != -1)
		{
			xDirect = 0;
			yDirect = 1;
		}
		break;
	}
}


void MovingWorm(HWND hwnd,HDC hdc)
{
	int save;
	int tmpx, tmpy, i;
	tmpx = wormX[0];
	tmpy = wormY[0];
	wormX[0] += xDirect; wormY[0] += yDirect;

	if (board[wormY[0]][wormX[0]] == -1 || board[wormY[0]][wormX[0]] == 3)
	{
		KillTimer(hwnd, 1);
		KillTimer(hwnd, 2);
		save = MessageBox(0, L"다시 시도하시겠습니까?", L"죽음!!", MB_RETRYCANCEL);
		if (save == 2) { exit(0); }
		else if(save == 4)
		{
			restart(hwnd);
			tmpx = 2;
			tmpy = 1;
		}
		wormX[0] = tmpx;
		wormY[0] = tmpy;
	}
	else
	{
		if (board[wormY[0]][wormX[0]] == 2)
		{
			point++; // 점수추가
			len = len + 1;
			board[wormY[0]][wormX[0]] = 0;
			if(point > 50)
			{
				KillTimer(hwnd, 1);
				KillTimer(hwnd, 2);
				save = MessageBox(0, L"축하드립니다 성공하셨습니다.", L"클리어!", MB_RETRYCANCEL);
				if (save == 2) { exit(0); }
				else if (save == 4)
				{
					restart(hwnd);
					tmpx = 2;
					tmpy = 1;
				}

			}
		}
		else
			board[wormY[len - 1]][wormX[len - 1]] = 0;

		for (i = len - 1; i > 1; i--)
		{
			wormX[i] = wormX[i - 1];
			wormY[i] = wormY[i - 1];
		}
		wormX[1] = tmpx;
		wormY[1] = tmpy;
		board[wormY[0]][wormX[0]] = 3;
	}
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	CString P;
	static RECT rectView;
	static int save;

	switch (iMsg) {
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		GameInit();
		SetTimer(hwnd, 1, 100, NULL);
		SetTimer(hwnd, 2, 10000, NULL);
		return 0;
	case WM_PAINT:
		GetClientRect(hwnd, &rectView);
		hdc = BeginPaint(hwnd, &ps);
		P.Format(_T("%d"), point);
		TextOut(hdc, rectView.left + 20, rectView.bottom - 20, L"점수:", 3);
		TextOut(hdc, rectView.left + 60, rectView.bottom - 20, P, P.GetLength());
		DrawGameBoard(hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		DirectControl((int)wParam);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			hdc = BeginPaint(hwnd, &ps);
			MovingWorm(hwnd, hdc);
			InvalidateRgn(hwnd, NULL, TRUE);
			break;
		case 2:
			ItemGenerator();
			break;
		}
		return 0;

	case WM_DESTROY:
		KillTimer(hwnd, 1);
		KillTimer(hwnd, 2);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
