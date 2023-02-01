cbuffer WorldTransform : register(b0)
{
    matrix c_world; // ���[���h�s��
}

cbuffer Camera : register(b1)
{
    matrix c_view; // �r���[�s��
    matrix c_proj; // �ˉe�s��
    float3 c_cameraPos; // �J�������W
}

cbuffer Color : register(b2)
{
    float4 c_color; // �F
}

struct VSInput
{
    float4 pos : POSITION; // ���W
    float3 normal : NORMAL; // �@��
};

struct VSOutput
{
    float4 svpos : SV_POSITION; // �V�X�e���p���W
    float4 worldpos : POSITION;
    float3 normal : NORMAL; // �@��
};