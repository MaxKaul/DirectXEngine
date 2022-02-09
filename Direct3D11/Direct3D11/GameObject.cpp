#include "GameObject.h"

bool GameObject::Init(const std::string& _filePath, ID3D11Device* _p_device, ID3D11DeviceContext* _p_deviceContext)
{
	p_device = _p_device;
	p_deviceContext = _p_deviceContext;

	//Initialize World Transformation-Matrix
	XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity());

	LoadModel(_filePath);
	return false;
}

bool GameObject::LoadModel(const std::string& _filePath)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(_filePath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	if (pScene == nullptr)
		return false;

	this->ProcessNode(pScene->mRootNode, pScene);

	return true;
}

void GameObject::ProcessNode(aiNode* _node, const aiScene* _scene)
{
	for (UINT i = 0; i < _node->mNumMeshes; i++)
	{
		aiMesh* mesh = _scene->mMeshes[_node->mMeshes[i]];
		meshes.push_back(this->ProcessMesh(mesh, _scene));
	}

	for (UINT i = 0; i < _node->mNumChildren; i++)
	{
		this->ProcessNode(_node->mChildren[i], _scene);
	}
}

Mesh GameObject::ProcessMesh(aiMesh* _mesh, const aiScene* _scene)
{
	std::vector<Vertex> vertices;
	std::vector<UINT> indices;

	vertices.reserve(_mesh->mNumVertices);
	indices.reserve(_mesh->mNumFaces * 3);

	for (UINT i = 0; i < _mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.position.x = _mesh->mVertices[i].x;
		vertex.position.y = _mesh->mVertices[i].y;
		vertex.position.z = _mesh->mVertices[i].z;

		if (_mesh->HasNormals())
		{
			vertex.normal = { *reinterpret_cast<XMFLOAT3*>(&_mesh->mNormals[i]) };
		}

		if (_mesh->mTextureCoords[0])
		{
			vertex.uv.x = (float)_mesh->mTextureCoords[0][i].x;
			vertex.uv.y = (float)_mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	for (UINT i = 0; i < _mesh->mNumFaces; i++)
	{
		aiFace face = _mesh->mFaces[i];


		for (UINT j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return Mesh(this->p_device, p_deviceContext, vertices, indices);
}

INT GameObject::Draw()
{
	//Set Mesh Data

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw();
	}

	return 0;
}

INT GameObject::Move(FLOAT _dt)
{
	//rotY += XM_PI / 3.0f * _dt;

	FLOAT move = 5.0f * _dt;;

	if (!(GetAsyncKeyState(VK_MBUTTON) & 0x8000))
	{
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
			posX += move;

		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
			posX -= move;

		if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
			posY -= move;

		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
			posY += move;

		if ((GetAsyncKeyState(VK_SUBTRACT) & 0x8000) || (GetAsyncKeyState('Q') & 0x8000))
			posZ += move;

		if ((GetAsyncKeyState(VK_ADD) & 0x8000) || (GetAsyncKeyState('E') & 0x8000))
			posZ -= move;

		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))
			rotX -= move;

		if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000))
			rotY -= move;

		if ((GetAsyncKeyState(VK_BACK) & 0x8000))
			rotZ -= move;

		//if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
		//{
		//	posX = startPos.x;
		//	posY = startPos.y;
		//	posZ = startPos.z;

		//	rotX = 0;
		//	rotY = 0;
		//	rotZ = 0;
		//}

		XMMATRIX translation = XMMatrixTranslation(posX, posY, posZ);
		XMMATRIX rotation = XMMatrixRotationRollPitchYaw(rotX, rotY, rotZ);
		XMMATRIX localScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);


		XMStoreFloat4x4(&worldMatrix, localScale * rotation * translation);

		return 0;
	}
}


