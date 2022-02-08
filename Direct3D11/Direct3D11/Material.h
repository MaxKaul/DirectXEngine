#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "VertexBuffer.h"
#include "Vertex.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
#include "WICTextureLoader11.h"
#include "Utils.h"

using namespace DirectX;

class Material
{
public:
	INT Init(ID3D11Device* _p_d3dDevice, LPCTSTR _textureName, ID3D11DeviceContext* _p_d3dDeviceContext);
	INT Render(ID3D11DeviceContext* _p_d3dDeviceContext, XMFLOAT4X4* _p_worldMatrix, XMMATRIX* _p_viewMatrix, XMMATRIX* _p_projectionMatrix);
	void DeInit();

private:

	INT CreateVertexShader(ID3D11Device* _p_d3dDevice);
	INT CreatePixelShader(ID3D11Device* _p_d3dDevice);
	INT CreateInputLayout(ID3D11Device* _p_d3dDevice, ID3DBlob* _p_vertexShaderData);
	INT CreateMatrixBuffer(ID3D11Device* _p_d3dDevice, ID3D11DeviceContext* _p_d3dDeviceContext);
	INT SetMatricesAndConstBuffer(ID3D11DeviceContext* _p_d3dDeviceContext, XMFLOAT4X4* _p_worldMatrix, XMMATRIX* _p_viewMatrix, XMMATRIX* _p_projectionMatrix);
	INT CreateTextureAndSampler(ID3D11Device* _p_d3dDevice, LPCTSTR _textureName);

	ID3D11VertexShader* p_VertexShader = nullptr;
	ID3D11PixelShader* p_PixelShader = nullptr;
	ID3D11InputLayout* p_InputLayout = nullptr;

	ConstantBuffer<CB_VS_VertexShader> constantBuffer;

	ID3D11ShaderResourceView* p_Texture = nullptr;
	ID3D11SamplerState* p_SamplerState = nullptr;
};

