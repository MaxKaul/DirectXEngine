#pragma once
#include <Windows.h>
#include <DirectXMath.h>

using namespace DirectX;

class ImguiManager
{
public:
	ImguiManager();
	~ImguiManager();

	INT Update();
	INT EndUpdate();		

	XMFLOAT2 GetMousePos();
};

