#include <windows.h>
#include "stdafx.h"
#include "Resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK InputNumberProc(HWND, UINT, WPARAM, LPARAM);

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
	static HINSTANCE hInstance;

	switch (iMsg)
	{

	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		buffer[0] = '\0';
		globalBuffer[0] = '\0';
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_INPUT:
			if (DialogBox(hInstance, "AboutBox", hwnd,
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
		SetDlgItemText(hDlg, ID_NUMBER, buffer);
		return FALSE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			for (int i = 0; i < 12; i++)
				globalBuffer[i] = buffer[i];
			globalCounter = counter;
			EndDialog(hDlg, TRUE);
			return TRUE;
		case IDCANCEL:
			for (int i = 0; i < 12; i++)
				buffer[i] = globalBuffer[i];
			counter = globalCounter;
			EndDialog(hDlg, FALSE);
			return TRUE;
		case IDCLEAR:
			buffer[0] = '\0';
			counter = 0;
			SetDlgItemText(hDlg, ID_NUMBER, buffer);
			UpdateWindow(hDlg);
			return TRUE; 
		case ID_1:
			if (counter < 11)
			{
				buffer[counter + 1] = '\0';
				buffer[counter] = '1';
				counter++;
				SetDlgItemText(hDlg, ID_NUMBER, buffer);
				UpdateWindow(hDlg);
			}
			return TRUE;
		case ID_2:
			if (counter < 11)
			{
				buffer[counter + 1] = buffer[counter];
				buffer[counter] = '2';
				counter++;
				SetDlgItemText(hDlg, ID_NUMBER, buffer);
				UpdateWindow(hDlg);
			}
			return TRUE;
		case ID_3:
			if (counter < 11)
			{
				buffer[counter + 1] = buffer[counter];
				buffer[counter] = '3';
				counter++;
				SetDlgItemText(hDlg, ID_NUMBER, buffer);
				UpdateWindow(hDlg);
			}
			return TRUE;
		case ID_4:
			if (counter < 11)
			{
				buffer[counter + 1] = buffer[counter];
				buffer[counter] = '4';
				counter++;
				SetDlgItemText(hDlg, ID_NUMBER, buffer);
				UpdateWindow(hDlg);
			}
			return TRUE;
		case ID_5:
			if (counter < 11)
			{
				buffer[counter + 1] = buffer[counter];
				buffer[counter] = '5';
				counter++;
				SetDlgItemText(hDlg, ID_NUMBER, buffer);
				UpdateWindow(hDlg);
			}
			return TRUE;
		case ID_6:
			if (counter < 11)
			{
				buffer[counter + 1] = buffer[counter];
				buffer[counter] = '6';
				counter++;
				SetDlgItemText(hDlg, ID_NUMBER, buffer);
				UpdateWindow(hDlg);
			}
			return TRUE;
		case ID_7:
			if (counter < 11)
			{
				buffer[counter + 1] = buffer[counter];
				buffer[counter] = '7';
				counter++;
				SetDlgItemText(hDlg, ID_NUMBER, buffer);
				UpdateWindow(hDlg);
			}
			return TRUE;
		case ID_8:
			if (counter < 11)
			{
				buffer[counter + 1] = buffer[counter];
				buffer[counter] = '8';
				counter++;
				SetDlgItemText(hDlg, ID_NUMBER, buffer);
				UpdateWindow(hDlg);
			}
			return TRUE;
		case ID_9:
			if (counter < 11)
			{
				buffer[counter + 1] = buffer[counter];
				buffer[counter] = '9';
				counter++;
				SetDlgItemText(hDlg, ID_NUMBER, buffer);
				UpdateWindow(hDlg);
			}
			return TRUE;
		case ID_0:
			if (counter < 11)
			{
				buffer[counter + 1] = buffer[counter];
				buffer[counter] = '0';
				counter++;
				SetDlgItemText(hDlg, ID_NUMBER, buffer);
				UpdateWindow(hDlg);
			}
			return TRUE;
		}
		break;

		return FALSE;
	}
}
