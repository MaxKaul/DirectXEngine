#pragma once
#include <Windows.h>
#include "Utils.h"

class Component 
{
public:

	//Component(GameObject _go)
	//{
	//	gameObject = _go;
	//}

	virtual INT Awake() = 0;
	virtual INT Start() = 0;
	virtual INT Update() = 0;
	virtual INT DeInit() = 0;


//protected:
//	GameObject gameObject;
};
