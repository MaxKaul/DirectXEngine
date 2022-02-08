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


	UINT width;
	UINT height;
	BOOL isFullScreen;


	D3D d3d = {};
	ID3D11Device* p_d3dDevice;
	ID3D11DeviceContext* p_d3dContext;

	POINT mousePoint;

	HUD hud = {};
	Time time = {};
	Light light = {};
	Window window = {};
	Camera camera = {};
	Material material = {};
	GameObject gameObject{};
	Light::LightData lightData = {};

	XMMATRIX* p_viewMatrix = camera.GetViewMatrix();
	XMFLOAT4X4* p_worldMatrix = gameObject.GetWorldMatrix();
	XMMATRIX* p_projectionMatrix = camera.GetProjectionMatrix();


	UINT(Time::* p_fps)();

	INT(D3D::* p_d3dEndScene)();

	FLOAT(Time::* p_deltaTime)();

	FLOAT(Time::* p_timeUpdate)();

	INT(GameObject::* p_drawObj)();

	BOOL(Window::* p_windowUpdate)();

	INT(GameObject::* p_moveObj)(FLOAT);

	INT(Camera::* p_cameraUpdate)(FLOAT);

	INT(D3D::* p_d3dBeginScene)(FLOAT, FLOAT, FLOAT);

	INT(Light::* p_lightRender)(ID3D11DeviceContext*);

	INT(HUD::* p_hud)(UINT, Camera*, INT, BOOL, BOOL, BOOL);

	INT(Material::* p_materialRender)(ID3D11DeviceContext*, XMFLOAT4X4*, XMMATRIX*, XMMATRIX*);
};
