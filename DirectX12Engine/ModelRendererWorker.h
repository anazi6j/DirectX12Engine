#pragma once
#include <d3dx12.h>
class ModelRendererWorker
{
public:
	ModelRenderWorker();
	HRESULT CreateCommandQueue();
	//������ŃR�}���h�n�C���^�[�t�F�[�X���쐬����B

	void CreateCommandAllocators();
	void CreateCommandLists();
};

