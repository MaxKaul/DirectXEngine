 #include "Material.h"

INT Material::Init(ID3D11Device* _p_d3dDevice, LPCTSTR _textureName, ID3D11DeviceContext* _p_d3dDeviceContext)
{
	INT error = CreateVertexShader(_p_d3dDevice);
	CheckError(error);

	error = CreatePixelShader(_p_d3dDevice);
	CheckError(error);

	error = CreateMatrixBuffer(_p_d3dDevice, _p_d3dDeviceContext);
	CheckError(error);

	error = CreateTextureAndSampler(_p_d3dDevice, _textureName);
	CheckError(error);

	return 0;
}

INT Material::Render(ID3D11DeviceContext* _p_d3dDeviceContext, XMFLOAT4X4* _p_worldMatrix, XMMATRIX* _p_viewMatrix, XMMATRIX* _p_projectionMatrix)
{
	//Set texture and Sampler State
	_p_d3dDeviceContext->PSSetShaderResources(0, 1, &p_Texture);
	_p_d3dDeviceContext->PSSetSamplers(0, 1, &p_SamplerState);

	//Set Shader Pipeline
	_p_d3dDeviceContext->VSSetShader(p_VertexShader, nullptr, 0);
	_p_d3dDeviceContext->PSSetShader(p_PixelShader, nullptr, 0);
	_p_d3dDeviceContext->IASetInputLayout(p_InputLayout);

	//Set Matrices
	SetMatricesAndConstBuffer(_p_d3dDeviceContext, _p_worldMatrix, _p_viewMatrix, _p_projectionMatrix);

	return 0;
}

void Material::DeInit()
{
	SafeRelease<ID3D11ShaderResourceView>(p_Texture);
	SafeRelease<ID3D11SamplerState>(p_SamplerState);
	SafeRelease<ID3D11InputLayout>(p_InputLayout);
	SafeRelease<ID3D11PixelShader>(p_PixelShader);
	SafeRelease<ID3D11VertexShader>(p_VertexShader);
}

INT Material::CreateVertexShader(ID3D11Device* _p_d3dDevice)
{
	ID3DBlob* p_CompiledShaderCode = nullptr;


	//2. Load already compiled Shader
	//HRESULT hr = D3DReadFileToBlob(TEXT("ColorVertexShader.cso"), &p_CompiledShaderCode);
	//HRESULT hr = D3DReadFileToBlob(TEXT("TextureVertexShader.cso"), &p_CompiledShaderCode);
	HRESULT hr = D3DReadFileToBlob(TEXT("LightingVertexShader.cso"), &p_CompiledShaderCode);
	CheckFailed(hr, 60);

	//Create Shader Code
	hr = _p_d3dDevice->CreateVertexShader(p_CompiledShaderCode->GetBufferPointer(), p_CompiledShaderCode->GetBufferSize(), nullptr, &p_VertexShader);
	CheckFailed(hr, 62);

	INT error = CreateInputLayout(_p_d3dDevice, p_CompiledShaderCode);
	CheckError(error);

	SafeRelease<ID3DBlob>(p_CompiledShaderCode);

	return 0;
}

INT Material::CreatePixelShader(ID3D11Device* _p_d3ddevice)
{
	ID3DBlob* p_CompiledShaderCode = nullptr;

	//HRESULT hr = D3DReadFileToBlob(TEXT("ColorPixelShader.cso"), &p_CompiledShaderCode);
	//HRESULT hr = D3DReadFileToBlob(TEXT("TexturePixelShader.cso"), &p_CompiledShaderCode);
	HRESULT hr = D3DReadFileToBlob(TEXT("LightingPixelShader.cso"), &p_CompiledShaderCode);
	CheckFailed(hr, 64);

	hr = _p_d3ddevice->CreatePixelShader(p_CompiledShaderCode->GetBufferPointer(), p_CompiledShaderCode->GetBufferSize(), nullptr, &p_PixelShader);
	CheckFailed(hr, 66);

	SafeRelease<ID3DBlob>(p_CompiledShaderCode);

	return 0;
}

INT Material::CreateInputLayout(ID3D11Device* _p_d3dDevice, ID3DBlob* _p_vertexShaderData)
{
	D3D11_INPUT_ELEMENT_DESC elements[4] = {};

	//Position
	elements[0].SemanticName = "POSITION";
	elements[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	//Position
	elements[1].SemanticName = "NORMAL";
	elements[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	//Position
	elements[2].SemanticName = "TEXCOORD";
	elements[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	elements[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	//Position
	elements[3].SemanticName = "COLOR";
	elements[3].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	elements[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = _p_d3dDevice->CreateInputLayout
	(
		elements,
		4,
		_p_vertexShaderData->GetBufferPointer(),
		_p_vertexShaderData->GetBufferSize(),
		&p_InputLayout
	);


	CheckFailed(hr, 68);

	return 0;
}

INT Material::CreateMatrixBuffer(ID3D11Device* _p_d3dDevice, ID3D11DeviceContext* _p_d3dDeviceContext)
{
	HRESULT hr = constantBuffer.Init(_p_d3dDevice, _p_d3dDeviceContext);
	CheckFailed(hr, 61);

	return 0;
}

INT Material::SetMatricesAndConstBuffer(ID3D11DeviceContext* _p_d3dDeviceContext, XMFLOAT4X4* _p_worldMatrix, XMMATRIX* _p_viewMatrix, XMMATRIX* _p_projectionMatrix)
{
	if(!(constantBuffer.ApplyChanges(_p_worldMatrix, *_p_viewMatrix, *_p_projectionMatrix)))
		return 0;

	_p_d3dDeviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

	return 0;
}

INT Material::CreateTextureAndSampler(ID3D11Device* _p_d3dDevice, LPCTSTR _textureName)
{
	// Create Texture
	HRESULT hr = CreateWICTextureFromFile(_p_d3dDevice, _textureName, nullptr, &p_Texture, 0);
	CheckFailed(hr, 63);

	// Create Sampler State
	D3D11_SAMPLER_DESC desc = {};

	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	hr = _p_d3dDevice->CreateSamplerState(&desc, &p_SamplerState);
	CheckFailed(hr, 65);

	return 0;
}
