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


class GameObject
{
public: 
	//bool Init(const std::string& _filePath, ID3D11Device* _p_device,ID3D11DeviceContext* _p_deviceContext);
	GameObject(const std::string& _filePath, ID3D11Device* _p_device,ID3D11DeviceContext* _p_deviceContext);
	INT Draw();

	//XMFLOAT4X4* GetWorldMatrix() { return &worldMatrix; }

	INT Move(FLOAT _dt);

private:

	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;
	ID3D11DeviceContext* p_deviceContext;
	ID3D11Device* p_device;

	vector<Mesh> meshes;

	//XMFLOAT4X4 worldMatrix = {};

	bool LoadModel(const std::string& _filePath);

	void ProcessNode(aiNode* _node, const aiScene* _scene);
	Mesh ProcessMesh(aiMesh* _mesh, const aiScene* _scene);


	FLOAT posX = 0.0f;
	FLOAT posY = -15.0f;
	FLOAT posZ = 50.0f;

	FLOAT rotX = 0.0f;
	FLOAT rotY = 0.0f;
	FLOAT rotZ = 0.0f;

};

