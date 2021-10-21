#pragma once
#include <d3dx12.h>
#include <dxgi1_6.h>
#include "Commands.h"
#include "Descriptor.h"
#include "PipelineObjectContainer.h"
class ModelRenderer
{
public:
	ModelRenderer() {};
	
	
	
	//�R�A�N���X�ŃX���b�v�`�F�[���A�����_�[�^�[�Q�b�g�r���[�A�f�v�X�X�e���V���r���[�B
// ���[�J�[�N���X�Ńp�C�v���C���I�u�W�F�N�g�i�V�F�[�_�[�A���[�g�V�O�l�`���APSO�j�����A
//�쐬�����������A�G���W���̏������N���X�ł��̃N���X�̃R���X�g���N�^�ɓn���ď���������)
	
	ModelRenderer(IDXGISwapChain3* swapchain, std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>renderTargets, const UINT& rtvDescriptorSize, const std::vector<Microsoft::WRL::ComPtr<ID3D12Fence1>> m_frameFences, const DescriptorHeapsContainer& DSV_RTV, const Commands& commands, const GraphicPipeLineObjectContainer& pipelineobjContainer, std::vector<UINT64> m_frameFenceValues);
	void Render(
		
		
		
	);
	const std::vector<Microsoft::WRL::ComPtr<ID3D12Resource1>> constantBuffers;
	void WaitPreviousFrame(ID3D12CommandQueue* queue, const std::vector<Microsoft::WRL::ComPtr<ID3D12Fence1>> m_frameFences, std::vector<UINT64> m_frameFenceValues);
	void MakeCommand(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& command, std::vector<Microsoft::WRL::ComPtr<ID3D12Resource1>> m_constantBuffers;);
	
	Microsoft::WRL::ComPtr<IDXGISwapChain3> m_swapchain;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>m_renderTargets;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Fence1>> m_frameFences;
	
	std::vector<UINT64> m_frameFenceValues;
	Commands m_commands;
	DescriptorHeapsContainer m_DSV_RTV;
	GraphicPipeLineObjectContainer pipelineobjContainer;
	
	UINT m_frameIndex;
	const UINT FrameBufferCount = 2;
	HANDLE m_fenceWaitEvent;
	const UINT GpuWaitTimeout = (10 * 1000);  // 10s
};

