#include "Camera.h"

using namespace DirectX;

INT Camera::Init(UINT _screenWidth, UINT _screenHeight, FLOAT _degree, FLOAT _nearClipZ, FLOAT _farCLipZ)
{
	pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vectorPos = XMLoadFloat3(&pos);
	rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vectorRot = XMLoadFloat3(&rot);

	XMStoreFloat4x4(worldMatrix, XMMatrixIdentity());


	//	// View Matrix
	//	XMMATRIX viewMat = XMMatrixLookToLH(
	//	XMVectorSet(posX, posY, posZ, 0.0f),			// Pos
	//	XMVectorSet(DirX, DirY, DirZ, 0.0f),			// Forward
	//	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)				// Up Dir
	//);

	//	XMStoreFloat4x4(&viewMatrix,(XMMatrixScaling(1,1,1) * XMMatrixRotationRollPitchYaw(XMConvertToRadians(rotX), XMConvertToRadians(rotY), XMConvertToRadians(rotZ)) *
	//					XMMatrixTranslation(posX, posY, posZ)));


	////XMStoreFloat4x4(&viewMatrix, viewMat);


	// FOV in Radians
	// Aspect Ratio
	// Near and Far Clip Plane
	projectionMatrix = XMMatrixPerspectiveFovLH(XM_PI * 0.3333333f,	(FLOAT)_screenWidth / (FLOAT)_screenHeight,	_nearClipZ, _farCLipZ);

	UpdateViewMatrix();

	return 0;
}

XMMATRIX* Camera::GetViewMatrix()
{
	return &viewMatrix;
}

XMMATRIX* Camera::GetProjectionMatrix()
{
	return &projectionMatrix;
}

XMFLOAT4X4* Camera::GetWorldMatrix()
{
	return &worldMatrix;
}

XMVECTOR Camera::GetPosVector()
{
	return vectorPos;
}

XMFLOAT3 Camera::GetPosFloat3()
{
	return pos;
}

XMVECTOR Camera::GetRotVector()
{
	return vectorRot;
}

XMFLOAT3 Camera::GetRotFloat3()
{
	return rot;
}

INT Camera::Update(FLOAT _dt)
{

	FLOAT camSpeed = 5 * _dt ;


	if ((GetAsyncKeyState(VK_MBUTTON) & 0x8000))
	{
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
			AdjPosition(currLeft * camSpeed);

		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
			AdjPosition(currRight * camSpeed);

		if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
			AdjPosition(currForward * camSpeed);

		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
			AdjPosition(currBackward * camSpeed);

		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))
			AdjRotation((lastMousePosY / 100) * camSpeed * 0.1f, (lastMousePosX / 100) * camSpeed * 0.1f, 0);


		//if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000))
		//	AdjRotation(currRight * camSpeed);

		//if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
		//{
		//	posX = 0;
		//	posY = 0;
		//	posZ = 0;

		//	rotX = 0;
		//	rotY = 0;
		//	rotZ = 1;
		//}

		//);

		//XMStoreFloat4x4(&viewMatrix, viewMat * (XMMatrixScaling(1, 1, 1) * XMMatrixRotationRollPitchYaw(XMConvertToRadians(rotX), XMConvertToRadians(rotY), XMConvertToRadians(rotZ)) *
		//	XMMatrixTranslation(posX, posY, posZ)));

		//XMMATRIX translation = XMMatrixTranslation(posX, posY, posZ);
		//XMMATRIX rotation = XMMatrixRotationRollPitchYaw(rotX, rotY, rotZ);
		//XMMATRIX localScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);

		//XMMATRIX rotationMatrixX = XMMatrixRotationX(XMConvertToRadians(rotY * _dt));
		//XMMATRIX rotationMatrixZ = XMMatrixRotationZ(XMConvertToRadians(rotZ * _dt));

		//XMStoreFloat4x4(&viewMatrix, XMLoadFloat4x4(&viewMatrix) * (rotationMatrixX));

		//XMStoreFloat4x4(&viewMatrix, viewMat * (localScale * rotation * translation));

		return 0;
	}

	return 0;
}

