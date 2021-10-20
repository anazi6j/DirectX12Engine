#include "Model.h"
#include <atlstr.h>
#include "MathUtility.h"
#include <assert.h>
using namespace MathUtility;
void Model::Init(const std::string pFile)
{
	Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_PreTransformVertices;
	flag |= aiProcess_CalcTangentSpace;
	flag |= aiProcess_GenSmoothNormals;
	flag |= aiProcess_GenUVCoords;
	flag |= aiProcess_RemoveRedundantMaterials;
	flag |= aiProcess_OptimizeMeshes;

	m_pScene = importer.ReadFile(pFile,
		flag);

	//メッシュのメモリを確保
	meshes.clear();
	meshes.resize(m_pScene->mNumMeshes);

	//メッシュデータを変換
	for (size_t i = 0; i < meshes.size(); ++i)
	{
		const auto pMesh = m_pScene->mMeshes[i];
		ProcessAssimpMesh(pMesh);
	}

}

// for: NumChildren







void Model::ProcessAssimpMesh(const aiMesh* p_mesh)
{


	
         ConvertToaiMatrix4x4toXMFLOAT4x4(m_pScene->mRootNode->mTransformation, modelmat);

	
		 DirectX::XMMATRIX xmModelMat = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&modelmat));
		

		for (unsigned int v = 0; v < p_mesh->mNumVertices; v++)
		{
			Vertex vertex = {};
			vertex.Pos.x = p_mesh->mVertices[v].x;
			vertex.Pos.y = p_mesh->mVertices[v].y;
			vertex.Pos.z = p_mesh->mVertices[v].z;

			if (p_mesh->mTextureCoords[0])
			{
				vertex.UV.x = p_mesh->mTextureCoords[0][v].x;
				vertex.UV.y = p_mesh->mTextureCoords[0][v].y;
			}

			
			if (p_mesh->mNormals)
			{
				vertex.Normal.x = p_mesh->mNormals[v].x;
				vertex.Normal.y = p_mesh->mNormals[v].y;
				vertex.Normal.z = p_mesh->mNormals[v].z;
			}
			/*
			 if (srcMesh->mTangents)
			{
				dstTangent[0] = srcMesh->mTangents[v].x;
				dstTangent[1] = srcMesh->mTangents[v].y;
				dstTangent[2] = srcMesh->mTangents[v].z;
			}

			  if (srcMesh->mBitangents)
			{
				dstBitangent[0] = srcMesh->mBitangents[v].x;
				dstBitangent[1] = srcMesh->mBitangents[v].y;
				dstBitangent[2] = srcMesh->mBitangents[v].z;
			}
			*/

			
			vertices.push_back(vertex);
			unsigned int tempindex = 0;
			for (unsigned int f = 0; f < p_mesh->mNumFaces; f++)
			{
				assert(p_mesh->mFaces[f].mNumIndices == 3);

				aiFace face = p_mesh->mFaces[f];
				for (UINT j = 0; j < face.mNumIndices; j++) {
					indices.push_back(tempindex);

				}
			}




		}
		//こちらはソース元、paimeshの多重ループになっているかを調べる。
	/*
	UINT Nummesh = pScene->mNumMeshes;
	const aiMesh* submesh = nullptr;
	aiBone* pBone = nullptr;
	UINT nBoneIndex = 0;
	UINT NumBones = 0;
	for (UINT i = 0; i < Nummesh; i++)
	{
		submesh = pScene->mMeshes[i];

		for (UINT j = 0; j < submesh->mNumBones; j++)
		{
			nBoneIndex = 0;
			pBone = submesh->mBones[j];

			nBoneIndex = NumBones++;

			//XMMATRIX
			bones[NumBones].boneoffsetmatrix = DirectX::XMMatrixTranspose(pBone->mOffsetMatrix);
			//aiMatrix4x4から、XMMATRIXへの変換関数を作成しておく
		}

		for (UINT k = 0; k < pBone->mNumWeights; k++)
		{
			mesh.mBone.VertexID[k] = pBone->mWeights[k].mVertexId;
			mesh.mBone.Weights.weight[k] = pBone->mWeights[k].mWeight;
			
		}
	}
	*/
}

bool FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nposIndex)
{
	nposIndex = 0;
	if (pNodeAnim->mNumPositionKeys > 0)
	{
		return false;
	}

	for (UINT i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++)
	{
		if ((AnimationTime >= (FLOAT)pNodeAnim->mPositionKeys[i].mTime)
			&& (AnimationTime < (FLOAT)pNodeAnim->mPositionKeys[i + 1].mTime))
		{
			nposIndex = i;
			return true;
		}
	}
	return false;
}


