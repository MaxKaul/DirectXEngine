#pragma once
#include "Component.h"
#include <d3d11.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include <DirectXMath.h>
#include <vector>
#include <iostream>
#include "Vertex.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace DirectX;

class Mesh
{
public:
	INT Init();
	INT Update(FLOAT _dt);
	INT DeInit();

	void Draw();

	Mesh();
	Mesh(const Mesh & _mesh);
	Mesh(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext, std::vector<Vertex> & _vertices, std::vector<UINT> & _indeces);


private:

	IndexBuffer indexBuffer;
	ID3D11Device* p_device = nullptr;
	VertexBuffer<Vertex> vertexBuffer;
	ID3D11DeviceContext* p_deviceContext = nullptr;
};

