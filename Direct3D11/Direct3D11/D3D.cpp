#include "D3D.h"
#include "imgui/imgui_impl_dx11.h"

INT D3D::Init(HWND _hwnd, UINT _width, UINT _height, BOOL _fullscreen)
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();


	HRESULT hr;
	// 1. Set up the presentation parameter

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.OutputWindow = _hwnd;
	swapChainDesc.Windowed = !_fullscreen;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Width = _width;
	swapChainDesc.BufferDesc.Height = _height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.SampleDesc.Count = 1; // this MSAA count has to be set to atleast 1


	// 2.Create Device with the choosen parameter

	D3D_FEATURE_LEVEL supportedFeatureLevels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	D3D_FEATURE_LEVEL choosenFeatureLevel = {};

	hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr, //use Primary Graphics Card
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0, //Flags
		supportedFeatureLevels, // Searches which dx will be supported
		std::size(supportedFeatureLevels),
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&p_DXGISwapChain,
		&p_device,
		&choosenFeatureLevel,
		&p_deviceContext
	);
	CheckFailed(hr, 20);

	//Create Render Target View
	ID3D11Texture2D* p_BackBufferTexture = nullptr;
	hr = p_DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&p_BackBufferTexture));
	CheckFailed(hr, 22);

	hr = p_device->CreateRenderTargetView(p_BackBufferTexture, nullptr, &p_RenderTargetView);
	CheckFailed(hr, 24);

	SafeRelease<ID3D11Texture2D>(p_BackBufferTexture);

	//Death Stencil View
	ID3D11Texture2D* p_depthStencilTexture = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilTextureDesc = {};
	depthStencilTextureDesc.Width = _width;
	depthStencilTextureDesc.Height = _height;
	depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilTextureDesc.ArraySize = 1; // at least one texture
	depthStencilTextureDesc.SampleDesc.Count = 1; // should be always 1

	hr = p_device->CreateTexture2D(&depthStencilTextureDesc, nullptr, &p_depthStencilTexture);
	CheckFailed(hr, 26);

	hr = p_device->CreateDepthStencilView(p_depthStencilTexture, nullptr, &p_depthStencilView);
	CheckFailed(hr, 28);

	SafeRelease<ID3D11Texture2D>(p_depthStencilTexture);

	//Rasterizer State
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;

	hr = p_device->CreateRasterizerState(&rasterizerDesc, &p_rasterizerState);
	CheckFailed(hr, 29);

	//Set Viewport
	D3D11_VIEWPORT viewPort = {}; // Describe area projectes onto screen/Window
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = _width;
	viewPort.Height = _height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	//Set Up Render pipeline
	p_deviceContext->OMSetRenderTargets(1, &p_RenderTargetView, p_depthStencilView);
	p_deviceContext->RSSetViewports(1, &viewPort);
	p_deviceContext->RSSetState(p_rasterizerState);

	ImGui_ImplDX11_Init(p_device, p_deviceContext);

	return 0;
}

INT D3D::BeginScene(FLOAT _red, FLOAT _green, FLOAT _blue)
{
	//Clear Back Buffer
	FLOAT backgroundColor[] = { _red, _green, _blue, 1.0f };
	p_deviceContext->ClearRenderTargetView(p_RenderTargetView, backgroundColor);

	//Clear depth buffer
	p_deviceContext->ClearDepthStencilView(p_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0xffffffff);

	return 0;
}

INT D3D::EndScene()
{
	//Swap Front and Back Buffer
	p_DXGISwapChain->Present(0, 0);

	return 0;
}

void D3D::DeInit()
{
	SafeRelease<ID3D11DepthStencilView>(p_depthStencilView);
	SafeRelease<ID3D11Device>(p_device);
	SafeRelease<ID3D11DeviceContext>(p_deviceContext);
	SafeRelease<IDXGISwapChain>(p_DXGISwapChain);
	SafeRelease<ID3D11RenderTargetView>(p_RenderTargetView);
	SafeRelease<ID3D11RasterizerState>(p_rasterizerState);
}

