#pragma once
#include "Utils.h"
#include <d3d11.h>
#include <xutility>

class D3D
{
public:
	INT Init(HWND _hwnd, UINT _width, UINT _height, BOOL _fullscreen);
	INT BeginScene(FLOAT _red, FLOAT _green, FLOAT _blue);
	INT EndScene();
	void DeInit();


	ID3D11Device* GetDevice() { return p_device; }
	ID3D11DeviceContext* GetDeviceContext() { return p_deviceContext; }

private:
	ID3D11Device* p_device = nullptr;					// creating objects, e.g. vertex buffer
	ID3D11DeviceContext* p_deviceContext = nullptr;		// handling render pipeline, e.g. set resopurces or draw call
	IDXGISwapChain* p_DXGISwapChain = nullptr;				// hold refernces to front and back buffer and swap them
	ID3D11RenderTargetView* p_RenderTargetView = nullptr;	// Decribe the Target the render pipeline will render in, e.g. back buffer
	ID3D11DepthStencilView* p_depthStencilView = nullptr;	// hold ref to depth and stencil buffer texture
	ID3D11RasterizerState* p_rasterizerState = nullptr;		// set up rasterizer stage
};

