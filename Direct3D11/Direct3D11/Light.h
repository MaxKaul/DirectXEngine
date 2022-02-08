#pragma once
#include <d3d11.h>
#include "Utils.h"
#include <DirectXMath.h>

using namespace DirectX;

class Light
{
public:
	struct  LightData
	{
		XMFLOAT3 LightDirection;
		FLOAT LightIntensity;
		XMFLOAT4 LightDiffuseColor;
	};


	INT Init(ID3D11Device* _p_d3dDevice, LightData& _light, INT _id = 0);
	INT Render(ID3D11DeviceContext* _p_d3dDeviceContext);
	void DeInit();

private:
	INT id = 0;
	LightData light = {};
	ID3D11Buffer* p_lightBuffer = nullptr;
};

