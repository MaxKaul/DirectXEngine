#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "ConstantBufferTypes.h"
#include <wrl/client.h>

using namespace DirectX;

template<class T>
class ConstantBuffer
{
	struct MatrixBuffer
	{
		XMFLOAT4X4 worldviewProjectionMatrix;
		XMFLOAT4X4 worldMatrix;
	};

private:
	ConstantBuffer(const ConstantBuffer<T>& rhs);

	// stores the buffer
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	ID3D11DeviceContext* deviceContext = nullptr;

public:
	ConstantBuffer() {}

	T Data;

	HRESULT Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext)
	{
		deviceContext = _deviceContext;

		D3D11_BUFFER_DESC constDesc;

		constDesc.Usage = D3D11_USAGE_DYNAMIC; // who has wich access
		constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // buffer type
		constDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constDesc.MiscFlags = 0;
		constDesc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
		constDesc.StructureByteStride = 0;

		HRESULT hr = _device->CreateBuffer(&constDesc, 0, buffer.GetAddressOf());
		return hr;
	}

	bool ApplyChanges(XMFLOAT4X4* _p_worldMatrix, XMMATRIX _p_viewMatrix, XMMATRIX _p_projectionMatrix)
	{
		XMMATRIX worldMatrix = XMLoadFloat4x4(_p_worldMatrix);

		XMMATRIX wvpMatrix = XMMatrixTranspose(worldMatrix * _p_viewMatrix * _p_projectionMatrix); //transpose for column mayor - row mayor problem

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		HRESULT hr = deviceContext->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(hr)) return false;

		//CopyMemory(mappedResource.pData, &Data, sizeof(T));

		MatrixBuffer* p_TempMatrixBuffer = static_cast<MatrixBuffer*>(mappedResource.pData);
		XMStoreFloat4x4(&(p_TempMatrixBuffer->worldviewProjectionMatrix), wvpMatrix);
		XMStoreFloat4x4(&(p_TempMatrixBuffer->worldMatrix), XMMatrixTranspose(worldMatrix));
		deviceContext->Unmap(buffer.Get(), 0);

		return true;
	}

	// returns a pointer to the buffer
	ID3D11Buffer* Get()const
	{
		return this->buffer.Get();
	}

	// returns the address 
	ID3D11Buffer* const* GetAddressOf()const
	{
		return this->buffer.GetAddressOf();
	}
};