void Camera::SetPosition(const XMVECTOR& _pos)
{
	XMStoreFloat3(&pos, _pos);
	vectorPos = _pos;
	UpdateViewMatrix();
}

void Camera::SetPosition(FLOAT _x, FLOAT _y, FLOAT _z)
{
	pos = XMFLOAT3(_x, _y, _z);
	vectorPos = XMLoadFloat3(&pos);
	UpdateViewMatrix();
}

void Camera::AdjPosition(const XMVECTOR& _pos)
{
	vectorPos += _pos;
	XMStoreFloat3(&pos, vectorPos);
	UpdateViewMatrix();
}

void Camera::AdjPosition(FLOAT _x, FLOAT _y, FLOAT _z)
{
	pos.x += _x;
	pos.y += _y;
	pos.z += _z;
	vectorPos = XMLoadFloat3(&pos);
	UpdateViewMatrix();
}

void Camera::SetRotation(const XMVECTOR& _rot)
{
	vectorRot += _rot;
	XMStoreFloat3(&rot, _rot);
	UpdateViewMatrix();
}

void Camera::SetRotation(FLOAT _x, FLOAT _y, FLOAT _z)
{
	rot = XMFLOAT3(_x, _y, _z);
	vectorRot = XMLoadFloat3(&rot);
	UpdateViewMatrix();
}

void Camera::AdjRotation(const XMVECTOR& _rot)
{
	vectorRot += _rot;
	XMStoreFloat3(&rot, vectorRot);
	UpdateViewMatrix();
}

void Camera::AdjRotation(FLOAT _x, FLOAT _y, FLOAT _z)
{
	rot.x += _x;
	rot.y += _y;
	rot.z += _z;
	vectorRot = XMLoadFloat3(&rot);
	UpdateViewMatrix();
}

void Camera::SetLookPos(XMFLOAT3 _lookPos)
{
	if (_lookPos.x == pos.x && _lookPos.y == pos.y && _lookPos.z == pos.z)
		return;

	_lookPos.x = pos.x - _lookPos.x;
	_lookPos.y = pos.y - _lookPos.y;
	_lookPos.z = pos.z - _lookPos.z;

	FLOAT pitch = 0.0f;

	if (_lookPos.y != 0.0f)
	{
		const float distance = sqrt((_lookPos.x * _lookPos.y) + (_lookPos.z *_lookPos.z));
		pitch = atan(_lookPos.y / distance);
	}

	FLOAT yaw = 0.0f;

	if (_lookPos.x != 0.0f)
		yaw = atan(_lookPos.x / _lookPos.z);

	if (_lookPos.z > 0)
		yaw += XM_PI;

	SetRotation(pitch, yaw, 0.0f);
}

INT Camera::SetMouseMousePos(XMFLOAT2 _pos)
{
	currMousePosX = _pos.x;
	currMousePosY = _pos.y;


	return 0;

	//lastMousePosX = currMousePosX;
	//lastMousePosY = currMousePosY;
}

void Camera::UpdateViewMatrix()
{
	// look targed gets determined by multipling the forward vec with the cam rot
	XMMATRIX camRotMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	XMVECTOR camDirTarged = XMVector3TransformCoord(defaultForward, camRotMatrix);

	camDirTarged += vectorPos;

	XMVECTOR upDir = XMVector3TransformCoord(defaultUp, camRotMatrix);

	viewMatrix = XMMatrixLookAtLH(vectorPos, camDirTarged, upDir);

	XMMATRIX vectorRotMat = XMMatrixRotationRollPitchYaw(0.0f, rot.y, 0.0f);
	currForward = XMVector3TransformCoord(defaultForward, vectorRotMat);
	currBackward = XMVector3TransformCoord(defaultBackward, vectorRotMat);
	currRight = XMVector3TransformCoord(defaultRight, vectorRotMat);
	currLeft = XMVector3TransformCoord(defaultLeft, vectorRotMat);

	lastMousePosX = currMousePosX - lastMousePosX;
	lastMousePosY = currMousePosY - lastMousePosY;
}
