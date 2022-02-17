#pragma once
#include <Windows.h>
#include <vector>
#include "GameObject.h"

class GameObjectManager
{
public:
	void Init();

private:
	std::vector<GameObject> allGameObjects;

	INT SubGO();
	INT UnsubGO();

};

