#include "Stage.h"
#include <fstream>
#include <string>
#include <iomanip> // std::setwのため
#include <cassert>
#include "Block.h"
#include "MainCamera.h"

#include "Input.h"
#include "TestObj.h"
#include "SnowBall.h"
#include "Game.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Resource.h"

std::string Stage::s_stageDataFileName = "Stage.json";
std::unique_ptr<nlohmann::json> Stage::s_stageData = std::make_unique<nlohmann::json>();

void Stage::LoadJson()
{
	std::ifstream jsonInFile(s_stageDataFileName);
	assert(jsonInFile);
	// 読み込み
	jsonInFile >> *s_stageData;
}

void Stage::SaveJson()
{
	std::ofstream jsonOutFile(s_stageDataFileName);
	// Jsonクラスに書き込み(setwでインデント数幅を指定)
	jsonOutFile << std::setw(4) << *s_stageData << std::endl;
}

Stage::Stage()
{

}

Stage::~Stage()
{
}

void Stage::Initalize()
{
	m_stageIndex = 1;
	
	m_transform.position = Vector3::Zero;
	m_transform.rotate = Quaternion::Identity;
	m_transform.scale = { 1.0f,1.0f,1.0f };

	LoadStageData();

	m_number = std::make_unique<Sprite>(Resource::GetInstance()->GetImage().NumberImage, Vector2{ 0, 0 }, Vector2{ 50, 50 });

	m_angle = 0;
}

void Stage::Update(const Vector2& player)
{
	auto input = Input::GetInstance();

	float rot = 0.0f;
	constexpr float rotSpeed = Math::ToRadians(1.0f);

	// 反時計回り
	if (input->IsKeyPressed(DIK_Q) || input->IsPadButtonPressed(0, kPadButtonLeftShoulder)) {
		rot += rotSpeed;
	}
	// 時計回り
	if (input->IsKeyPressed(DIK_E) || input->IsPadButtonPressed(0, kPadButtonRightShoulder)) {
		rot += -rotSpeed;
	}
	m_angle += rot;
	Vector2 pos = m_transform.position.xy();
	pos = pos - player;
	pos = pos.Rotated(rot);
	pos = pos + player;
	m_transform.position.xy(pos);
	m_transform.rotate = Quaternion::CreateFromAngleAxis(rot, Vector3::UnitZ) * m_transform.rotate;
	
	for (auto& it : m_blocks) {
		it->Update();
	}

	m_transform.UpdateMatrix();
}

void Stage::PreCollision()
{
	m_transform.UpdateMatrix();
	for (auto& it : m_blocks) {
		it->PreCollision1(m_angle);
	}
}


void Stage::Draw3D()
{
	m_transform.UpdateMatrix();

	for (auto& it : m_blocks) {
		it->Draw();
	}

	m_number->SetTextureRect({ 32 * (float)m_stageIndex, 0 }, { 32,32 });
}

void Stage::Draw2D()
{
	Sprite::Draw(m_number.get(), SceneManager::GetInstance()->commonData().camera2D->GetTransformMatrix());
}


void Stage::LoadStageData()
{
	m_blocks.clear();
	// ステージ配列のステージ番号要素を取得
	const auto& data = s_stageData->at("stage").at(m_stageIndex);
	
	data.at("width").get_to(m_width);
	data.at("height").get_to(m_height);
	
	float w = 1.0f;

	// ステージ左辺ブロック
	auto left = std::make_unique<Block>();
	left->type(Block::kBlockTypeNone);
	left->center({ -m_width,0.0f });
	left->rotate(0.0f);
	left->width(w);
	left->height(m_height - w);
	left->parent(&m_transform);
	left->Initalize();
	m_blocks.push_back(std::move(left));
	
	// ステージ上辺ブロック
	auto top = std::make_unique<Block>();
	top->type(Block::kBlockTypeNone);
	top->center({ 0.0f,m_height });
	top->rotate(0.0f);
	top->width(m_width + w);
	top->height(w);
	top->parent(&m_transform);
	top->Initalize();
	m_blocks.push_back(std::move(top));

	// ステージ右辺ブロック
	auto right = std::make_unique<Block>();
	right->type(Block::kBlockTypeNone);
	right->center({ m_width,0.0f });
	right->rotate(0.0f);
	right->width(w);
	right->height(m_height - w);
	right->parent(&m_transform);
	right->Initalize();
	m_blocks.push_back(std::move(right));

	// ステージ上辺ブロック
	auto bottom = std::make_unique<Block>();
	bottom->type(Block::kBlockTypeNone);
	bottom->center({ 0.0f,-m_height});
	bottom->rotate(0.0f);
	bottom->width(m_width + w);
	bottom->height(w);
	bottom->parent(&m_transform);
	bottom->Initalize();
	m_blocks.push_back(std::move(bottom));

	// ブロック要素を取得
	for (const auto& block : data.at("blocks")) {
		auto addBlock = std::make_unique<Block>();
		int type = {};
		Vector2 center = {};
		float rotate = {};
		float width = {};
		float height = {};
		block.at(0).get_to(type);
		block.at(1).get_to(center.x);
		block.at(2).get_to(center.y);
		block.at(3).get_to(rotate);
		block.at(4).get_to(width);
		block.at(5).get_to(height);
		addBlock->type(type);
		addBlock->center(center);
		addBlock->rotate(rotate);
		addBlock->width(width);
		addBlock->height(height);
		addBlock->parent(&m_transform);
		addBlock->Initalize();
		m_blocks.push_back(std::move(addBlock));
	}

}

void Stage::SaveStageData()
{
	// ステージ配列のステージ番号要素を取得
	auto& data = s_stageData->at("stage").at(m_stageIndex);
	data.at("width") = m_width;
	data.at("height") = m_height;
	// 追加するデータ
	nlohmann::json tmpJson;
	auto block = m_blocks.begin() + 4; // 初めの4つは枠なので保存しない
	for (; block != m_blocks.end(); block++) {
		tmpJson.push_back({ {(*block)->type(),(*block)->center().x,(*block)->center().y,(*block)->rotate(),(*block)->width(),(*block)->height()} });
	}
	data.at("blcoks") = tmpJson;
}

