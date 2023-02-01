cbuffer WorldTransform : register(b0)
{
    matrix c_world; // ワールド行列
}

cbuffer Camera : register(b1)
{
    matrix c_view; // ビュー行列
    matrix c_proj; // 射影行列
    float3 c_cameraPos; // カメラ座標
}

cbuffer Color : register(b2)
{
    float4 c_color; // 色
}

struct VSInput
{
    float4 pos : POSITION; // 座標
    float3 normal : NORMAL; // 法線
};

struct VSOutput
{
    float4 svpos : SV_POSITION; // システム用座標
    float4 worldpos : POSITION;
    float3 normal : NORMAL; // 法線
};