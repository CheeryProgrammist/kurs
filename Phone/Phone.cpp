#include <windows.h>
#include "stdafx.h"
#include "Resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL	CALLBACK InputNumberProc(HWND, UINT, WPARAM, LPARAM);
BOOL	PutNumber(HWND, char *, int &, char);

HINSTANCE appHInstance;
char globalBuffer[12];
int globalCounter = 0;
char buffer[12];
int counter = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static char  szAppName[] = "Phone";
	MSG          msg;
	WNDCLASSEX   wndclass;
	HWND          hwnd;
	appHInstance = hInstance;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, szAppName);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = szAppName;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(hInstance, szAppName);

	RegisterClassEx(&wndclass);
	hwnd = CreateWindow(szAppName, "Phone",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		200, 100,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK  WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:

		buffer[0] = '\0';
		globalBuffer[0] = '\0';
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_INPUT:
			if (DialogBox(appHInstance, "InputNumber", hwnd,
				InputNumberProc))
				InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case IDM_EXIT:
			PostQuitMessage(0);
			return 0;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

BOOL CALLBACK InputNumberProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_INITDIALOG:
		strcpy_s(buffer, globalBuffer);
		counter = globalCounter;
		return SetDlgItemText(hDlg, ID_NUMBER, buffer);

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			strcpy_s(globalBuffer, buffer);
			globalCounter = counter;
			return EndDialog(hDlg, TRUE);

		case IDCANCEL:
			return EndDialog(hDlg, FALSE);

		case IDCLEAR:
			buffer[0] = '\0';
			counter = 0;
			return SetDlgItemText(hDlg, ID_NUMBER, buffer);

		case ID_1:
			return PutNumber(hDlg, buffer, counter, '1');
		case ID_2:
			return PutNumber(hDlg, buffer, counter, '2');
		case ID_3:
			return PutNumber(hDlg, buffer, counter, '3');
		case ID_4:
			return PutNumber(hDlg, buffer, counter, '4');
		case ID_5:
			return PutNumber(hDlg, buffer, counter, '5');
		case ID_6:
			return PutNumber(hDlg, buffer, counter, '6');
		case ID_7:
			return PutNumber(hDlg, buffer, counter, '7');
		case ID_8:
			return PutNumber(hDlg, buffer, counter, '8');
		case ID_9:
			return PutNumber(hDlg, buffer, counter, '9');
		case ID_0:
			return PutNumber(hDlg, buffer, counter, '0');
		}
		break;
	}
	return FALSE;
}

BOOL PutNumber(HWND hDlg, char *buffer, int &counter, char digit)
{
	if (counter >= 11)
		return false;
	buffer[counter++] = digit;
	buffer[counter] = '\0';
	return SetDlgItemText(hDlg, ID_NUMBER, buffer);
}