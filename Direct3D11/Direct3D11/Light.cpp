#include "Light.h"

INT Light::Init(ID3D11Device* _p_d3dDevice, LightData& _light, INT _id)
{
	light = _light;
	id = _id;

	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(LightData);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = &light;

	HRESULT hr = _p_d3dDevice->CreateBuffer(&desc, &data, &p_lightBuffer);
	CheckFailed(hr, 70);

	return 0;
}

INT Light::Render(ID3D11DeviceContext* _p_d3dDeviceContext)
{
	_p_d3dDeviceContext->PSSetConstantBuffers(id, 1, &p_lightBuffer);

	return 0;
}

void Light::DeInit()
{
	SafeRelease<ID3D11Buffer>(p_lightBuffer);
}
