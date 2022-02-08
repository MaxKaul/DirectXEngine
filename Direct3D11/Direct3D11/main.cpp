#include <Windows.h>
#include "Run.h"

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	Run runApp = {};

	runApp.Init(_hInstance, _hPrevInstance, _lpCmdLine, _nCmdShow);

	return 0;
}