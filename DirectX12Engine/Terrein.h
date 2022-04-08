#pragma once
#include <vector>
#include "SimpleMath.h"
#include <memory>
#include "VertexTypes.h"
#include "ImguiCore.h"
#include "TerreinEditor.h"
struct grayscale
{
	unsigned int width=0;
	unsigned int height=0;
	std::vector<std::vector<unsigned int>> m_grayscale;
	unsigned int s_grayscale[12][12];
};

struct Normalmap
{
	unsigned int width;
	unsigned int height;
	std::shared_ptr< DirectX::SimpleMath::Vector3> normalmap;
};

class Terrein
{
	Terrein();
	grayscale heightmap;
	std::vector<DirectX::VertexPositionNormalTexture> vertices;
	//�n�C�g�}�b�v���쐬�A�܂��̓��[�h�A�ǂ��炩
	//���s��
	void Preparegrayscale();
	//�m�[�}���}�b�v���쐬�A�܂��̓��[�h�A�ǂ��炩��
	//�s��
	//GUI������Addline�Ɏg����Imvec2�C���X�^���X�z��̑S�Ă̗v�f���g���Agrayscale�̗v�f�ɑ������
	void SetGrayScale();

	void PrepareNormalMap(const grayscale* heightMap, Normalmap* normalMap, unsigned int width,unsigned int height)
		;
	void Preparepatch();

	std::unique_ptr<TerreinEditor> m_terreineditor;
};

