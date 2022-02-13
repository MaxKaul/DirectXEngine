#pragma once
#include "Mesh.h"
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
#include "Time.h"
#include "Material.h"
#include "Utils.h"

class GameObject
{
public: 
	INT Move();
	INT Draw();
	INT Init(std::string _meshFilePath, std::string _textureFilePath, ID3D11Device* _p_device, ID3D11DeviceContext* _p_deviceContext, XMMATRIX* _p_wMatrix, XMMATRIX* _p_vMatrix, XMMATRIX* _p_pMatrix);


	GameObject() {};
	GameObject(const GameObject& rhs) 
	{
		memcpy(this, &rhs, sizeof(GameObject));
	}
	GameObject(std::string _meshFilePath, std::string _textureFilePath, ID3D11Device* _p_device, ID3D11DeviceContext* _p_deviceContext, XMMATRIX* _p_wMatrix, XMMATRIX* _p_vMatrix, XMMATRIX* _p_pMatrix);
private:
	INT(Material::* p_materialRender)(ID3D11DeviceContext*, XMMATRIX*, XMMATRIX*, XMMATRIX*);	

	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;
	ID3D11DeviceContext* p_deviceContext;
	ID3D11Device* p_device;

	vector<Mesh> meshes;

	XMFLOAT4X4 positionMatrix;

	bool LoadModel( std::string& _filePath);

	void ProcessNode(aiNode* _node, const aiScene* _scene);
	Mesh ProcessMesh(aiMesh* _mesh, const aiScene* _scene);

	FLOAT posX = 0.0f;
	FLOAT posY = -15.0f;
	FLOAT posZ = 50.0f;

	FLOAT rotX = 0.0f;
	FLOAT rotY = 0.0f;
	FLOAT rotZ = 0.0f;

	Material material;

	XMMATRIX* Debug_Matrix_World;
	XMMATRIX* Debug_Matrix_View;
	XMMATRIX* Debug_Matrix_Projection;
};

