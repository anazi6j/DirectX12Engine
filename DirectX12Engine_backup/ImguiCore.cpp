
#include "ImguiCore.h"



ImguiCore::ImguiCore(const HWND& hwnd,ID3D12Device* device, const
	 DirectX::DescriptorHeap& desc,
	D3D12_CPU_DESCRIPTOR_HANDLE srvcpuhandle,
	const D3D12_GPU_DESCRIPTOR_HANDLE& srvgpuhandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	auto d3ddevice = device;
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX12_Init(d3ddevice, 3,
		DXGI_FORMAT_B8G8R8A8_UNORM, desc.Heap(),
		srvcpuhandle,
		srvgpuhandle);


}
void ImguiCore::ImguiCore_Tick()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	                         // Create a window {
	

}

bool show_demo_window = true;
bool show_another_window = false;
void ImguiCore::RenderGUIpanel(DX::DeviceResources* deviceresources)
{
	
	ImGui::Begin("Rendering Test Menu");
	ImGui::SetWindowSize(ImVec2(400, 500),
		ImGuiCond_::ImGuiCond_FirstUseEver);
	
	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), deviceresources->GetCommandList());
}

void ImguiCore::EndRenderImguicore()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

