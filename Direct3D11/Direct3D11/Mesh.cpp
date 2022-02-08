#include "Mesh.h"
#include "Utils.h"
#include <xutility>
#include <iostream>
#include <string>


INT Mesh::Init()
{

	return 0;
}


Mesh::Mesh(ID3D11Device* _p_device, ID3D11DeviceContext* _p_deviceContext, std::vector<Vertex>& _vertices, std::vector<UINT>& _indeces)
{
	p_deviceContext = _p_deviceContext;
	p_device = _p_device;

	HRESULT hr = vertexBuffer.Init(p_device, _vertices.data(), _vertices.size());
	CheckFailed(hr);

	hr = indexBuffer.Init(p_device, _indeces.data(), _indeces.size());
	CheckFailed(hr);
}

Mesh::Mesh(const Mesh & _mesh)
{
	vertexBuffer = _mesh.vertexBuffer;
	indexBuffer = _mesh.indexBuffer;
	p_deviceContext = _mesh.p_deviceContext;;
	p_device = _mesh.p_device;;
}

void Mesh::Draw()
{
	static UINT offset = 0;
	p_deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
	p_deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);

	p_deviceContext->DrawIndexed(indexBuffer.BufferSize(), 0, 0);
}

INT Mesh::Update(FLOAT _dt)
{

	return 0;
}


INT Mesh::DeInit()
{
	//SafeRelease<ID3D11Buffer>(vertexBuffer.GetAddress());
	//SafeRelease<ID3D11Buffer>(indicesBuffer.GetAddressOf());
	
	return 0;
}


//INT Mesh::InitVertexBuffer(ID3D11Device* _p_d3dDevice)
//{
	//Vertex vertecies[] = {		
	//	//        X      Y     Z	   U      V      nX     nY     nZ    

	//	// Left
	//	Vertex(  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f),
	//	Vertex(  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f),
	//	Vertex(  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f),
	//	Vertex(  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f),

	//	// Right
	//	Vertex( -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f),
	//	Vertex( -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f),
	//	Vertex( -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f),
	//	Vertex( -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f),
	//	
	//	// Bottom
	//	Vertex( -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f),
	//	Vertex(  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f),
	//	Vertex( -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f),
	//	Vertex(  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f),

	//	// Top
	//	Vertex( -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f),
	//	Vertex(  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f),
	//	Vertex( -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f),
	//	Vertex(  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f),
	//						   
	//	// Back
	//	Vertex( -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f),
	//	Vertex(  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f),
	//	Vertex( -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f),
	//	Vertex( 1.0f,  -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f),
	//						   
	//	// Front
	//	Vertex(  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f),
	//	Vertex( -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f),
	//	Vertex(  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f),
	//	Vertex( -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f),
	//};

	//HRESULT hr = vertexBuffer.Init(_p_d3dDevice, vertecies, ARRAYSIZE(vertecies));
	//CheckFailed(hr, 30);



	//return 0;
//}

//INT Mesh::InitIndexBuffer(ID3D11Device* _p_d3dDevice)
//{
	/*DWORD indices[] = {

		0,2,1,
		2,3,1,

		4,6,5,
		6,7,5,

		8,10,9,
		10,11,9,

		12,14,13,
		14,15,13,

		16,18,17,
		18,19,17,

		20,22,21,
		22,23,21
	};*/
	 
	/*HRESULT hr = indexBuffer.Init(_p_d3dDevice, indices, ARRAYSIZE(indices));
	CheckFailed(hr, 32);*/

	//return 0;
//}

