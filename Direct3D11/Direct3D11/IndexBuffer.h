#pragma once
#include <wrl/client.h>
#include "D3D.h"


class IndexBuffer
{
private:
	//IndexBuffer(const IndexBuffer& rhs);

	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	UINT bufferSize;

public:
	IndexBuffer() {}

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

	// returns the buffer size 
	UINT BufferSize()const
	{
		return this->bufferSize;
	}

	HRESULT Init(ID3D11Device* _device, UINT* _data, UINT indicesAmount)
	{
		bufferSize = indicesAmount;

		D3D11_BUFFER_DESC indicesDesc = {};
		indicesDesc.Usage = D3D11_USAGE_IMMUTABLE; // who has wich access
		indicesDesc.ByteWidth = sizeof(UINT) * indicesAmount;
		indicesDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; // buffer type
		indicesDesc.CPUAccessFlags = 0;
		indicesDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initialData = {};
		initialData.pSysMem = _data;

		HRESULT hr = _device->CreateBuffer(&indicesDesc, &initialData, buffer.GetAddressOf());

		return hr;
	}
};

