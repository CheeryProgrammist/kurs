#include <windows.h>
#include "stdafx.h"
#include "Resource.h"

// Объявления сигнатур функций
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);			// Функция обработки сообщений главного окна приложения
BOOL	CALLBACK InputNumberProc(HWND, UINT, WPARAM, LPARAM);	// Функция обработки сообщения диалогового окна ввода номера
BOOL	PutNumber(HWND, char *, int &, char);					// Функция ввода цифры в буфер и его отображения
void	ShowNumber(HDC, int, int, char*);						// Функция отрисовки текста в заданный контекст устройства вывода

HINSTANCE appHInstance;
char globalBuffer[12];
int globalCounter = 0;
char buffer[12];
int counter = 0;

// Точка входа в приложение. Инициализация и регистрация в системе класса окна,
// буфера для хранения номера телефона
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static char  szAppName[] = "Phone";
	MSG          msg;
	
	// Объявление переменной класса окна
	WNDCLASSEX   wndclass;
	// Дескриптор главного окна приложения
	HWND          hwnd;
	// Дескриптор экземпляра приложения
	appHInstance = hInstance;

	// Инициализация переменной класса окна
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

	// Регистрация класса окна в системе
	RegisterClassEx(&wndclass);

	// Создание экземпляра главного окна приложения
	hwnd = CreateWindow(szAppName, "Phone",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		250, 100,
		NULL, NULL, hInstance, NULL);

	// Отображение главного окна
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Возврат кода завершения приложения
	return msg.wParam;
}

// Функция обработки сообщений главного окна приложения
LRESULT CALLBACK  WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDc = GetDC(hwnd);

	switch (iMsg)
	{
	// Инициализация главного окна, буфера для хранения и отображения номера телефона
	case WM_CREATE:
		buffer[0] = '\0';
		globalBuffer[0] = '\0';
		return 0;

	// Обработка события изменения данных, инвалидация клиентской области окна
	case WM_UPDATE:
		RECT invalidationRect;
		GetClientRect(hwnd, &invalidationRect);
		InvalidateRect(hwnd, &invalidationRect, TRUE);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		// Обработка события выбора пункта меню 'Input number', создание диалогового окна ввода номера
		case IDM_INPUT:
			DialogBox(appHInstance, "InputNumber", hwnd, InputNumberProc);
			return 0;
		// Обработка события выбора пункта меню 'Exit', отправка сообщения выхода из приложения
		case IDM_EXIT:
			PostQuitMessage(0);
			return 0;
		}
		break;

	// Обработка события для перерисовки инвалидированной клиентской области, перерисовка номера телефона
	case WM_PAINT:
		Rectangle(hDc, 40, 5, 195, 35);
		ShowNumber(hDc, 75, 12, globalBuffer);
		break;
	// Обработка события выхода из приложения
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	// Вызов обработчика сообщения по умолчанию, если сообщение не было обработано
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

// Функция обработки сообщений диалогового окна ввода номера телефона
BOOL CALLBACK InputNumberProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	// Инициализация диалогового окна, буфера для ввода номера телефона
	case WM_INITDIALOG:
		strcpy_s(buffer, globalBuffer);
		counter = globalCounter;
		return SetDlgItemText(hDlg, ID_NUMBER, buffer);

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		// Обработка событий нажатия цифровых кнопок
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
		
		// Обработка события нажатия кнопки очистки поля ввода
		case IDCLEAR:
			buffer[0] = '\0';
			counter = 0;
			return SetDlgItemText(hDlg, ID_NUMBER, buffer);
		
		// Обработка сообщения нажатия кнопки 'OK'
		case IDOK:
			strcpy_s(globalBuffer, buffer);
			globalCounter = counter;
			SendMessage(GetWindow(hDlg, GW_OWNER), WM_UPDATE, NULL, NULL);
			return EndDialog(hDlg, TRUE);

		// Обработка сообщения нажатия кнопки 'Cancel'
		case IDCANCEL:
			return EndDialog(hDlg, FALSE);
		}
		break;
	}
	return FALSE;
}

// Функция добавляет новую цифру в буфер, хранящий номер телефона и немедленно отображает его
BOOL PutNumber(HWND hDlg, char *buffer, int &counter, char digit)
{
	if (counter >= 11)
		return false;
	buffer[counter++] = digit;
	buffer[counter] = '\0';
	return SetDlgItemText(hDlg, ID_NUMBER, buffer);
}

// Функция выводит текст в заданный контекст устройства вывода
void ShowNumber(HDC hDc, int x, int y, char* buffer)
{
	TextOut(hDc, x, y, buffer, strlen(buffer));
}