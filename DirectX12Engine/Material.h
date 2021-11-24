#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <string>
struct Material
{

	DirectX::XMFLOAT3   Diffuse;        //!< �g�U���ː����ł�.
	DirectX::XMFLOAT3   Specular;       //!< ���ʔ��ː����ł�.
	float               Alpha;          //!< ���ߐ����ł�.
	float               Shininess;      //!< ���ʔ��ˋ��x�ł�.
	std::wstring        DiffuseMap;     //!< �f�B�t���[�Y�}�b�v�t�@�C���p�X�ł�.
	std::wstring        SpecularMap;    //!< �X�y�L�����[�}�b�v�t�@�C���p�X�ł�.
	std::wstring        ShininessMap;   //!< �V���C�l�X�}�b�v�t�@�C���p�X�ł�.
	std::wstring        NormalMap;      //!< �@���}�b�v�t�@�C���p�X�ł�.

};

