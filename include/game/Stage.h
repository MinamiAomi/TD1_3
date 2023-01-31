#pragma once
#include <vector>
#include <memory>
#include <string>
#include "WorldTransform.h"
#include "json.hpp"

class Sprite;
class Block;
class Item;

class Stage
{

private:
	static std::string s_stageDataFileName;	// ステージデータファイル名

	static std::unique_ptr<nlohmann::json> s_stageData;

public:
	static void LoadJson();
	static void SaveJson();

private:
	unsigned int m_stageIndex = 0;	// ステージナンバー
	WorldTransform m_transform;
	std::vector<std::unique_ptr<Block>> m_blocks;	// 地面となるブロック
	std::vector<std::unique_ptr<Item>> m_items;	//	ゴール条件に必要なアイテム

	std::unique_ptr<Sprite> m_number;
	
	float m_width = {};
	float m_height = {};

	float m_angle = {};

public:
	Stage();
	~Stage();

	float angle() const { return m_angle; }

	void Initalize();
	void Update(const Vector2& player);
	void PreCollision();
	void Draw3D();
	void Draw2D();

	const std::vector<std::unique_ptr<class Block>>& blocks()const { return m_blocks; }
	unsigned int GetStageIndex() const { return m_stageIndex; }

private:
	void LoadStageData();
	void SaveStageData();	
};

