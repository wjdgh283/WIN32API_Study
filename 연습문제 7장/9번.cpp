#include <Windows.h>
#include<tchar.h>
#include<string.h>
#include<math.h>
//#include"resource.h"
//#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;

	hInst = hInstance;
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

	hwnd = CreateWindow(
		_T("Window Class Name"),
		_T("박정호"),
		WS_OVERLAPPEDWINDOW,
		50,
		50,
		1000,
		500,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
#define IDC_COMBO1 100
#define IDC_COMBO2 101
#define IDC_COMBO3 102
#define IDC_COMBO4 103
#define IDC_COMBO5 104

#define IDC_COMBO6 105
#define IDC_COMBO7 106
#define IDC_COMBO8 107
#define IDC_COMBO9 108
#define IDC_COMBO10 109
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND hCombo[10];
	static TCHAR BusStop[16][10] = { _T("역전") , _T("시장") , _T("초등학교") , _T("중학교") , _T("고등학교") , _T("대학교") , _T("터미널") , _T("아파트") , _T("백화점") , _T("병원") , _T("전철역") , _T("경찰서") , _T("소방서") , _T("구청") , _T("시청") , _T("동사무소") };
	RECT rect;
	switch (iMsg)
	{
	case WM_CREATE:
		for (int i = 0; i < 5; i++)
			hCombo[i] = (HWND)CreateWindow(_T("combobox"), NULL, WS_CHILD | CBS_DROPDOWN | CBS_NOINTEGRALHEIGHT, i * 160, 100, 100, 400, hwnd, (HMENU)(100 + i), hInst, NULL);
		for (int i = 0; i < 5; i++)
			hCombo[5 + i] = (HWND)CreateWindow(_T("combobox"), NULL, WS_CHILD | CBS_DROPDOWN | CBS_NOINTEGRALHEIGHT, 640 - i * 160, 300, 100, 400, hwnd, (HMENU)(100 + i), hInst, NULL);
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 16; j++)
				SendMessage(hCombo[i], CB_ADDSTRING, 0, (LPARAM)BusStop[j]);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		MoveToEx(hdc, 0, 110, NULL);
		LineTo(hdc, 700, 110);

		MoveToEx(hdc, 700, 110, NULL);
		LineTo(hdc, 700, 310);

		MoveToEx(hdc, 700, 310, NULL);
		LineTo(hdc, 0, 310);
		for (int i = 0; i < 5; i++)
			Rectangle(hdc, i * 160, 100, i * 160 + 100, 120);
		for (int i = 0; i < 5; i++)
			Rectangle(hdc, 640 - i * 160, 300, 640 - i * 160 + 100, 320);
		EndPaint(hwnd, &ps);
		break;
	case WM_RBUTTONDOWN:
		for (int i = 0; i < 5; i++)
		{
			if (LOWORD(lParam) > 160 * i&&LOWORD(lParam) < 160 * i + 100 && HIWORD(lParam) > 100 && HIWORD(lParam) < 120)
			{
				ShowWindow(hCombo[i], SW_SHOW);
				break;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			if (LOWORD(lParam) > 640 - i * 160 && LOWORD(lParam) < 640 - i * 160 + 100 && HIWORD(lParam) > 300 && HIWORD(lParam) < 320)
			{
				ShowWindow(hCombo[i + 5], SW_SHOW);
				break;
			}
		}
		break;
	case WM_COMMAND:
		hdc = GetDC(hwnd);
		if (LOWORD(wParam) - 100 < 5)
			rect = { (LOWORD(wParam) - 100) * 160,80,(LOWORD(wParam) - 100) * 160 + 100,120 };
		else
			rect = { 640 - (LOWORD(wParam) - 105) * 160,280,640 - (LOWORD(wParam) - 105) * 160 + 100,320 };

		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			DrawText(hdc, BusStop[SendMessage(hCombo[LOWORD(wParam) - 100], CB_GETCURSEL, 0, 0)], _tcslen(BusStop[SendMessage(hCombo[LOWORD(wParam) - 100], CB_GETCURSEL, 0, 0)]), &rect, DT_TOP | DT_CENTER);
			ShowWindow(hCombo[LOWORD(wParam) - 100], SW_HIDE);
		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}