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

	 /*error = goManager.Init(p_device, p_deviceContext, p_worldMatrix, p_viewMatrix, p_projectionMatrix);
	 CheckError(error);*/

	 error = camera.Init(width, height, 0, 0.15f, 1000.0f);
	 camera.SetPosition(0.0f, 0.0f, -10.0f);
	 CheckError(error);

	 error = time.Init();
	 CheckError(error);

	 error = material.Init(p_device, L"Assets\\textures\\texture.png", p_deviceContext);
	 CheckError(error);

	 lightData.LightDirection = { -1.0f, 0.0f, 1.0f };
	 //lightData.LightDirection = { *camera.DirX, *camera.DirY, *camera.DirZ };
	 lightData.LightDiffuseColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	 lightData.LightIntensity = 5.0f;

	 error = light.Init(p_device, lightData);
	 CheckError(error);

	 error = gameObject.Init("Assets\\obj - fbx\\Robot.fbx", "Assets\\textures\\texture.png", p_device, p_deviceContext, p_worldMatrix, p_viewMatrix, p_projectionMatrix);
	 CheckError(error);

	 error = hud.Init(p_device, p_deviceContext);
	 CheckError(error);


	 p_fps = &Time::GetFPS;
	 p_hud = &HUD::Draw_Text;
	 p_timeUpdate = &Time::Update;
	 p_lightRender = &Light::Render;
	 p_d3dEndScene = &D3D::EndScene;

	 //p_draw = &GameObjectManager::DrawSpawnedObjects;
	 p_moveObj = &GameObject::Move;
	 p_drawObj = &GameObject::Draw;

	 //p_spawnObject = &GameObjectManager::SpawnObject;
	 //p_amountSpawned = &GameObjectManager::AmountOfSpawned;

	 p_cameraUpdate = &Camera::Update;
	 p_windowUpdate = &Window::Update;
	 p_deltaTime = &Time::GetDeltaTime;
	 p_d3dBeginScene = &D3D::BeginScene;
	 p_materialRender = &Material::Render;


	 //p_debugPrint = &HUD::PrintObjectSpawn_Debug;
	 
	 RunApplication();

	return 0;
}

INT Run::RunApplication()
{
	while (BOOL windowUpdate = (window.*p_windowUpdate)())
	{
		UINT fps = (time.*p_fps)();
		FLOAT deltaTime = (time.*p_deltaTime)();
		FLOAT updateTime = (time.*p_timeUpdate)();

		FLOAT d3dBeginScene = (d3d.*p_d3dBeginScene)(0, 0, 0);

		INT updateCamera = (camera.*p_cameraUpdate)(deltaTime);

		//if(goManager.AmountOfSpawned() > 0)
		INT renderMaterial = (material.*p_materialRender)(p_deviceContext, p_worldMatrix, p_viewMatrix, p_projectionMatrix);

		INT renderLight = (light.*p_lightRender)(p_deviceContext);

		INT moveObj = (gameObject.*p_moveObj)();

		//INT drawObj = (goManager.*p_draw)();
		INT drawObj = (gameObject.*p_drawObj)();

		//INT drawFps = (hud.*p_hud)(fps, &camera, 3, true, true, true);

		//INT drawDebug = (hud.*p_debugPrint)((goManager.*p_amountSpawned)(), debugSpawnObj);


		if ((GetAsyncKeyState('P') & 0x8000))
			debugSpawnObj = EGameObjectType::eNanosuit;
		if ((GetAsyncKeyState('O') & 0x8000))
			debugSpawnObj = EGameObjectType::eRobot;

		/*if ((GetAsyncKeyState('K') & 0x8000))
			INT spawnObj = (goManager.*p_spawnObject)(debugSpawnObj);*/

		if (GetCursorPos(&mousePoint))
			if (ScreenToClient(window.GetWindowHandle(), &mousePoint))
			{
				

				FLOAT x = mousePoint.x;
				FLOAT y = mousePoint.y;

				camera.SetMouseMousePos(x, y);
			}

		INT endScene = (d3d.*p_d3dEndScene)();
	}

	light.DeInit();
	//material.DeInit();
	//d3d.DeInit();
	window.DeInit();

	return 0;
}
