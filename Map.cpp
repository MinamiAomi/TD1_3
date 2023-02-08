#include "Map.h"
#include "Wall.h"
#include "Input.h"
#include "CameraTransform.h"


#include "Resources.h"
#include "Model.h"
#include "Collision2D.h"
#include "Goal.h"

#include <fstream>
#include <string>
#include <iomanip> // std::setwのため
#include <cassert>

std::string Map::s_stageDataFileName = "resources/text/Stage.json";
std::unique_ptr<nlohmann::json> Map::s_stageData = std::make_unique<nlohmann::json>();

void Map::LoadJson()
{
	std::ifstream jsonInFile(s_stageDataFileName);
	assert(jsonInFile);
	// 読み込み
	jsonInFile >> *s_stageData;
}

void Map::SaveJson()
{
	std::ofstream jsonOutFile(s_stageDataFileName);
	// Jsonクラスに書き込み(setwでインデント数幅を指定)
	jsonOutFile << std::setw(4) << *s_stageData << std::endl;
}

Map::Map()
{
	m_test.Initalize();
}

Map::~Map()
{
	SaveMapData();
}

void Map::Initalize(WorldTransform* world, CameraTransform* camera)
{
	m_world = world;
	m_camera = camera;
	
	
	m_selectIndex = 4;

	LoadMapData();

	//auto tmp = std::make_unique<Wall>();
	//tmp->parent(world);
	//tmp->Initalize({ 5,5 }, 1, 1.7, Math::ToRadians(45.0f));
	//m_walls.emplace_back(std::move(tmp));
}

void Map::Update()
{
#ifdef _DEBUG
	Edit();
#endif // _DEBUG

	
	for (auto& it : m_walls) {
		it->Update();
	}
	for (auto& it : m_items) {
		if (it->isGet() == false) {
			it->Update();
		}
	}
	m_goal->Update();
}

void Map::Draw()
{
	for (auto& it : m_walls) {
		it->Draw();
	}
	for (auto& it : m_items) {
		if (it->isGet() == false) {
			it->Draw(m_camera);
		}
	}
	m_goal->Draw(m_camera);

	//m_test.UpdateMatrix();
	//Resource::GetInstance()->GetModel().bucket->Draw(&m_test, m_camera);
}

void Map::LoadMapData()
{
	m_walls.clear();
	for (int i = 0; i < 4; i++) {
		m_walls.emplace_back(std::make_unique<Wall>());
		m_walls[i]->parent(m_world);
	}
	m_walls[0]->Initalize({ -10.0f,   0.0f }, 0.0f,1.0f, 11.0f);
	m_walls[1]->Initalize({ 10.0f,   0.0f }, 0.0f,1.0f, 11.0f);
	m_walls[2]->Initalize({ 0.0f,  10.0f }, 0.0f,9.0f, 1.0f);
	m_walls[3]->Initalize({ 0.0f,	-10.0f }, 0.0f,9.0f, 1.0f);

	// ステージ配列のステージ番号要素を取得
	const auto& wallData = s_stageData->at("walls");

	// ブロック要素を取得
	for (const auto& data : wallData) {
		auto addWall = std::make_unique<Wall>();
		addWall->parent(m_world);
		float centerX = {};
		float centerY = {};
		float rotate = {};
		float width = {};
		float height = {};
		data.at(0).get_to(centerX);
		data.at(1).get_to(centerY);
		data.at(2).get_to(rotate);
		data.at(3).get_to(width);
		data.at(4).get_to(height);
		addWall->Initalize({ centerX,centerY }, rotate, width, height);
		m_walls.push_back(std::move(addWall));
	}

	auto iter = m_items.begin();
	for (const auto& item : s_stageData->at("items")) {
		auto addItem = std::make_unique<ClearItem>();
		ClearItem::Type type = ClearItem::kTypeCarrot;
		if (item.at("name") == "bucket") {
			type = ClearItem::kTypeBucket;
		}
		Vector2 pos;
		float radius = {};
		item.at("pos").at(0).get_to(pos.x);
		item.at("pos").at(1).get_to(pos.y);
		item.at("scale").get_to(radius);
		addItem->parent(m_world);
		addItem->Initalize(type, pos, radius);
		*iter = std::move(addItem);
		iter++;
	}

	m_goal = std::make_unique<Goal>();
	m_goal->parent(m_world);
	Vector2  pos;
	s_stageData->at("goal").at("pos").at(0).get_to(pos.x);
	s_stageData->at("goal").at("pos").at(1).get_to(pos.y);
	m_goal->Initalize(pos);


	//for (const auto& item : data.at("items")) {
	//	std::unique_ptr<Item> tmp;
	//	if (item.at("name") == "carrot") {
	//		tmp = std::make_unique<CarrotItem>();
	//	}
	//	else if (item.at("name") == "bucket") {
	//		tmp = std::make_unique<BucketItem>();
	//	}
	//	else if (item.at("name") == "eye") {
	//		tmp = std::make_unique<EyeItem>();
	//	}
	//	if (tmp) {
	//		tmp->position(Vector3(item.at("pos").at(0), item.at("pos").at(1), 0.0f));
	//		tmp->scale(Vector3(item.at("scale")));
	//		tmp->parent(&m_transform);
	//		tmp->Initalize();
	//		m_items.push_back(std::move(tmp));
	//	}
	//}

	//std::unique_ptr<Goal> tmpInstance;
	//tmpInstance = std::make_unique<Goal>();
	//tmpInstance->position({ data.at("goal").at("pos").at(0), data.at("goal").at("pos").at(1) });
	//tmpInstance->rotate(data.at("goal").at("rot"));
	//tmpInstance->parent(&m_transform);
	//tmpInstance->Initalize();
	//m_goal = std::move(tmpInstance);
}