bool FindRotation(FLOAT AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nRotationIndex)
{
	nRotationIndex = 0;
	if (!(pNodeAnim->mNumRotationKeys > 0))
	{
		return false;
	}

	for (UINT i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
	{
		// ﾑﾏｸ�ﾅﾐｶﾏﾊｱｼ腟ickﾊﾇｷ�ﾔﾚﾁｽｸ�ｹﾘｼ・｡ﾖｮｼ・
		if ((AnimationTime >= (FLOAT)pNodeAnim->mRotationKeys[i].mTime)
			&& (AnimationTime < (FLOAT)pNodeAnim->mRotationKeys[i + 1].mTime))
		{
			nRotationIndex = i;
			return true;
		}
	}

	return false;
}


BOOL FindScaling(FLOAT AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nScalingIndex)
{
	nScalingIndex = 0;
	if (!(pNodeAnim->mNumScalingKeys > 0))
	{
		return false;
	}

	for (UINT i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++)
	{
		// ﾑﾏｸ�ﾅﾐｶﾏﾊｱｼ腟ickﾊﾇｷ�ﾔﾚﾁｽｸ�ｹﾘｼ・｡ﾖｮｼ・
		if ((AnimationTime >= (FLOAT)pNodeAnim->mScalingKeys[i].mTime)
			&& (AnimationTime < (FLOAT)pNodeAnim->mScalingKeys[i + 1].mTime))
		{
			nScalingIndex = i;
			return true;
		}
	}

	return false;
}
void CalcInterpolatedPosition(DirectX::XMVECTOR& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1)
	{
		mxOut = DirectX::XMVectorSet(pNodeAnim->mPositionKeys[0].mValue.x, pNodeAnim->mPositionKeys[0].mValue.y, pNodeAnim->mPositionKeys[0].mValue.z, 0);
		return;
	}

	UINT PositionIndex = 0;
	if (!FindPosition(AnimationTime, pNodeAnim, PositionIndex))
	{
		mxOut = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		return;
	}

	UINT NextPositionIndex = (PositionIndex + 1);

	assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
	float deltatime = static_cast<float>(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
	float Factor = (AnimationTime - static_cast<float>(pNodeAnim->mPositionKeys[PositionIndex].mTime)) / deltatime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	VectorLerp(mxOut, pNodeAnim->mPositionKeys[PositionIndex].mValue
		, pNodeAnim->mPositionKeys[NextPositionIndex].mValue, Factor);
}

void CalcInterpolatedRotation(DirectX::XMVECTOR& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1)
	{
		QuaternionEqual(mxOut, pNodeAnim->mRotationKeys[0].mValue);
		return;
	}

	UINT RotationIndex = 0;
	if (!FindRotation(AnimationTime, pNodeAnim, RotationIndex))
	{
		mxOut = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		return;
	}
	UINT NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
	float Deltatime = static_cast<float>(pNodeAnim->mRotationKeys[NextRotationIndex].mTime
		- pNodeAnim->mRotationKeys[RotationIndex].mTime);
	float Factor = AnimationTime - static_cast<float>(pNodeAnim->mRotationKeys[RotationIndex].mTime) / Deltatime;
	assert(Factor >= 0.0f && Factor <= 1.0f);


	DirectX::XMQuaternionNormalize(mxOut);
}

void CalcInterpolatedScaling(DirectX::XMVECTOR& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1)
	{
		VectorEqual(mxOut, pNodeAnim->mScalingKeys[0].mValue);
		return;
	}



	UINT ScalingIndex = 0;
	if (!FindScaling(AnimationTime, pNodeAnim, ScalingIndex))
	{// ｵｱﾇｰﾊｱｼ葷｡ﾃｻﾓﾐﾋ�ｷﾅｱ莉ｻ｣ｬｷｵｻﾘ 1.0ﾋ�ｷﾅｱﾈﾀ�
		mxOut = DirectX::XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
		return;
	}

	UINT NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
	float DeltaTime = (FLOAT)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
	float Factor = (AnimationTime - (FLOAT)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);

	VectorLerp(mxOut
		, pNodeAnim->mScalingKeys[ScalingIndex].mValue
		, pNodeAnim->mScalingKeys[NextScalingIndex].mValue
		, Factor);


}

