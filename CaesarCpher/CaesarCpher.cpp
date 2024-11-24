#include <iostream>
#include <cstdlib>
#include "logics.h"
#include "Windows.h"

#define OnButtonClick 1

LRESULT CALLBACK aplProcedure(HWND hWnd, UINT message, WPARAM wp, LPARAM lp);
WNDCLASS newWindow(HBRUSH backgroundColor, HCURSOR cursor, HINSTANCE hinst, HICON icon, LPCWSTR name, WNDPROC procdure);
void MainWndAddWidget(HWND hwnd);

HWND hEdit;

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrevinst, LPSTR args, int ncmdshow) {
	WNDCLASS aplication = newWindow((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW),
		hinst, LoadIcon(NULL, IDI_QUESTION), L"Cpher", aplProcedure);

	if (!RegisterClassW(&aplication)) {
		return -1;
	}

	MSG aplMessage = { 0 };

	CreateWindow(L"Cpher", L"Caesar",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 150, NULL, NULL, NULL, NULL);

	while (GetMessage(&aplMessage, NULL, NULL, NULL)) {
		TranslateMessage(&aplMessage);
		DispatchMessage(&aplMessage);
	}
}

WNDCLASS newWindow(HBRUSH backgroundColor, HCURSOR cursor, HINSTANCE hinst, HICON icon, LPCWSTR name, WNDPROC procdure) {
	WNDCLASS NewWindowClass = { 0 };

	NewWindowClass.hIcon = icon;
	NewWindowClass.hCursor = cursor;
	NewWindowClass.hInstance = hinst;
	NewWindowClass.lpszClassName = name;
	NewWindowClass.hbrBackground = backgroundColor;
	NewWindowClass.lpfnWndProc = procdure;

	return NewWindowClass;
}

LRESULT CALLBACK aplProcedure(HWND hWnd, UINT message, WPARAM wp, LPARAM lp) {
	switch (message)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case OnButtonClick: {
			char buffer[256];
			GetWindowTextA(hEdit, buffer, sizeof(buffer));
			std::string text(buffer);
			srand(std::time(0));
			std::string result = encryption(text, "right", (rand() % 26));
			MessageBoxA(hWnd, result.c_str(), "Success", MB_OK);
			break;
		}
		default:
			break;
		}
		break;
	case WM_CREATE:
		MainWndAddWidget(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	default:
		return DefWindowProc(hWnd, message, wp, lp);
	}
}

void MainWndAddWidget(HWND hwnd) {
	RECT rect;
	GetClientRect(hwnd, &rect);

	int centerX = (rect.right - rect.left) / 2;
	int elementWidth = 200;
	int elementHeight = 20;

	CreateWindowA(
		"static",
		"Enter your text for encryption",
		WS_VISIBLE | WS_CHILD | SS_CENTER,
		centerX - elementWidth / 2,
		20,
		elementWidth, elementHeight,
		hwnd, NULL, NULL, NULL
	);

	hEdit = CreateWindowA(
		"edit",
		"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER,
		centerX - elementWidth / 2,
		50,
		elementWidth, elementHeight,
		hwnd, NULL, NULL, NULL
	);

	CreateWindowA(
		"button",
		"Encrypt",
		WS_VISIBLE | WS_CHILD,
		centerX - elementWidth / 2,
		80,
		elementWidth, elementHeight,
		hwnd, (HMENU)OnButtonClick, NULL, NULL
	);
}
