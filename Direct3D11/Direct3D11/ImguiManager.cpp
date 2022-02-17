#include "ImguiManager.h"
#include "ImguiManager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

ImguiManager::ImguiManager()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	//ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_DockingEnable;
}

ImguiManager::~ImguiManager()
{
	ImGui::DestroyContext();
}

INT ImguiManager::Update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	return 0;
}

INT ImguiManager::EndUpdate()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return 0;
}

XMFLOAT2 ImguiManager::GetMousePos()
{
	ImVec2 mousePos = ImGui::GetMousePos();

	return XMFLOAT2(mousePos.x, mousePos.y);
}
