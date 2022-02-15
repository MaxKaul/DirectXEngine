#include "HUD.h"

INT HUD::Init(ID3D11Device* _p_device, ID3D11DeviceContext* _p_deviceContext)
{
	p_device = _p_device;
	p_deviceContext = _p_deviceContext;

	p_camPos = &Camera::GetPosFloat3;
	p_camRot = &Camera::GetRotFloat3;

	spriteBatch = std::make_unique<DirectX::SpriteBatch>(p_deviceContext);
	spriteFont = std::make_unique<DirectX::SpriteFont>(p_device, L"Assets\\fonts\\arial_16.spritefont");

	//p_objPos = &Mesh::GetPos;
	//p_objRot = &Mesh::GetRot;
	return 0;
}

INT HUD::Draw_Text(UINT _p_fps,Camera* _p_cam, INT _p_lineAmount, BOOL _p_displayFps, BOOL _p_displayCamPos, BOOL _p_displayObjTransform)
{
	wstring output = L"";

	if (_p_displayFps)
	{
		wstring fps = to_wstring(_p_fps);
		output += TEXT("FPS: ") + fps + TEXT("\n\n");
	}

	if (_p_displayCamPos)
	{
		XMFLOAT3 camPos = (*_p_cam.*p_camPos)();
		XMFLOAT3 camRot = (*_p_cam.*p_camRot)();

		wstring posX = to_wstring((int)camPos.x);
		wstring posY = to_wstring((int)camPos.y);
		wstring posZ = to_wstring((int)camPos.z);

		wstring rotX = to_wstring((int)camRot.x);
		wstring rotY = to_wstring((int)camRot.y);
		wstring rotZ = to_wstring((int)camRot.z);

		output += TEXT("Camera Transform \n")
				  TEXT("Position; \n")
				  TEXT("X: ") + posX + TEXT(" Y: ") + posY + TEXT(" Z: ") + posZ + TEXT("\n")
				  TEXT("Rotation; \n") +
				  TEXT("X: ") + rotX + TEXT(" Y: ") + rotY + TEXT(" Z: ") + rotZ + TEXT("\n\n");;
	}

	if (_p_displayObjTransform)
	{
		///*XMFLOAT3 objPos = (*_mesh.*p_objPos)();
		//XMFLOAT3 objRot = (*_mesh.*p_objRot)();*/

		//wstring posX = to_wstring((int)objPos.x);
		//wstring posY = to_wstring((int)objPos.y);
		//wstring posZ = to_wstring((int)objPos.z);

		//wstring rotX = to_wstring((int)objRot.x);
		//wstring rotY = to_wstring((int)objRot.y);
		//wstring rotZ = to_wstring((int)objRot.z);

		//output += TEXT("Current Object \n")
		//		  TEXT("Position; \n")
		//		  TEXT("X: ") + posX + TEXT(" Y: ") + posY + TEXT(" Z: " ) + posZ + TEXT("\n")
		//		  TEXT("Rotation; \n") +
		//		  TEXT("X: ") + rotX + TEXT(" Y: ") + rotY + TEXT(" Z: " ) + rotZ + TEXT("\n\n");;

	}

	spriteBatch->Begin();

	spriteFont->DrawString(spriteBatch.get(), output.c_str(), XMFLOAT2(0.0f, 0.0f), Colors::Red, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f));

	spriteBatch->End();

	return 0;
}

INT HUD::PrintObjectSpawn_Debug(INT _amountOfSpawned, EGameObjectType _currentSelected)
{
	wstring selected = L"";

	switch (_currentSelected)
	{
	case EGameObjectType::eCamera:
		selected = L"Camera";
		break;
	case EGameObjectType::eRobot:
		selected = L"Robot";
		break;
	case EGameObjectType::eNanosuit:
		selected = L"Nanosuit";
		break;
	default:
		break;
	}
	
	wstring output = TEXT(" Select Nanosuit: P \n Select Robot:     O \n\n Press K to Spawn \n")  TEXT(" ") + selected + TEXT("\n\n Amount of Spawned: ") + to_wstring(0);

	spriteBatch->Begin();

	spriteFont->DrawString(spriteBatch.get(), output.c_str(), XMFLOAT2(0.0f, 0.0f), Colors::Red, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f));

	spriteBatch->End();


	return 0;
}
