#include "Window.h"

INT Window::Init(HINSTANCE _hInstance, UINT _width, UINT _height)
{
	// -->Register Window Class<--
	WNDCLASS wc = {};									// Create Window Class
	wc.hInstance = _hInstance;							// Creates a window class object
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));	// handle to application instance
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);		// handle to background brush (colour)
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);		// handle to application cursor
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// handle to application icon
	wc.lpszClassName = TEXT("Window");					// additional window behaviour
	wc.lpfnWndProc = WndProc;							// window class name


	//Register Window
	if (!RegisterClass(&wc)) { return 10; }

	//Window Adjustment
	UINT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	UINT screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT wr = { (screenWidth - _width) / 2, (screenHeight - _height) / 2, (screenWidth + _width) / 2, (screenHeight + _height) / 2 };
	DWORD style = WS_OVERLAPPEDWINDOW;

	AdjustWindowRect(&wr, style, false);

	// -->Create Window<--
	p_hWnd = CreateWindow
	(
		wc.lpszClassName,	// ClassName
		L"Graphics Engine", // WindowName
		style,				// Style
		wr.left,			// PosX
		wr.top,				// PosY
		wr.right - wr.left, // Width
		wr.bottom - wr.top, // Height
		nullptr,			// Parent Window
		nullptr,			// Menu Instance
		_hInstance,
		nullptr				// Optional Param
	); 

	CheckNull(p_hWnd, 11);

	// -->Shows the Window<--
	ShowWindow(p_hWnd, SW_SHOW);
	SetFocus(p_hWnd);

	return 0;
}

BOOL Window::Update()
{
	// -->Message Pump<--

	static MSG msg = {};

	if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.message != WM_QUIT;
}

void Window::DeInit()
{
}

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
		break;

		/*case WM_KEYDOWN:
			if (_wparam == VK_ESCAPE) DestroyWindow(_hwnd);
			break;*/

	default:
		return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
	}

	return 0;
}
