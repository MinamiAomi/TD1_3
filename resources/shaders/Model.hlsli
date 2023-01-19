cbuffer WorldTransform : register(b0)
{
    matrix c_world;       // ���[���h�s��
}

cbuffer Camera : register(b1)
{
    matrix c_view;        // �r���[�s��
    matrix  c_proj;       // �ˉe�s��
    float3 c_cameraPos;    // �J�������W
}

cbuffer Material : register(b2)
{
    float3 c_ambient : packoffset(c0); // �����i�A���r�G���g�j
    float3 c_diffuse : packoffset(c1); // �g�U���i�f�B�t���[�Y�j
    float c_shininess : packoffset(c1.w); // ����x
    float3 c_specular : packoffset(c2); // ���ʔ��ˌ��i�X�y�L�����[�j
    float c_alpha : packoffset(c2.w); // �����x�i�A���t�@�j
}

struct VSInput
{
    float4 pos : POSITION;      // ���W
    float3 normal : NORMAL;     // �@��
    float2 uv : TEXCOORD;          //�@uv���W
};

struct VSOutput
{
    float4 svpos : SV_POSITION; // �V�X�e���p���W
    float4 worldpos : POSITION;
    float3 normal : NORMAL;     // �@��
    float2 uv : TEXCOORD;       //�@uv���W
};