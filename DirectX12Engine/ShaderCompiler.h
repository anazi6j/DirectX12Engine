#pragma once

#include <wrl.h>
#include "Structures.h"
#include <dxcapi.h>
#include <Windows.h>
class ShaderCompiler
{
	IDxcBlob* GetCompiledDxcBlob() const
	{
		return m_dxcBlob;
	}
public:
	/// <summary>
	/// ���C�g���[�V���O�p�̃V�F�[�_�[�����[�h�B
	/// </summary>
	void LoadRaytracing(const wchar_t* filePath);
	/// <summary>
	/// �R���p�C���ς݃V�F�[�_�[�f�[�^���擾�B
	/// </summary>
	/// <returns></returns>
private:
	ID3DBlob* m_blob = nullptr;	//�R���p�C���ς݂̃V�F�[�_�[�f�[�^�B
	IDxcBlob* m_dxcBlob = nullptr;	//DXC�R���p�C�����g�p�����Ƃ��̃V�F�[�_�[�f�[�^�B
	bool m_isInited = false;		//�������ς݁H

};

