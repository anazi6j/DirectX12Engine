#pragma once
#include <d3dx12.h>
#include <wrl.h>
#include "ShaderParameters.h"
#include <wrl.h>

struct DescriptorHeapWorker;
class ModelRendererWorker
{
public:
	
	

	
	
	ModelRendererWorker(Microsoft::WRL::ComPtr<ID3D12Device> p_device, UINT FrameBufferCount, const DescriptorHeapWorker& SceneCBVheap);
	HRESULT CreateCommandQueue(ID3D12Device* p_device);
	//������ŃR�}���h�n�C���^�[�t�F�[�X���쐬����B
	CD3DX12_VIEWPORT  m_viewport;
	CD3DX12_RECT m_scissorRect;
	
	
	
	void CreateCommandAllocators(ID3D12Device* p_device, UINT FrameBufferCount);
	void CreateCommandLists(ID3D12Device* p_device);
	
	

	
	
	void CreateSceneView(Microsoft::WRL::ComPtr<ID3D12Device> p_device, const DescriptorHeapWorker& SceneCBVheap);
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList1> m_commandList;

	Microsoft::WRL::ComPtr <ID3D12CommandQueue> m_commandQueue;

	std::vector< Microsoft::WRL::ComPtr <ID3D12CommandAllocator>> m_commandAllocators;
	
	const UINT FrameBufferCount = 2;

	std::vector<D3D12_GPU_DESCRIPTOR_HANDLE> m_cbViews;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource1>> m_constantBuffers;
	
};

