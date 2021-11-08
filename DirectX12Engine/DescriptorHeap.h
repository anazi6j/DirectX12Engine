#pragma once
#include <d3dx12.h>
#include <wrl.h>



struct DescriptorHeap {
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_heapSrvCbv;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_heapSampler;
	UINT  m_samplerDescriptorSize;
	D3D12_GPU_DESCRIPTOR_HANDLE m_sampler;
	D3D12_GPU_DESCRIPTOR_HANDLE m_srv;
	const UINT FrameBufferCount = 2;
	UINT m_srvcbvDescriptorSize = 0;

	void PrepareCBV_SRVHeaps(ID3D12Device* p_device)
	{
		// CBV/SRV �̃f�B�X�N���v�^�q�[�v
		//  0:�V�F�[�_�[���\�[�X�r���[
		//  1,2 : �萔�o�b�t�@�r���[ (FrameBufferCount�����g�p)


		UINT count = FrameBufferCount + 1;
		D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc{
		  D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		  count,
		  D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
		  0
		};
		p_device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&m_heapSrvCbv));
		m_srvcbvDescriptorSize = p_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		// �_�C�i�~�b�N�T���v���[�̃f�B�X�N���v�^�q�[�v
		D3D12_DESCRIPTOR_HEAP_DESC samplerHeapDesc{
		  D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
		  1,
		  D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
		  0
		};
		p_device->CreateDescriptorHeap(&samplerHeapDesc, IID_PPV_ARGS(&m_heapSampler));
		m_samplerDescriptorSize = p_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
	}
}