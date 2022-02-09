#pragma once
#include"Window.h"
//#include "SpriteBatch.h"
//#include "SpriteFont.h"
#include <d3d11.h>
#include "D3D.h"
#include "Time.h"
#include "Camera.h"
#include "Mesh.h"


class HUD
{
public: 
	INT Init(ID3D11Device* _p_device, ID3D11DeviceContext* _p_deviceContext);
	INT Draw_Text(UINT _p_fps, Camera* _p_cam, INT _lineAmount, BOOL _displayFps, BOOL _displayCamPos, BOOL _displayBoxPos);

	INT PrintMousePos(float _mousePosX, float _mousePosY);

private:
	XMFLOAT3(Camera::* p_camPos)() = 0;
	XMFLOAT3(Camera::* p_camRot)() = 0;

	XMFLOAT3(Mesh::* p_objPos)() = 0;
	XMFLOAT3(Mesh::* p_objRot)() = 0;


	//std::unique_ptr<SpriteBatch> spriteBatch = 0;
	//std::unique_ptr<SpriteFont> spriteFont = 0;

	ID3D11Device* p_device;
	ID3D11DeviceContext* p_deviceContext;
};

