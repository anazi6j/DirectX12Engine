#include "Animator.h"

//Tick����
//���㕡���̃��f���𓮂����ۂ�for�����g���i����Ⴛ�����j
void Animator::CalculateBoneAnimation(const aiScene* pScene, const aiNode* pNode)
{
	/*void ProcessBoneNode(const aiAnimation * p_animation,
	const aiScene* pScene, 
		const aiNode* node,
		const DirectX::XMMATRIX& ParentNodeTransform);
		*/
	const aiAnimation* pAnimation = m_model.m_pScene->mAnimations[m_model.mcurrentAnimIndex];
	DirectX::XMMATRIX Identity = DirectX::XMMatrixIdentity();
	m_model.ProcessBoneNode(pAnimation, m_model.m_pScene, m_model.m_pScene->mRootNode, Identity);
}
