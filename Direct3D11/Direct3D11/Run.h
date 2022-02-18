#pragma once
#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Utils.h"
#include "Camera.h"
#include "Time.h"
#include "Material.h"
#include "Light.h"
#include "HUD.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ImguiManager.h"

class Run
{
public:
	INT Init(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow);

	HUD* GetHud() { return &hud; }

private:
	INT RunApplication();


	int nCmdShow;
	LPSTR lpCmdLine;
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;

	UINT spawnAmount = 2;

	UINT width;
	UINT height;
	BOOL isFullScreen;


	D3D d3d = {};
	ID3D11Device* p_device;
	ID3D11DeviceContext* p_deviceContext;

	POINT mousePoint;

	HUD hud = {};
	Time time = {};
	Light light = {};
	Window window = {};
	Camera camera = {};
	Material material = {};
	//GameObject gameObject{};
	GameObjectManager goManager{};
	ImguiManager imguiManager{};
	Light::LightData lightData = {};

	XMMATRIX* p_viewMatrix = camera.GetViewMatrix();
	XMFLOAT4X4* p_worldMatrix = camera.GetWorldMatrix();
	XMMATRIX* p_projectionMatrix = camera.GetProjectionMatrix();


	UINT(Time::* p_fps)();

	INT(D3D::* p_d3dEndScene)();

	FLOAT(Time::* p_deltaTime)();

	FLOAT(Time::* p_timeUpdate)();

	INT(GameObject::* p_drawObj)();

	BOOL(Window::* p_windowUpdate)();

	INT(ImguiManager::* p_updateGui)();

	INT(GameObject::* p_moveObj)(FLOAT);

	INT(Camera::* p_cameraUpdate)(FLOAT);

	INT(ImguiManager::* p_endUpdateGui)();

	INT(Camera::* p_setMousePos)(XMFLOAT2);

	XMFLOAT2(ImguiManager::* p_getMousePos)();

	INT(D3D::* p_d3dBeginScene)(FLOAT, FLOAT, FLOAT);

	INT(Light::* p_lightRender)(ID3D11DeviceContext*);

	INT(HUD::* p_hud)(UINT, Camera*, INT, BOOL, BOOL, BOOL);

	INT(Material::* p_materialRender)(ID3D11DeviceContext*, XMFLOAT4X4*, XMMATRIX*, XMMATRIX*);
};

