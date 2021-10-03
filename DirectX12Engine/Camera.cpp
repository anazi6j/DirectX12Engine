/*!
* @brief	�J����
*/

#include "Camera.h"


Camera::Camera(CD3DX12_VIEWPORT&  in_viewport, CD3DX12_RECT& in_scissorRect)
{
	m_viewport = in_viewport;
	m_rect = in_scissorRect;
	m_position = DirectX::XMVectorSet(0.0f, 3.0f, -5.0f, 0.0f);
	m_target = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	SetViewProj();
}
void Camera::Update()
{
	
}


void Camera::SetViewProj()
{
	// �e�s��̃Z�b�g.
	
	DirectX::XMStoreFloat4x4(&shaderParams.mtxWorld, DirectX::XMMatrixRotationAxis(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(45.0f)));
	/*
	auto mtxView = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(0.0f, 3.0f, -5.0f, 0.0f),//position
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),//target
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)//up
	);
	*/

	
	auto mtxView = DirectX::XMMatrixLookAtLH(
		m_position,//position
		m_target,//target
		up//up
	);
	
	auto mtxProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), m_viewport.Width / m_viewport.Height, 0.1f, 100.0f);
	DirectX::XMStoreFloat4x4(&shaderParams.mtxView, DirectX::XMMatrixTranspose(mtxView));
	DirectX::XMStoreFloat4x4(&shaderParams.mtxProj, DirectX::XMMatrixTranspose(mtxProj));


}

void Camera::SetPosition(const DirectX::XMVECTOR& in_posvector)
{
	m_position = DirectX::XMVectorSet(in_posvector.m128_f32[0], in_posvector.m128_f32[1], in_posvector.m128_f32[2],0.0f);
}

void Camera::SetRotation(const DirectX::XMVECTOR& in_rotvector)
{
	m_rotation = DirectX::XMVectorSet(in_rotvector.m128_f32[0], in_rotvector.m128_f32[1], in_rotvector.m128_f32[2], 1.0f);
		
}

