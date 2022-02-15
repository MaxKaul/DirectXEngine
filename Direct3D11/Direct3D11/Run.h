#pragma once
#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Utils.h"
#include "Camera.h"
#include "Time.h"
#include "Light.h"
#include "HUD.h"
#include "GameObjectManager.h"

class Run
{
public:
	INT Init(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow);

	HUD* GetHud() { return &hud; }

private:
	INT RunApplication();

	INT amountOfGo = 3;

	FLOAT spawnOffset = 5;

	int nCmdShow;
	LPSTR lpCmdLine;
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;

	EGameObjectType debugSpawnObj = EGameObjectType::eNanosuit;

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

	GameObject gameObject{};

	Light::LightData lightData = {};
	GameObjectManager goManager = {};

	HWND windowHandle = window.GetWindowHandle();

	XMMATRIX* p_viewMatrix = camera.GetViewMatrix();
	XMMATRIX* p_worldMatrix = camera.GetWorldMatrix();
	XMMATRIX* p_projectionMatrix = camera.GetProjectionMatrix();


	UINT(Time::* p_fps)();

	INT(D3D::* p_d3dEndScene)();

	FLOAT(Time::* p_deltaTime)();

	FLOAT(Time::* p_timeUpdate)();

	INT(GameObject::* p_drawObj)();

	BOOL(Window::* p_windowUpdate)();

	INT(GameObjectManager::* p_draw)();
	INT(GameObject::* p_moveObj)();

	INT(Camera::* p_cameraUpdate)(FLOAT);

	INT(GameObjectManager::* p_amountSpawned)();


	INT(HUD::* p_debugPrint)(INT, EGameObjectType);

	INT(D3D::* p_d3dBeginScene)(FLOAT, FLOAT, FLOAT);

	INT(Light::* p_lightRender)(ID3D11DeviceContext*);

	INT(HUD::* p_hud)(UINT, Camera*, INT, BOOL, BOOL, BOOL);

	INT(GameObjectManager::* p_spawnObject)(EGameObjectType);

	INT(Material::* p_materialRender)(XMMATRIX*, XMMATRIX*, XMMATRIX*);
};

