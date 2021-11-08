#pragma once
#include <d3dx12.h>
#include <wrl.h>
namespace Descriptor {
	HRESULT CreateSRV();//SRV
	HRESULT CreateUAV();//UAV�̍쐬
	HRESULT CreateCBV();// //CBV�̍쐬
	HRESULT CreateDSV();// DSV�̍쐬
	HRESULT CreateDescriptorHeap();//�f�B�X�N���v�^�q�[�v���쐬����
	
	HRESULT Create_MAXSIZE_DescriptorHeap();//�쐬�ł���ő�l�܂Ńf�B�X�N���v�^�q�[�v���쐬����B
	
	void PrepareDescriptorHeaps(ID3D12Device* p_device, Microsoft::WRL::ComPtr< ID3D12DescriptorHeap> rtvheap, 
		UINT FrameBufferCount, UINT& m_rtvDescriptorSize);
	void CreateDepthBuffer(ID3D12Device* p_device, int width, int height, 
		Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvheap);
	//����:�r���[�̃^�C�v


}

struct DescriptorHeapsContainer
{
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heapRtv;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heapDsv;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heapSrv;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heapUav;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heapCbv;
};