#include "GameObjectManager.h"

INT GameObjectManager::Init(ID3D11Device* _p_device, ID3D11DeviceContext* _p_deviceContext, XMMATRIX* _p_wMatrix, XMMATRIX* _p_vMatrix, XMMATRIX* _p_pMatrix)
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
		//GameObject newObj("Assets\\obj - fbx\\Robot.fbx", "Assets\\textures\\texture.png", p_device, p_deviceContext , debufWorldMatrix, debufViewMatrix, debufProjectionMatrix);
		//allGameObjects.push_back(newObj);
	}
		break;
	case EGameObjectType::eNanosuit:
	{	 
		//GameObject newObj("Assets\\obj - fbx\\nanosuit.obj", "Assets\\textures\\texture.png", p_device, p_deviceContext, debufWorldMatrix, debufViewMatrix, debufProjectionMatrix);
		//allGameObjects.push_back(newObj);
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
		allGameObjects[i].Draw();
		allGameObjects[i].Move();
	}

	return 0;
}
