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

	 p_d3dDevice = d3d.GetDevice();
	 p_d3dContext = d3d.GetDeviceContext();

	 error = camera.Init(width, height, 0, 0.15f, 1000.0f);
	 camera.SetPosition(0.0f, 0.0f, -10.0f);
	 CheckError(error);

	 error = time.Init();
	 CheckError(error);

	 error = material.Init(p_d3dDevice, TEXT("texture.png"), p_d3dContext);
	 CheckError(error);


	 Light::LightData lightData = {};

	 lightData.LightDirection = { -1.0f, 0.0f, 1.0f };
	 //lightData.LightDirection = { *camera.DirX, *camera.DirY, *camera.DirZ };
	 lightData.LightDiffuseColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	 lightData.LightIntensity = 5.0f;

	 error = light.Init(p_d3dDevice, lightData);
	 CheckError(error);

	 error = gameObject.Init("FinalBaseMesh.obj", p_d3dDevice, p_d3dContext);
	 CheckError(error);

	 error = hud.Init(p_d3dDevice, p_d3dContext);
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
	 p_materialRender = &Material::Render;


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

		INT renderMaterial = (material.*p_materialRender)(p_d3dContext, p_worldMatrix, p_viewMatrix, p_projectionMatrix);

		INT renderLight = (light.*p_lightRender)(p_d3dContext);

		INT moveObj = (gameObject.*p_moveObj)(deltaTime);

		INT drawObj = (gameObject.*p_drawObj)();

		//INT drawFps = (hud.*p_hud)(fps, &camera, 3, true, true, true);


		if (GetCursorPos(&mousePoint))
			if (ScreenToClient(window.GetWindowHandle(), &mousePoint))
			{
				FLOAT x = mousePoint.x;
				FLOAT y = mousePoint.y;

				camera.SetMouseMousePos(x, y);

				hud.PrintMousePos(x, y);
			}

		INT endScene = (d3d.*p_d3dEndScene)();
	}

	light.DeInit();
	material.DeInit();
	d3d.DeInit();
	window.DeInit();

	return 0;
}
