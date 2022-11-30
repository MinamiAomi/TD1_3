cbuffer ConstBufferData : register(b0)
{
    float4 color; // �F
    matrix transMat; // �ϊ��s��
}

struct VSOutput
{
    float4 svpos : SV_POSITION; // �V�X�e���p���_���W
    float2 uv : TEXCOORD;       // uv�l
};