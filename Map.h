#pragma once
#include <memory>
#include <vector>
#include "MathUtility.h"
#include "WorldTransform.h"
#include "ClearItem.h"

#include "json.hpp"

class WorldTransform;
class CameraTransform;

class Map
{
private:
	static std::string s_stageDataFileName;	// ステージデータファイル名

	static std::unique_ptr<nlohmann::json> s_stageData;

public:
	static void LoadJson();
	static void SaveJson();

private:
	std::vector<std::unique_ptr<class Wall>> m_walls;
	std::array<std::unique_ptr<ClearItem>, ClearItem::kTypeCount> m_items;
	std::unique_ptr<class Goal> m_goal;
	WorldTransform* m_world = nullptr;
	CameraTransform* m_camera = nullptr;

	WorldTransform m_test;

	int m_selectIndex = 0;

	Vector3 m_mouse;



public:
	Map();
	~Map();

	std::vector<std::unique_ptr<Wall>>& walls() { return m_walls; }
	std::array<std::unique_ptr<ClearItem>, ClearItem::kTypeCount>& items() { return m_items; }
	std::unique_ptr<Goal>& goal() { return m_goal; };

	void Initalize(WorldTransform* world, CameraTransform* camera);
	void Update();
	void Draw();

private:
	void LoadMapData();
	void SaveMapData();
	void Edit();
};

