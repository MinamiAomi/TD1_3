#include "Model.hlsli"

Texture2D<float4> t_texture : register(t0);
SamplerState s_sampler : register(s0);

struct directionLight
{
    float3 color;
    float3 direction;
};

float4 main(VSOutput input) : SV_TARGET
{
    directionLight light;
    light.color = float3(1.0f, 1.0f, 1.0f);
    light.direction = normalize(float3(0.0f, -1.0f, 0.0f));
    
    float3 ambientColor = float3(0.2f, 0.2f, 0.2f);
    // �e�N�X�`���̐F
    float4 textureColor = t_texture.Sample(s_sampler, input.uv);
    // �V�F�[�f�B���O�ɂ��F
    float4 shadeColor = float4(ambientColor * c_ambient, c_alpha);
    
    //// �g�U���ˌ� ��
    //// �s�N�Z���̖@���ƃ��C�g�̕����̓��ς��v�Z����
    float dot_light_normal = saturate(dot(-light.direction, input.normal));
    //// �g�U���ˌ�
    float3 diffuse = dot_light_normal * float3(1.0f, 1.0f, 1.0f);
    
    // ���ʔ��ˌ� ��
    // ���_���王�_�ւ̃x�N�g��
    float3 toEye = normalize(c_cameraPos - input.worldpos.xyz);
    // ���C�g�x�N�g���̖ʂƂ̔��˃x�N�g��
    float3 refVec = normalize(light.direction + 2 * dot_light_normal * input.normal);
    // ���˃x�N�g���Ǝ��_�ւ̃x�N�g���̓���
    float dot_refVec_toEye = saturate(dot(refVec, toEye));
   
    // ���ʔ��˂̋������i��
    dot_refVec_toEye = pow(dot_refVec_toEye, c_shininess);
    // ���ʔ��ˌ�
    float3 specular = dot_refVec_toEye * c_specular;
    
    shadeColor.rgb += (diffuse + specular) * light.color;
      
    return shadeColor * textureColor;
}