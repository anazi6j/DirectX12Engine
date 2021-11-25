struct VSOutput
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD0;
};

cbuffer Material : register(b1)
{
   float3 Diffuse; //!< �g�U���ː����ł�.
    float4 Specular; //!< ���ʔ��ː����ł�.
    float3 ambient;
   
}

cbuffer Light : register(b2)
{
    float3 lightpos;
    float3 lightcolor;
}
Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(VSOutput In) : SV_TARGET
{
    float3 N = normalize(In.Nomal);
    float3 L = normalize(lightpos - In.Position);
    float diffuse = lightcolor * Diffuse * saturate(dot(L, N));
    float3 Lightreflect = normalize(reflect(lightcolor, N.xyz));
    float specular = pow(saturate(dot(Lightreflect, In.eyeray), Specular.a));
    //eyeray�́A�J��������̎����x�N�g��
    return In.Color*Diffuse + float4(specular, Specular.rgb, 1), float4((tex.Sample(samp, In.UV) * ambient), 1);
}