#include "Run.h"

INT Run::Init(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	 hInstance = _hInstance;
	 hPrevInstance = _hPrevInstance;
	 lpCmdLine = _lpCmdLine;
	 nCmdShow = _nCmdShow;

	 width = 1024;
	 height = 768;
	 isFullScreen = false;

	 INT error = window.Init(hInstance, width, height);
	 CheckError(error);

	 error = d3d.Init(window.GetWindowHandle(), width, height, isFullScreen);
	 CheckError(error);

	 p_device = d3d.GetDevice();
	 p_deviceContext = d3d.GetDeviceContext();

	 error = camera.Init(width, height, 0, 0.15f, 1000.0f);
	 camera.SetPosition(0.0f, 0.0f, -10.0f);
	 CheckError(error);

	 error = time.Init();
	 CheckError(error);

	 error = material.Init(p_device, TEXT("F:\\texture.png"), p_deviceContext);
	 CheckError(error);

	 lightData.LightDirection = { -1.0f, 0.0f, 1.0f };
	 //lightData.LightDirection = { *camera.DirX, *camera.DirY, *camera.DirZ };
	 lightData.LightDiffuseColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	 lightData.LightIntensity = 5.0f;

	 error = light.Init(p_device, lightData);
	 CheckError(error);

	 error = goManager.Init(p_device, p_deviceContext, p_worldMatrix, p_viewMatrix, p_projectionMatrix, spawnAmount);
	 CheckError(error);

	 //error = gameObject.Init("F:\\Robot.fbx", p_d3dDevice, p_d3dContext);
	 //CheckError(error);

	 error = hud.Init(p_device, p_deviceContext);
	 CheckError(error);


	 p_fps = &Time::GetFPS;
	 p_hud = &HUD::Draw_Text;
	 p_timeUpdate = &Time::Update;
	 p_lightRender = &Light::Render;
	 p_d3dEndScene = &D3D::EndScene;
	 p_drawObj = &GameObject::Draw;
	 p_moveObj = &GameObject::Move;
	 p_cameraUpdate = &Camera::Update;
	 p_windowUpdate = &Window::Update;
	 p_deltaTime = &Time::GetDeltaTime;
	 p_d3dBeginScene = &D3D::BeginScene;
	 p_updateGui = &ImguiManager::Update;
	 p_materialRender = &Material::Render;
	 p_setMousePos = &Camera::SetMouseMousePos;
	 p_endUpdateGui = &ImguiManager::EndUpdate;
	 p_getMousePos = &ImguiManager::GetMousePos;


	 RunApplication();

	return 0;
}

INT Run::RunApplication()
{
	while (BOOL windowUpdate = (window.*p_windowUpdate)())
	{
		FLOAT updateTime = (time.*p_timeUpdate)();

		FLOAT d3dBeginScene = (d3d.*p_d3dBeginScene)(0, 0, 0);

		INT updateCamera = (camera.*p_cameraUpdate)((time.*p_deltaTime)());

		INT renderMaterial = (material.*p_materialRender)(p_deviceContext, p_worldMatrix, p_viewMatrix, p_projectionMatrix);

		INT renderLight = (light.*p_lightRender)(p_deviceContext);

		INT moveObj = (gameObject.*p_moveObj)((time.*p_deltaTime)());

		INT drawObj = (gameObject.*p_drawObj)();

		INT updateGUI = (imguiManager.*p_updateGui)();

		INT drawFps = (hud.*p_hud)((time.*p_fps)(), &camera, 3, true, true, true);

		INT mousePos = (camera.*p_setMousePos)((imguiManager.*p_getMousePos)());

		INT endUpdateGUI = (imguiManager.*p_endUpdateGui)();

		INT endScene = (d3d.*p_d3dEndScene)();
	}

	light.DeInit();
	material.DeInit();
	d3d.DeInit();
	window.DeInit();

	return 0;
}