void Map::SaveMapData()
{
	// ステージ配列のステージ番号要素を取得
	auto& wallData = s_stageData->at("walls");
	wallData.clear();
	// 追加するデータ
	nlohmann::json tmpJson;
	auto wall = m_walls.begin() + 4; // 初めの4つは枠なので保存しない
	for (; wall != m_walls.end(); wall++) {
		nlohmann::json w = { (*wall)->center().x, (*wall)->center().y, (*wall)->angle(), (*wall)->width(), (*wall)->height() };
		tmpJson.emplace_back(w);
	}
	wallData = tmpJson;

	SaveJson();
}

void Map::Edit()
{
	auto input = Input::GetInstance();

	Vector2 mouse2D = input->GetMousePosition();

	Matrix44 vpInv = Matrix44::CreateViewport(0, 0, 1280, 720).Inverse();
	Matrix44 pInv = m_camera->projMat.Inverse();
	Matrix44 vInv = m_camera->viewMat.Inverse();

	Matrix44 invMat = vpInv * pInv * vInv;

	Vector3 mouseFar = Matrix44::FromScreenVector({ mouse2D,1.0f }, invMat);
	Vector3 mouseNear = Matrix44::FromScreenVector({ mouse2D,0.0f }, invMat);

	Vector3 mouseRay = mouseFar - mouseNear;

	Vector3 wallNormal = Vector3::UnitY;

	float dot1 = Dot(Vector3::Zero - mouseNear, wallNormal);
	float dot2 = Dot(mouseFar - mouseNear, wallNormal);

	m_mouse = mouseNear + dot1 / dot2 * mouseRay;
	m_mouse.y = 2.0f;
	m_test.position = m_mouse;


	if (input->IsMouseTrigger(kMouseButtonLeft)) {


		Collider2D::Circle mouse;
		mouse.center = m_mouse.xz();
		mouse.radius = 0.5f;
		Vector2 x;

		int i = 4;
		for (; i < m_walls.size(); i++) {
			if (Collision2D::Hit_Circle_OBB(mouse, m_walls[i]->collider(), x)) {
				m_selectIndex = i;
				break;
			}
		}

	}


	if (m_selectIndex < m_walls.size()) {
		if (input->IsMousePressed(kMouseButtonRight)) {
			m_walls[m_selectIndex]->Pos(m_mouse.xz());
		}

		if (input->IsKeyPressed(DIK_E)) {
			m_walls[m_selectIndex]->IncAngle(Math::ToRadians(-1));
		}
		if (input->IsKeyPressed(DIK_Q)) {
			m_walls[m_selectIndex]->IncAngle(Math::ToRadians(1));
		}
		if (input->IsKeyPressed(DIK_X)) {
			m_walls[m_selectIndex]->IncWidth(0.1f);
		}
		if (input->IsKeyPressed(DIK_Z) && m_walls[m_selectIndex]->width() > 0.1f) {
			m_walls[m_selectIndex]->IncWidth(-0.1f);
		}
		if (input->IsKeyPressed(DIK_D)) {
			m_walls[m_selectIndex]->IncHeight(0.1f);
		}
		if (input->IsKeyPressed(DIK_C) && m_walls[m_selectIndex]->height() > 0.1f) {
			m_walls[m_selectIndex]->IncHeight(-0.1f);
		}
	}

	if (input->IsKeyPressed(DIK_LCONTROL) && input->IsKeyTrigger(DIK_S)) {
		SaveMapData();
	}
}
