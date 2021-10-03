	
#include "SimpleDeg.hlsli"
cbuffer DiretionLightCB :register(b1)
{
	float3 dirDirection; //���C�g�̕���
	float3 dirColor;	//���C�g�̃J���[
	float3 eyePos //���_�̈ʒu
		float3 ambientLight //�A���r�G���g���C�g

		float3 groundcolor;
	float3 skyColor;
	float3 groundNormal;
}

float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float4 normal);
float3 CalcLigFromDirectionLight(VSOutput in_PS);

Texture2D<float4> g_texture :register(t0);

sampler g_sampler :register(s0);
//�����o�[�g�g�U���ˌ����v�Z����
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
	//�s�N�Z���̖@���ƃ��C�g�̕����̓��ς��v�Z����
	float t = dot(normal, lightDirection) * -1.0f;

	//���ς̒l��0�ȏ�̒l�ɂ���

	t = max(0.0f, t);

	return lightColor * t;
}

//Phong���ʔ��ˌ��̌v�Z����

float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
	float3 regVec = reflect(lightDirection, normal);

	//�������������T�[�t�F�X���王�_�ɐL�т�x�N�g�������߂�
	float3 toEye = eyePos - worldPos;
	toEye = normalize(toEye);

	// ���ʔ��˂̋��������߂�
	float t = dot(refVec, toEye);

	// ���ʔ��˂̋�����0�ȏ�̐��l�ɂ���
	t = max(0.0f, t);

	// ���ʔ��˂̋������i��
	t = pow(t, 5.0f);

	// ���ʔ��ˌ������߂�
	return lightColor * t;
}

/// <summary>
/// �f�B���N�V�������C�g�ɂ�锽�ˌ����v�Z
/// </summary
/// <param name="psIn">�s�N�Z���V�F�[�_�[����̓��́B</param>
float3 CalcLigFromDirectionLight(VSOutput psIn)
{
	// �f�B���N�V�������C�g�ɂ��Lambert�g�U���ˌ����v�Z����
	float3 diffDirection = CalcLambertDiffuse(dirDirection, dirColor, psIn.normal);

	// �f�B���N�V�������C�g�ɂ��Phong���ʔ��ˌ����v�Z����
	float3 specDirection = CalcPhongSpecular(dirDirection, dirColor, psIn.worldPos, psIn.normal);
	return diffDirection + specDirection;
}