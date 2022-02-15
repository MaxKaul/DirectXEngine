#pragma once
#include <memory>
#include "Utils.h"
#include "D3D.h"
#include <DirectXMath.h>
#include <iostream>
#include <wrl/client.h>

using namespace std;

template<class T>
class VertexBuffer
{
private:

	// stores the buffer
	ID3D11Buffer* buffer = nullptr;
	// stores stride
	std::shared_ptr<UINT> stride;
	// stores the buffer size (total number of vertices)
	UINT bufferSize = 0;

public:
	VertexBuffer(){}


	VertexBuffer(const VertexBuffer<T>& rhs) 
	{
		buffer = rhs.buffer;
		bufferSize = rhs.bufferSize;
		stride = rhs.stride;
	}

	//VertexBuffer<T>& T::operator=(const VertexBuffer<T>& rhs)
	//{
	//	buffer = rhs.buffer;
	//	bufferSize = rhs.bufferSize;
	//	stride = rhs.bufferSize;

	//	return *this;
	//}



	HRESULT Init(ID3D11Device* _device, T* _data, UINT verticesNumber)
	{
		bufferSize = verticesNumber;
		stride = std::make_shared<UINT>(sizeof(T));

		D3D11_BUFFER_DESC vertDesc;
		//ZeroMemory(&vertDesc, sizeof(vertDesc));

		vertDesc.Usage = D3D11_USAGE_DEFAULT; // who has wich access
		vertDesc.ByteWidth = sizeof(T) * verticesNumber;
		vertDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // buffer type
		vertDesc.CPUAccessFlags = 0;
		vertDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initialData;
		//ZeroMemory(&initialData, sizeof(initialData));
		initialData.pSysMem = _data;

		HRESULT hr = _device->CreateBuffer(&vertDesc, &initialData, &buffer);
		return hr;
	}

	// returns a pointer to the buffer
	ID3D11Buffer* GetBuffer()const
	{
		return this->buffer;
	}

	// returns the address 
	ID3D11Buffer* const* GetAddressOf()const
	{
		return &this->buffer;
	}

	// returns the buffer size 
	UINT BufferSize()const
	{
		return this->bufferSize;
	}

	// returns the stride
	const UINT Stride()const
	{
		return *this->stride.get();
	}

	// returns a pointer to the buffer 
	const UINT * StridePtr()const
	{
		return this->stride.get();
	}
};
