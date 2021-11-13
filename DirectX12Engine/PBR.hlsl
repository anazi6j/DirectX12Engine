/*!
 * @brief �f�B�Y�j�[�x�[�X�̕����x�[�X�V�F�[�_
 */
/*
 ///////////////////////////////////////////////////
 // �萔
 ///////////////////////////////////////////////////
static const int NUM_DIRECTIONAL_LIGHT = 4; // �f�B���N�V�������C�g�̖{��
static const float PI = 3.1415926f;         // ��

///////////////////////////////////////////////////
// �\����
///////////////////////////////////////////////////
// ���f���p�̒萔�o�b�t�@�[
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

// �f�B���N�V�������C�g
struct DirectionalLight
{
    float3 direction;   // ���C�g�̕���
    float4 color;       // ���C�g�̐F
};

// ���C�g�p�̒萔�o�b�t�@�[
cbuffer LightCb : register(b1)
{
    DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];
    float3 eyePos;          // �J�����̎��_
    float specPow;          // �X�y�L�����̍i��
    float3 ambientLight;    // ����
};

// ���_�V�F�[�_�[�ւ̓���
struct SVSIn
{
    float4 pos : POSITION;  // ���f���̒��_���W
    float3 normal : NORMAL; // �@��
    float3 tangent  : TANGENT;
    float3 biNormal : BINORMAL;
    float2 uv : TEXCOORD0;  // UV���W
};

// �s�N�Z���V�F�[�_�[�ւ̓���
struct SPSIn
{
    float4 pos : SV_POSITION;       // �X�N���[����Ԃł̃s�N�Z���̍��W
    float3 normal : NORMAL;         // �@��
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
    float2 uv : TEXCOORD0;          // uv���W
    float3 worldPos : TEXCOORD1;    // ���[���h��Ԃł̃s�N�Z���̍��W
};

///////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////

// �e��}�b�v�ɃA�N�Z�X���邽�߂̕ϐ���ǉ�
Texture2D<float4> g_albedo : register(t0);           // �A���x�h�}�b�v
Texture2D<float4> g_normalMap : register(t1);        // �@���}�b�v
Texture2D<float4> g_metallicSmoothMap : register(t2); // ���^���b�N�X���[�X�}�b�v�Br�Ƀ��^���b�N�Aa�ɃX���[�X

// �T���v���[�X�e�[�g
sampler g_sampler : register(s0);


float3 GetNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
    float3 binSpaceNormal = g_nornal.SampleLevel(g_sampler, uv, 0.0f).xyz;
    binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;
    
    float3 newNormal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y
        + normal * binSpaceNormal.z;
    
    return newNormal;
}

//�x�b�N�}�����z���v�Z����
float Beckmann(float m, float t)
{
    float t2 = t * t;
    float t4 = t * t * t * t;
    float m2 =m*m:
    float D = 1.0f / (4.0f * m2 + t4);
    D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
    return D;
}

//�t���l�����v�Z Schlick�ߎ����g�p
float SpcFresnel(float f0, float u)
{
    return f0 + (1 - f0) * pow(1 - u, 5);
}

//Cook-Torrance���f���̋��ʔ���

float CookTorranceSpecular(float3 L, float3 V, float3 N, float metalic)
{
    float microfacet = 0.76f;

    //�����x�𐂒����˂̎��̃t���l�����˗��Ƃ��Ĉ���
    //�����x�������قǃt���l�����Ђ͑傫���Ȃ�
    float t0 = metalic;

    //���C�g�Ɍ������x�N�g���Ǝ����Ɍ������x�N�g���̃n�[�t�x�N�g�������߂�
    float H = normalize(L + V);

    //�e��x�N�g�����ǂꂭ�炢���Ă��邩����ς𗘗p���ċ��߂�
    float NdotH = saturate(dot(N, H));
    float VdotH = saturate(dot(V, H));
    float NdotL = saturate(dot(N, L));
    float NdotV = saturate(dot(N, V));

    //D����Schlicj�ߎ���p���Čv�Z����
    float F = SpcFresnel(f0, VdotH);

    //G�������߂�
    float m = PI * NdotV * NdotH;

    //�����܂ŋ��߂��l�𗘗p���āACool-Torrance���f���̋��ʔ��˂����߂�
    return max(F * D * G / m, 0.0);
}

//�t���l�����˂��l�������g�U���˂��v�Z

//�t���l�����˂́A�������̂̕��ʂŔ��˂��錸���̂���

//����g�U���˂͌������̂̓����ɓ����āA�����������N�����āA�g�U���Ĕ��˂��Ă������̎��ł���B
//�܂�t���l�����˂��ア�Ƃ��ɂ́A�g�U���˂��傫���Ȃ�A�t���l�����˂������Ƃ��ɂ́A�g�U���˂��������Ȃ�

//N =�@��
//L �����Ɍ������x�N�g�� ���̕����Ƌt�����̃x�N�g��
//V �����Ɍ������x�N�g�� 
//�e���B0~1�͈̔�

float CalcDiffuseFromFresnel(float3 N, float3 L, float3 V)
{
    //step-1 �f�B�Y�j�[�x�[�X�̃t���l�����˂ɂ��g�U���˂�^�ʖڂɎ�������B
    //�����Ɍ������x�N�g���Ǝ����Ɍ������x�N�g���̃n�[�t�x�N�g�������߂�
    float3 H = normalize(L + V);

    //�e����0.5�ŌŒ�
    float roughness = 0.5f;

    float energyBias = lerp(0.0f, 0.5f, roughness);
    float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);

    //�����Ɍ������x�N�g���ƃn�[�t�x�N�g�����ǂꂾ�����Ă��邩����ςŋ��߂�
    float dotLH = saturate(dot(L, H));

    //�����Ɍ������x�N�g���ƃn�[�t�x�N�g��
    //���ƕ��s�ɓ��˂����Ƃ��̊g�U���˗ʂ����߂Ă���
    float Fd90 = energyBias + 2.0 * dotLH * dotLH * dotLH * roughness;

    //�@���Ǝ��_�Ɍ������x�N�g���𗘗p���Ċg�U���˗������߂�
    float fotNV = saturate(dot(N, V));
    float FL = (1 + (Fd90 - 1) * pow(1 - dotNL, 5));

    //�@���ƌ����ւ̕����Ɉˑ�����g�U���˗��ƁA�@���Ǝ��_�x�N�g���Ɉˑ�����g�U���˗�����Z���čŏI�I�Ȕ��˗������߂Ă���BPI
    //�ŏ��Z���Ă���̂͐��K�����s�����߁B
    return (FL * FV * energyFactor);
   
}

float4 PSMain(VSOutput psIn) :SV_Target0
{
    float3 normal = GetNormal(psIn.normal,psIn.tangent,psIn.biNormal,psIn.uv);

    //�A���x�h�J���[�A�X�y�L�����J���[,�����x�A���炩�����T���v�����O����
    //�A���x�h�J���[(�g�U���ˌ�)
    float4 specColor = albedoColor;
    //�����x
    float metalic = g_metalicSmoothMap.Sample(g_sampler, psIn.uv).r;

    //���炩��
    float metalic = g_metalicSmoothMap.Sample(g_sampler, psIn.uv).a;

    //���R�Ɍ������ĐL�т�x�N�g�����v�Z����
    float3 toEye = normalize(eyePos - psIn.worldPos);

    float lig = 0;
    for (int ligNo = 0; ligNo < NUM_DIRECTIONAL_LIGHT; ligNo++)
    {
        //�V���v���ȃf�B�Y�j�[�x�[�X�̊g�U���˂���������
        //�t���l�����˂��l�������g�U���˂��v�Z
        float fiffuseFromFresnel = CalcDiffuseFromFresnel(normal, -directionalLight[ligNo].direction, toEye);

        //���K��Lambert�g�U���˂����߂�
        float NdotL = saturate(dot(normal, -directionalLight[ligNo].direction));
        float3 lambertDiffuse = directionalLight[ligNo].color * NdotL / PI;

        //�ŏI�I�Ȋg�U���ˌ����v�Z����B
        float3 diffuse = albedoColor * diffuseFromFresnel * lambertDiffuse;

        //Cook-Torrance���f���𗘗p�������ʔ��˗����v�Z����
        //Cook-Torrance���f���̋��ʔ��˗����v�Z����
        float3 spec = CookTorranceSpecular(
            -directionLight[ligNo].direction, toEye, normal, smooth)
            * directionalLight[ligNo].color;

        //�����x��������΁A���ʔ��˂̓X�y�L�����J���[�A�Ⴏ��Δ�
        //�X�y�L�����J���[�̋��������ʔ��˗��Ƃ��Ĉ���
        spec *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, metalic);

    }

    //�����ɂ���グ
    lig += ambientLight * albedoColor;

    float4 finalColor = 1.0f;
    finalColor.xyz = lig;
    return finalColor;
}

*/