#pragma once
#include <wrl.h>
#include <d3dcompiler.h>
#include <d3dx12.h>
//�����_�����O�p�C�v���C���ɕK�v�ȁA�V�F�[�_�[�A���[�g�V�O�l�`���ƃp�C�v���C���X�e�[�g�I�u�W�F�N�g���i�[����

struct GraphicPipeLineObjectContainer
{

	Microsoft::WRL::ComPtr<ID3DBlob>  m_vs, m_ps;
	//�n���A�W�I���g����������Ă����B
	Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipeline;
};