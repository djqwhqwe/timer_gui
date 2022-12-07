#define _CRT_SECURE_NO_WARNINGS
#define CELL_SIZE 70
#include <Windows.h>
#include <xstring>
#include <cstdlib>
#include <tchar.h>
#include <commdlg.h>
#include <commctrl.h>
#include <fstream>
#include <vector>
#include <string>
#include "resource.h"
//TBBUTTON tbb[] = {
//{STD_FILENEW, ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON,0,0,0,0},
//{STD_FILEOPEN, ID_FILE_OPEN,TBSTATE_ENABLED, TBSTYLE_BUTTON,0,0,0,0},
//{STD_FILESAVE, ID_FILE_SAVE,TBSTATE_ENABLED, TBSTYLE_BUTTON,0,0,0,0}
//};
//HINSTANCE hInst;

const int LineHeight = 16;//Высота строки текста + межстрочное расстояние

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
int WINAPI WinMain(HINSTANCE This, // Дескриптор текущего приложения
	HINSTANCE Prev, // В современных системах всегда 0
	LPSTR cmd, // Командная строка
	int mode) // Режим отображения окна
{
	HWND hWnd; // Дескриптор главного окна программы
	MSG msg; // Структура для хранения сообщения
	WNDCLASS wc; // Класс окна
	// Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; // Имя класса окна
	wc.lpfnWndProc = WndProc; // Функция окна
	wc.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Стандартный курсор
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // Нет меню
	wc.cbClsExtra = 0; // Нет дополнительных данных класса
	wc.cbWndExtra = 0; // Нет дополнительных данных окна
	// Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0; // Регистрация класса окна 
	// Создание окна
	hWnd = CreateWindow(WinName, // Имя класса окна
		_T("Window Name"), // Заголовок окна
		WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, // Стиль окна
		CW_USEDEFAULT,// x
		CW_USEDEFAULT,// y Размеры окна
		CW_USEDEFAULT,// Width
		CW_USEDEFAULT,// Height
		HWND_DESKTOP, // Дескриптор родительского окна
		NULL, // Нет меню
		This, // Дескриптор приложения
		NULL); // Дополнительной информации нет
	ShowWindow(hWnd, mode); //Показать окно
	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);// Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg); // Посылает сообщение функции WndProc()
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
	HDC hdc;
	TEXTMETRIC tm;
	TCHAR s[10], str[30];
	const wchar_t* numbers[] = {
	_T(" 3"),
	_T(" 4"),
	_T(" 5"),
	_T(" 6"),
	_T(" 7"),
	_T(" 8"),
	_T(" 9"),
	_T("10"),
	_T("11"),
	_T("12"),
	_T(" 1"),
	_T(" 2"),
	};
	static int hours = 0, minutes = 0, seconds = 0, mseconds = 0;
	static int sx, sy;
	static double angle2 = 270, angle3 = 270;
	double text_x , text_y;
	double angle = 0; int offsetX = sx / 2, offsetY = sy / 2;
	int i, lineX, lineY;
	int timer = 0;
	switch (message) {
	case WM_CREATE:
		break;
	case WM_TIMER:
			switch (wParam) {
			case 1:
				minutes += 1;
				return 0;
			case 2:
				seconds += 1;
				if (angle3 == 360)
					angle3 = 0;
				angle3 += 6;
				InvalidateRect(hWnd, NULL, TRUE);
				return 0;
		}
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		hdc = BeginPaint(hWnd, &ps);
		angle3 = 270;
		MoveToEx(hdc, offsetX, offsetY, NULL);
		lineX = 125 * cos(3.14159265358979323846 * angle3 / 180) + offsetX;
		lineY = 125 * sin(3.14159265358979323846 * angle3 / 180) + offsetY;
		LineTo(hdc, lineX, lineY);
		
		EndPaint(hWnd, &ps);
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_LBUTTONDOWN:
		if (timer == 0) {
			SetTimer(hWnd, 1, 60000, NULL);
			SetTimer(hWnd, 2, 1000, NULL);
			SetTimer(hWnd, 3, 10, NULL);
			timer = 1;
		}
		break;
	case WM_RBUTTONUP:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_KEYDOWN:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetTextMetrics(hdc, &tm);
		if (seconds == 60) {
			seconds = 0;
		}
		if (minutes == 60)
			minutes = 0;
		Ellipse(hdc, sx / 2 - 150, sy / 2 - 150, sx / 2 + 150, sy / 2 + 150);
		for (int i = 0; i <=11; i++) {
			text_x = 140 * cos(3.14159265358979323846 * angle / 180) + offsetX - 7;
			text_y = 140 * sin(3.14159265358979323846 * angle / 180) + offsetY - 7;
			TextOut(hdc, text_x, text_y, numbers[i], wcslen(numbers[i]));
			angle += 30;
		}
		MoveToEx(hdc, offsetX, offsetY, NULL);
		lineX = 125 * cos(3.14159265358979323846 * angle3 / 180) + offsetX;
		lineY = 125 * sin(3.14159265358979323846 * angle3 / 180) + offsetY;
		LineTo(hdc, lineX, lineY);
		//MoveToEx(hdc, offsetX, offsetY, NULL);
		//lineX = 125 * cos(3.14159265358979323846 * angle2 / 180) + offsetX;
		//lineY = 125 * sin(3.14159265358979323846 * angle2 / 180) + offsetY;
		//LineTo(hdc, lineX, lineY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY: 
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
