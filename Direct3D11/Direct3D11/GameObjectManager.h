#pragma once
#include <Windows.h>
#include <vector>
#include "GameObject.h"

enum class EGameObjectType
{
	eCamera,
	eRobot,
	eNanosuit
};

enum class EComponentType
{
	eMesh,
	eTransform
};

class GameObjectManager
{
public:
	INT Init(ID3D11Device* _p_device, ID3D11DeviceContext* _p_deviceContext, XMMATRIX* _p_wMatrix, XMMATRIX* _p_vMatrix, XMMATRIX* _p_pMatrix, UINT _spawnAmount);
	INT SpawnObject(EGameObjectType _type);
	INT DespawnObject();

	INT DrawSpawnedObjects();

	INT AmountOfSpawned() { return allGameObjects.size(); }

private:
	vector<GameObject> allGameObjects;

	INT SubscribeObject();
	INT UnsubscribeObject();

	INT DebugSpawnInterface();


	ID3D11Device* p_device;
	ID3D11DeviceContext* p_deviceContext;

	XMMATRIX* debufWorldMatrix;
	XMMATRIX* debufViewMatrix;
	XMMATRIX* debufProjectionMatrix;

	//INT(GameObject::* p_drawObj)();

	//INT error = gameObject.Init("Assets\\obj - fbx\\nanosuit.obj", p_d3dDevice, p_d3dContext);
	//CheckError(error);
	//p_drawObj = &GameObject::Draw;
	//INT drawObj = (gameObject.*p_drawObj)();
};

