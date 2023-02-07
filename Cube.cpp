#include "Cube.h"
#include "Meth.h"
#include "DirectXCommon.h"
#include "Model.h"

Cube* Cube::GetInstance()
{
    static Cube instance;
    return &instance;
}

void Cube::Draw(Material* material, WorldTransform* world, CameraTransform* camera)
{
	Model::Draw(m_meth.get(), material, world, camera);
}

void Cube::InternalInitalize()
{
	m_meth = Meth::Create();

	std::vector<Meth::Vertex> vertcies = {	// 前
			{ {	-1.0f, -1.0f,  -1.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f,1.0f} },	// 左下
			{ { -1.0f,  1.0f,  -1.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f,0.0f} },	// 左上
			{ {  1.0f, -1.0f,  -1.0f }, { 0.0f, 0.0f, 1.0f }, {1.0f,1.0f} },	// 右下
			{ {  1.0f,  1.0f,  -1.0f }, { 0.0f, 0.0f, 1.0f }, {1.0f,0.0f} },	// 右上
			// 後
			{ {	-1.0f, -1.0f,   1.0f }, { 0.0f, 0.0f, -1.0f }, {0.0f,1.0f} },	// 左下
			{ { -1.0f,  1.0f,   1.0f }, { 0.0f, 0.0f, -1.0f }, {0.0f,0.0f} },	// 左上
			{ {  1.0f, -1.0f,   1.0f }, { 0.0f, 0.0f, -1.0f }, {1.0f,1.0f} },	// 右下
			{ {  1.0f,  1.0f,   1.0f }, { 0.0f, 0.0f, -1.0f }, {1.0f,0.0f} },	// 右上
			// 左
			{ {	-1.0f, -1.0f,  -1.0f }, { -1.0f, 0.0f, 0.0f }, {0.0f,1.0f} },	// 左下
			{ { -1.0f, -1.0f,   1.0f }, { -1.0f, 0.0f, 0.0f }, {0.0f,0.0f} },	// 左上
			{ { -1.0f,  1.0f,  -1.0f }, { -1.0f, 0.0f, 0.0f }, {1.0f,1.0f} },	// 右下
			{ { -1.0f,  1.0f,   1.0f }, { -1.0f, 0.0f, 0.0f }, {1.0f,0.0f} },	// 右上
			// 右
			{ {	 1.0f, -1.0f,  -1.0f }, { 1.0f, 0.0f, 0.0f }, {0.0f,1.0f} },	// 左下
			{ {  1.0f, -1.0f,   1.0f }, { 1.0f, 0.0f, 0.0f }, {0.0f,0.0f} },	// 左上
			{ {  1.0f,  1.0f,  -1.0f }, { 1.0f, 0.0f, 0.0f }, {1.0f,1.0f} },	// 右下
			{ {  1.0f,  1.0f,   1.0f }, { 1.0f, 0.0f, 0.0f }, {1.0f,0.0f} },	// 右上
			// 上
			{ {	-1.0f,  1.0f,  -1.0f }, { 0.0f, 1.0f, 0.0f }, {0.0f,1.0f} },	// 左下
			{ {  1.0f,  1.0f,  -1.0f }, { 0.0f, 1.0f, 0.0f }, {0.0f,0.0f} },	// 左上
			{ { -1.0f,  1.0f,   1.0f }, { 0.0f, 1.0f, 0.0f }, {1.0f,1.0f} },	// 右下
			{ {  1.0f,  1.0f,   1.0f }, { 0.0f, 1.0f, 0.0f }, {1.0f,0.0f} },	// 右上
			// 下
			{ {	-1.0f, -1.0f,  -1.0f }, { 0.0f, -1.0f, 0.0f }, {0.0f,1.0f} },	// 左下
			{ {  1.0f, -1.0f,  -1.0f }, { 0.0f, -1.0f, 0.0f }, {0.0f,0.0f} },	// 左上
			{ { -1.0f, -1.0f,   1.0f }, { 0.0f, -1.0f, 0.0f }, {1.0f,1.0f} },	// 右下
			{ {  1.0f, -1.0f,   1.0f }, { 0.0f, -1.0f, 0.0f }, {1.0f,0.0f} },	// 右上
	};

	std::vector<uint16_t> indcies = {
		0, 1, 2,
		2, 1, 3,

		5, 4, 6,
		5, 6, 7,

		8, 9,10,
	   10, 9,11,

	   13,12,14,
	   13,14,15,

	   17,16,18,
	   17,18,19,

	   21,22,20,
	   22,21,23
	};

	m_meth->AddVertcies(vertcies);
	m_meth->AddIndcies(indcies);

	m_meth->CreateBuffer(DirectXCommon::GetInstance()->GetDevice());
}