void Model::ProcessBoneNode(const aiAnimation* p_animation, const aiScene* pScene, const aiNode* node
	, float AnimationTime,const DirectX::XMMATRIX& ParentNodeTransform)
	{
		
	
	DirectX::XMFLOAT4X4 NodeTransformation = {};
	   
	   ConvertToaiMatrix4x4toXMFLOAT4x4(node->mTransformation, NodeTransformation);

		CStringA strNodeName(node->mName.data);
		const aiNodeAnim* pNodeAnim =SearchNodeAnim(p_animation, strNodeName);
		//名前がstrNodeNameと一致するアニメーションが、p_Animationのチャンネルの中から存在していたら
		//それをpNodeAnimの内容とする。
		
		DirectX::XMMATRIX NodeTransformationXM = DirectX::XMLoadFloat4x4(&NodeTransformation);

		if (pNodeAnim)
		{
			DirectX::XMVECTOR tempcalclatedScaling = {};
			CalcInterpolatedScaling(tempcalclatedScaling, AnimationTime, pNodeAnim);
			DirectX::XMMATRIX calclatedScaling = DirectX::XMMatrixScalingFromVector(tempcalclatedScaling);
			
			
			DirectX::XMVECTOR tempcalclatedRotation = {};
			CalcInterpolatedRotation(tempcalclatedRotation, AnimationTime, pNodeAnim);
			DirectX::XMMATRIX calclatedRotation = DirectX::XMMatrixScalingFromVector(tempcalclatedRotation);

			DirectX::XMVECTOR tempcalclatedTranslation = {};
			CalcInterpolatedPosition(tempcalclatedTranslation, AnimationTime, pNodeAnim);
			DirectX::XMMATRIX calclatedTranslation = DirectX::XMMatrixScalingFromVector(tempcalclatedTranslation);


			//pnodeanimのデータを利用し、
			//スケーリング、回転、平行移動の計算を行う
			//計算した上記三つの結果(calclated~)を、NodeTransformationに代入する。
			NodeTransformationXM = calclatedScaling * calclatedRotation * calclatedTranslation;
			// OpenGL｣ｺTranslationM* RotationM* ScalingM;
		}
		UINT nBoneIndex = 0;
		//親ノード空間へと座標変換
		DirectX::XMMATRIX GlobalTransformation =DirectX::XMMatrixMultiply(NodeTransformationXM, ParentNodeTransform);
		//GPUに渡すボーン行列に座標変換
		bones[nBoneIndex].transformmatrixforGPU = bones[nBoneIndex].boneoffsetmatrix * GlobalTransformation *
			modelmat;
		for (UINT i = 0; i < node->mNumChildren; i++) {
			ProcessBoneNode(p_animation, pScene, node->mChildren[i], AnimationTime, GlobalTransformation);
		}
		
	}
__inline VOID VectorLerp(DirectX::XMVECTOR& vOut, aiVector3D& aivStart, aiVector3D& aivEnd, FLOAT t)
{
	DirectX::XMVECTOR vStart = DirectX::XMVectorSet(aivStart.x, aivStart.y, aivStart.z, 0);
	DirectX::XMVECTOR vEnd = DirectX::XMVectorSet(aivEnd.x, aivEnd.y, aivEnd.z, 0);
	vOut = DirectX::XMVectorLerp(vStart, vEnd, t);
}

__inline const DirectX::XMVECTOR& QuaternionEqual(DirectX::XMVECTOR& qDX, const aiQuaternion& qAI)
{
	qDX = DirectX::XMVectorSet(qAI.x, qAI.y, qAI.z, qAI.w);
	return qDX;
}

__inline VOID QuaternionSlerp(DirectX::XMVECTOR& vOut, aiQuaternion& qStart, aiQuaternion& qEnd, FLOAT t)
{
	//DirectXMathﾋﾄﾔｪﾊ�ｺｯﾊ�ﾊｹﾓﾃXMVECTOR 4 - vectorﾀｴｱ�貔ﾋﾄﾔｪﾊ�｣ｬﾆ葷ﾐX｡｢YｺﾍZｷﾖﾁｿﾊﾇﾊｸﾁｿｲｿｷﾖ｣ｬWｷﾖﾁｿﾊﾇｱ・ｿｲｿｷﾖ｡｣

	DirectX::XMVECTOR qdxStart;
	DirectX::XMVECTOR qdxEnd;
	QuaternionEqual(qdxStart, qStart);
	QuaternionEqual(qdxEnd, qEnd);

	vOut = DirectX::XMQuaternionSlerp(qdxStart, qdxEnd, t);
}

__inline const DirectX::XMVECTOR& VectorEqual(DirectX::XMVECTOR& vDX, const aiVector3D& vAI)
{
	vDX = DirectX::XMVectorSet(vAI.x, vAI.y, vAI.z, 0);
	return vDX;
}
