#pragma once
#include <memory>
#include "Utils.h"
#include <Windows.h>

class Window
{
public:
	INT Init(HINSTANCE _hInstance, UINT _width, UINT _height);
	BOOL Update();
	void DeInit();

	HWND GetWindowHandle() { return p_hWnd; }

private:
	HWND p_hWnd = nullptr;
};

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

