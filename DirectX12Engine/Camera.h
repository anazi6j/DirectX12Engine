#pragma once
#define NOMINMAX
#include <DirectXMath.h>
#include <d3dx12.h>
#include "CubeApp.h"

struct ShaderParameters;
class DX12EngineCore;
class Camera
{
public:
	Camera() {};
	
	
	Camera(const std::shared_ptr<DX12EngineCore> in_core, const DirectX::XMMATRIX& modelMat, ShaderParameters* ModelrendererShaderparam);
	//CubeApp::ShaderParameters shaderParams;
	
	CD3DX12_VIEWPORT m_viewport;
	CD3DX12_RECT m_rect;
	
	//void Update(const DirectX::XMMATRIX& modelMat);
	
	
	
	void Update(const DirectX::XMMATRIX& modelMat, ShaderParameters* ModelrendererShaderparam);
	void SetViewProj(const DirectX::XMMATRIX& ModelMat, ShaderParameters* ModelrendererShaderparam);
	void SetPosition(const DirectX::XMVECTOR& in_posvector);
	void SetRotation(const DirectX::XMVECTOR& in_rotvector);
	DirectX::XMVECTOR m_position;
	DirectX::XMVECTOR m_rotation;
	DirectX::XMVECTOR m_target;
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//�J�����𓮂���
	float x = 0;
	float y = 0;
	float z = 0;
	void Move(const DirectX::XMVECTOR& move)
	{
		m_position = DirectX::XMVectorAdd(m_position, move);
		m_target = DirectX::XMVectorAdd(m_target, move);

	}
	//�����_�𓮂���
	void MoveTarget(const DirectX::XMVECTOR& move)
	{
		m_target = DirectX::XMVectorAdd(m_target, move);

	}
	//���_�𓮂���
	void MovePosition(const DirectX::XMVECTOR& move)
	{
		m_position = DirectX::XMVectorAdd(m_position, move);

	}

};

