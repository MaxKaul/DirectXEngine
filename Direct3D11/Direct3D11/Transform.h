#pragma once
#include "Window.h"

class Transform 
{
public:
	FLOAT* Position_X = &posX;
	FLOAT* Position_Y = &posY;
	FLOAT* Position_Z = &posZ;

	FLOAT* Rotation_X = &rotX;
	FLOAT* Rotation_Y = &rotY;
	FLOAT* Rotation_Z = &rotZ;

	FLOAT* Scale_X = &scaleX;
	FLOAT* Scale_Y = &scaleY;
	FLOAT* Scale_Z = &scaleZ;

	void SetNewPosX(FLOAT _value) { posX = _value; }
	void SetNewPosY(FLOAT _value) { posY = _value; }
	void SetNewPosZ(FLOAT _value) { posZ = _value; }

	void SetNewRotX(FLOAT _value) { rotX = _value; }
	void SetNewRotY(FLOAT _value) { rotY = _value; }
	void SetNewRotZ(FLOAT _value) { rotZ = _value; }

	void SetNewScaleX(FLOAT _value) { scaleX = _value; }
	void SetNewScaleY(FLOAT _value) { scaleY = _value; }
	void SetNewScaleZ(FLOAT _value) { scaleZ = _value; }

private:
	FLOAT posX = 0;
	FLOAT posY = 0;
	FLOAT posZ = 0;
			   
	FLOAT rotX = 0;
	FLOAT rotY = 0;
	FLOAT rotZ = 0;

	FLOAT scaleX = 0;
	FLOAT scaleY = 0;
	FLOAT scaleZ = 0;
};
