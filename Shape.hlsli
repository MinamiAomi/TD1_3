cbuffer CommonConstBufferData : register(b0)
{
    matrix camera; // �J�������W�ϊ��s��
}

cbuffer ConstBufferData : register(b1)
{
    matrix world; // ���[���h���W�ϊ��s��
}

struct VSOutput
{
    float4 svpos : SV_Position;
    float4 color : COLOR;
};