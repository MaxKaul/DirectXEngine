#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "winuser.h"
#include "Mesh.h"

using namespace DirectX;

class Camera
{
public:
	INT Init(UINT _screenWidth, UINT _screenHeight, FLOAT _degree, FLOAT _nearClipZ, FLOAT _farCLipZ);
	INT Update(FLOAT _dt);

	XMMATRIX* GetViewMatrix();
	XMMATRIX* GetProjectionMatrix();

	XMVECTOR GetPosVector();
	XMFLOAT3 GetPosFloat3();

	XMVECTOR GetRotVector();
	XMFLOAT3 GetRotFloat3();

	void SetPosition(const XMVECTOR& _pos);
	void SetPosition(FLOAT _x, FLOAT _y, FLOAT _z);

	void AdjPosition(const XMVECTOR& _pos);
	void AdjPosition(FLOAT _x, FLOAT _y, FLOAT _z);

	void SetRotation(const XMVECTOR& _rot);
	void SetRotation(FLOAT _x, FLOAT _y, FLOAT _z);

	void AdjRotation(const XMVECTOR& _rot);
	void AdjRotation(FLOAT _x, FLOAT _y, FLOAT _z);

	void SetLookPos(XMFLOAT3 _lookPos);

	INT SetMouseMousePos(XMFLOAT2 _pos);

private:
	void UpdateViewMatrix();

	FLOAT currMousePosX;
	FLOAT currMousePosY;

	FLOAT lastMousePosX;
	FLOAT lastMousePosY;

	XMVECTOR vectorPos;
	XMVECTOR vectorRot;

	XMFLOAT3 pos;
	XMFLOAT3 rot;
	
	XMMATRIX viewMatrix = {};
	XMMATRIX projectionMatrix = {};

	XMVECTOR defaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR defaultBackward = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);

	XMVECTOR defaultUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMVECTOR defaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR defaultLeft = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR currForward;
	XMVECTOR currBackward;
	XMVECTOR currRight;
	XMVECTOR currLeft;
};

