#include "PipelineState.h"
#include <stddef.h>
#include <stdlib.h>
#include "Vertex.h"
void PipelineState::CreatePipeLineState(ID3DBlob* pixelShader,ID3DBlob* vertexshader,ID3D12Device* device,ID3D12RootSignature* rootSignature) {
	// �C���v�b�g���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputElementDesc[] = {
	  { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, Pos), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA},
	  { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, offsetof(Vertex,Color), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA},
	  { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(Vertex,UV), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA}
	};

	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g�̐���.
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc{};
	// �V�F�[�_�[�̃Z�b�g
	psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexshader);
	psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader);
	// �u�����h�X�e�[�g�ݒ�
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	// ���X�^���C�U�[�X�e�[�g
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	// �o�͐��1�^�[�Q�b�g
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	// �f�v�X�o�b�t�@�̃t�H�[�}�b�g��ݒ�
	psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	psoDesc.InputLayout = { inputElementDesc, _countof(inputElementDesc) };

	// ���[�g�V�O�l�`���̃Z�b�g
	psoDesc.pRootSignature = rootSignature;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	// �}���`�T���v���ݒ�
	psoDesc.SampleDesc = { 1,0 };
	psoDesc.SampleMask = UINT_MAX; // �����Y���ƊG���o�Ȃ����x�����o�Ȃ��̂Œ���.

	auto hr = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_graphicpipelinestate));
	if (FAILED(hr))
	{
		throw std::runtime_error("CreateGraphicsPipelineState failed");
	}

}