#pragma once

#include <stierr.h>
#include <sstream>
#include <fstream>
#include <atlbase.h>
#include <string>
#include <d3dcompiler.h>
#include <dxcapi.h>
#include <Windows.h>
#include "dxc/include/dxc/Support/dxcapi.use.h"
#include <wrl.h>
#include "TesselationEffectPipelineDescription.h"
//�V�F�[�_�[
enum EShader {
	eShader_Raygeneration,		//�J�������C�𐶐�����V�F�[�_�[�B
	eShader_Miss,				//�J�������C���ǂ��ɂ��Ԃ���Ȃ��������ɌĂ΂��V�F�[�_�[�B
	eShader_PBRChs,				//�����Ƃ��߂��|���S���ƃJ�������C�����������Ƃ��ɌĂ΂��V�F�[�_�[�B
	eShader_ShadowChs,			//�����Ƃ��߂��|���S���ƃV���h�E���C�����������Ƃ��ɌĂ΂��V�F�[�_�[�B
	eShader_ShadowMiss,			//�V���h�E���C���ǂ��ɂ��Ԃ���Ȃ��������ɌĂ΂��V�F�[�_�[�B
	eShader_Num,				//�V�F�[�_�[�̐��B
};

//�V�F�[�_�[�f�[�^�\���́B
struct ShaderData {
	const wchar_t* entryPointName;				//�G���g���[�|�C���g�̖��O�B
	
};

class Shader {
public:
	void CreateTesslelationShader(ID3D12Device* device,
		Microsoft::WRL::ComPtr<ID3D12RootSignature> in_patchrootsignature,
		Microsoft::WRL::ComPtr<ID3D12PipelineState> in_patchpipelinestate,
		DirectX::RenderTargetState targetstate,
		const ShaderData& shaderData);
	D3D12_EXPORT_DESC libExport;
	D3D12_DXIL_LIBRARY_DESC dxLibdesc;
	void LoadShader(const wchar_t* filePath, const wchar_t* entrypoint);
	/// <summary>
	/// �R���p�C���ς݃V�F�[�_�[�f�[�^���擾�B
	/// </summary>
	/// <returns></returns>
	ID3DBlob* GetCompiledBlob() const
	{
		return m_blob;
	}
	IDxcBlob* GetCompiledDxcBlob() const
	{
		return m_dxcBlob;
	}
	
	/// <summary>
	/// �������ς݁H
	/// </summary>
	/// <returns></returns>
	bool IsInited() const
	{
		return m_isInited;
	}
private:
	
private:
	ID3DBlob* m_blob = nullptr;	//�R���p�C���ς݂̃V�F�[�_�[�f�[�^�B
	IDxcBlob* m_dxcBlob = nullptr;	//DXC�R���p�C�����g�p�����Ƃ��̃V�F�[�_�[�f�[�^�B
	bool m_isInited = false;		//�������ς݁H
};

const ShaderData shaderDatas[] = {

	{ L"mainDS"},
	{ L"mainHS"},
	{ L"mainPS"},
	{ L"mainVS"}
};