#include "HUD.h"
#include "imgui/imgui.h"

INT HUD::Init(ID3D11Device* _p_device, ID3D11DeviceContext* _p_deviceContext)
{
	p_device = _p_device;
	p_deviceContext = _p_deviceContext;

	p_camPos = &Camera::GetPosFloat3;
	p_camRot = &Camera::GetRotFloat3;

	//p_objPos = &Mesh::GetPos;
	//p_objRot = &Mesh::GetRot;
	return 0;
}

INT HUD::Draw_Text(UINT _p_fps,Camera* _p_cam, INT _p_lineAmount, BOOL _p_displayFps, BOOL _p_displayCamPos, BOOL _p_displayObjTransform)
{

	

	return 0;
}
