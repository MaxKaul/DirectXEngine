#include "GameObjectManager.h"

INT GameObjectManager::Init(ID3D11Device* _p_device, ID3D11DeviceContext* _p_deviceContext, XMMATRIX* _p_wMatrix, XMMATRIX* _p_vMatrix, XMMATRIX* _p_pMatrix, UINT _spawnAmount)
{
	p_device = _p_device;
	p_deviceContext = _p_deviceContext;

	debufWorldMatrix = _p_wMatrix;
	debufViewMatrix = _p_vMatrix;
	debufProjectionMatrix = _p_pMatrix;


	return 0;
}

INT GameObjectManager::SpawnObject(EGameObjectType _type)
{
	//GameObject newObj = *new GameObject;

	switch (_type)
	{
		break;
	case EGameObjectType::eRobot:
	{		
		allGameObjects.push_back(GameObject("Assets\\obj - fbx\\Robot.fbx", p_device, p_deviceContext));
	}
	break;
	case EGameObjectType::eNanosuit:
	{
		allGameObjects.push_back(GameObject("Assets\\obj - fbx\\nanosuit.obj", p_device, p_deviceContext));
	}
	break;
	default:
		break;
	}


	return 0;
}

INT GameObjectManager::DespawnObject()
{
	return 0;
}



INT GameObjectManager::SubscribeObject()
{
	return 0;
}

INT GameObjectManager::UnsubscribeObject()
{
	return 0;
}

INT GameObjectManager::DebugSpawnInterface()
{
	return 0;
}

INT GameObjectManager::DrawSpawnedObjects()
{
	int size = allGameObjects.size();

	if (size <= 0)
		return 0;

	for (size_t i = 0; i < size; i++)
	{
		//allGameObjects[i].Draw();
		//allGameObjects[i].Move();
	}

	return 0;
}
