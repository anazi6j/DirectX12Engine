#include "ModelRenderer.h"
#include "DX12EngineCore.h"
#include "ModelRendererWorker.h"
#include "PipelineState.h"
#include <DirectXMath.h>





D3D12_COMMAND_QUEUE_DESC queueDesc{
  D3D12_COMMAND_LIST_TYPE_DIRECT,
  0,
  D3D12_COMMAND_QUEUE_FLAG_NONE,
  0
};


void ModelRenderer::CreateSceneView(Microsoft::WRL::ComPtr<ID3D12Device> p_device, const DescriptorHeapsContainer& SceneCBVheap)
{


	// �萔�o�b�t�@/�萔�o�b�t�@�r���[�̐���
	m_constantBuffers.resize(FrameBufferCount);
	m_cbViews.resize(FrameBufferCount);


	for (UINT i = 0; i < FrameBufferCount; ++i)
	{
		UINT bufferSize = sizeof(ShaderParameters) + 255 & ~255;
		m_constantBuffers[i] = CreateBuffer(p_device.Get(), bufferSize, nullptr);

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbDesc{};
		cbDesc.BufferLocation = m_constantBuffers[i]->GetGPUVirtualAddress();
		cbDesc.SizeInBytes = bufferSize;

		CD3DX12_CPU_DESCRIPTOR_HANDLE handleCBV(SceneCBVheap.m_heapCbv->GetCPUDescriptorHandleForHeapStart(), ConstantBufferDescriptorBase + i, m_cbvDescriptorSize);
		D3D12_CPU_DESCRIPTOR_HANDLE handleCBV = SceneCBVheap.m_heapCbv->GetCPUDescriptorHandleForHeapStart()
		p_device->CreateConstantBufferView(&cbDesc, handleCBV);

		m_cbViews[i] = CD3DX12_GPU_DESCRIPTOR_HANDLE(SceneCBVheap.m_heapCbv->GetGPUDescriptorHandleForHeapStart(), ConstantBufferDescriptorBase + i, m_srvcbvDescriptorSize);
	}

}




ModelRenderer::ModelRenderer(const std::shared_ptr<DX12EngineCore> core, const Commands& commands,
	std::shared_ptr<Model> in_model, const std::shared_ptr<ModelRendererWorker> in_modelRendererWorker,
	const DescriptorHeapsContainer& descheaps) {


	CreateCommandAllocators(m_core->m_device.Get(), FrameBufferCount);
	CreateCommandQueue(m_core->m_device.Get());
	CreateCommandLists(m_core->m_device.Get());


	CreateSceneView(m_core->m_device.Get(), SceneCBVheap);
	m_commandList->Close();
	m_core = core;
	m_model = in_model;
	m_frameIndex = core->m_swapchain->GetCurrentBackBufferIndex();
	m_heapSrv = descheaps.heapSrv;
	m_heapCbv = descheaps.heapCbv;
	m_heapRTV = descheaps.heapRtv;
	m_heapDSV = descheaps.heapDsv;
	m_heapSampler = descheaps.heapSampler;
	m_commands = commands;
	m_Rendererworker = in_modelRendererWorker;
	m_swapchain = m_core->m_swapchain.Get();
	m_viewport = m_core->m_viewport;
	m_scissorRect = m_core->m_scissorRect;
	m_frameFences = m_core->m_frameFences;
	m_frameFenceValues = m_core->m_frameFenceValues;
	

}




