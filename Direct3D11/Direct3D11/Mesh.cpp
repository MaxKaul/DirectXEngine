#include "Mesh.h"
#include "Utils.h"
#include <xutility>
#include <iostream>
#include <string>

Mesh::Mesh(ID3D11Device* _p_device, ID3D11DeviceContext* _p_deviceContext, std::vector<Vertex>& _vertices, std::vector<UINT>& _indeces)
{
	p_device = _p_device;

	HRESULT hr = vertexBuffer.Init(p_device, _vertices.data(), _vertices.size());
	CheckFailed(hr);

	hr = indexBuffer.Init(p_device, _indeces.data(), _indeces.size());
	CheckFailed(hr);
}

void Mesh::Draw(ID3D11DeviceContext* _p_deviceContext)
{
	static UINT offset = 0;
	_p_deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
	_p_deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);

	_p_deviceContext->DrawIndexed(indexBuffer.BufferSize(), 0, 0);
}