void ModelRenderer::Render(std::shared_ptr<Camera>
	 camera
)
{
	m_frameIndex = m_core->m_swapchain->GetCurrentBackBufferIndex();

	m_commands.allocators[m_frameIndex]->Reset();
	m_commands.list->Reset(
		m_commands.allocators[m_frameIndex].Get(),
		nullptr
	);

	// �X���b�v�`�F�C���\���\���烌���_�[�^�[�Q�b�g�`��\��
	auto barrierToRT = CD3DX12_RESOURCE_BARRIER::Transition(
		m_renderTargets[m_frameIndex].Get(),
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET);
	m_commands.list->ResourceBarrier(1, &barrierToRT);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtv(
		m_heapRTV->GetCPUDescriptorHandleForHeapStart(),
		m_frameIndex, rtvDescriptorSize);
	CD3DX12_CPU_DESCRIPTOR_HANDLE dsv(
	m_heapDSV->GetCPUDescriptorHandleForHeapStart()
	);

	// �J���[�o�b�t�@(�����_�[�^�[�Q�b�g�r���[)�̃N���A
	const float clearColor[] = { 0.1f,0.25f,0.5f,0.0f }; // �N���A�F
	m_commands.list->ClearRenderTargetView(rtv, clearColor, 0, nullptr);

	// �f�v�X�o�b�t�@(�f�v�X�X�e���V���r���[)�̃N���A
	m_commands.list->ClearDepthStencilView(
		dsv, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// �`�����Z�b�g
	m_commands.list->OMSetRenderTargets(1, &rtv, FALSE, &dsv);

	MakeCommand(m_commands.list,m_Rendererworker->m_constantBuffers,camera);

	// �����_�[�^�[�Q�b�g����X���b�v�`�F�C���\���\��
	auto barrierToPresent = CD3DX12_RESOURCE_BARRIER::Transition(
		m_renderTargets[m_frameIndex].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT
	);
	m_commands.list->ResourceBarrier(1, &barrierToPresent);

	m_commands.list->Close();

	ID3D12CommandList* lists[] = { m_commands.list.Get() };
	m_commands.queue->ExecuteCommandLists(1, lists);

	m_core->m_swapchain->Present(1, 0);

	WaitPreviousFrame();
}


void ModelRenderer::WaitPreviousFrame()
{
	// ���݂̃t�F���X�� GPU �����B��ݒ肳���l���Z�b�g.
	auto& fence = m_frameFences[m_frameIndex];
	const auto currentValue = ++m_frameFenceValues[m_frameIndex];
	m_commands.queue->Signal(fence.Get(), currentValue);

	// ����������R�}���h�i�A���P�[�^�|�j�̂��͎̂��s�����ς݂����A
	// �΂ɂȂ��Ă���t�F���X�Ŋm�F����.
	auto nextIndex = (m_frameIndex + 1) % FrameBufferCount;
	const auto finishExpected = m_frameFenceValues[nextIndex];
	const auto nextFenceValue = m_frameFences[nextIndex]->GetCompletedValue();
	if (nextFenceValue < finishExpected)
	{
		// GPU ���������̂��߁A�C�x���g�őҋ@����
		m_frameFences[nextIndex]->SetEventOnCompletion(finishExpected, m_fenceWaitEvent);
		WaitForSingleObject(m_fenceWaitEvent, GpuWaitTimeout);
	}
}


void ModelRenderer::MakeCommand(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& command, std::vector<Microsoft::WRL::ComPtr<ID3D12Resource1>> m_constantBuffers,std::shared_ptr<Camera> camera)
{
	
	/*
	// �e�s��̃Z�b�g.
	ShaderParameters shaderParams;
	XMStoreFloat4x4(&shaderParams.mtxWorld, XMMatrixRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMConvertToRadians(45.0f)));
	auto mtxView = XMMatrixLookAtLH(
		XMVectorSet(0.0f, 3.0f, -5.0f, 0.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	);
	auto mtxProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), m_viewport.Width / m_viewport.Height, 0.1f, 100.0f);
	XMStoreFloat4x4(&shaderParams.mtxView, XMMatrixTranspose(mtxView));
	XMStoreFloat4x4(&shaderParams.mtxProj, XMMatrixTranspose(mtxProj));
	*/
	DirectX::XMStoreFloat4x4(&m_model->modelmat, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f),
		DirectX::XMMatrixRotationAxis(
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),
			DirectX::XMConvertToRadians(45.0f))), DirectX::XMMatrixTranslation(m_model->m_position.x, m_model->m_position.y, m_model->m_position.z)));

	camera->Update(DirectX::XMLoadFloat4x4(&m_model->modelmat),&shaderParams);
	// �萔�o�b�t�@�̍X�V.
	auto& constantBuffer = m_Rendererworker->m_constantBuffers[m_frameIndex];
	{
		void* p;
		CD3DX12_RANGE range(0, 0);
		constantBuffer->Map(0, &range, &p);
		//memcpy(p, &shaderParams, sizeof(shaderParams));
		memcpy(p, &shaderParams, sizeof(shaderParams));
		constantBuffer->Unmap(0, nullptr);
	}
	//��CopyToVRAM
	// �p�C�v���C���X�e�[�g�̃Z�b�g
	m_commands.list->SetPipelineState(m_model->m_modelPSO->m_graphicpipelinestate.Get());
	// ���[�g�V�O�l�`���̃Z�b�g
	m_commands.list->SetGraphicsRootSignature(m_model->m_rootSignature.Get());
	// �r���[�|�[�g�ƃV�U�[�̃Z�b�g
	m_commands.list->RSSetViewports(1, &m_viewport);
	m_commands.list->RSSetScissorRects(1, &m_scissorRect);

	// �f�B�X�N���v�^�q�[�v���Z�b�g.
	ID3D12DescriptorHeap* heaps[] = {
	 m_heapSrv.Get(),m_heapCbv.Get() ,m_heapSampler.Get()
	};
	m_commands.list->SetDescriptorHeaps(_countof(heaps), heaps);

	// �v���~�e�B�u�^�C�v�A���_�E�C���f�b�N�X�o�b�t�@�̃Z�b�g
	m_commands.list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	
	m_commands.list->IASetVertexBuffers(0, 1, &m_model->m_vertexBufferView);
	m_commands.list->IASetIndexBuffer(&m_model->m_indexBufferView);

	m_commands.list->SetGraphicsRootDescriptorTable(0, m_heapSrv->GetGPUDescriptorHandleForHeapStart());
	m_commands.list->SetGraphicsRootDescriptorTable(0, m_heapCbv->GetGPUDescriptorHandleForHeapStart());
	//m_commands.list->SetGraphicsRootDescriptorTable(1, m_model->m_srv);
	m_commands.list->SetGraphicsRootDescriptorTable(2, m_heapSampler->GetGPUDescriptorHandleForHeapStart());

	// �`�施�߂̔��s
	m_commands.list->DrawIndexedInstanced(m_model->m_indexCount, 1, 0, 0, 0);
}
