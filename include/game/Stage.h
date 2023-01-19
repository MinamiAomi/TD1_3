#pragma once
#include <vector>
#include <memory>
#include <string>

class Stage
{

private:
	static std::string s_stageDataFileName;	// ステージデータファイル名


private:
	unsigned int m_stageIndex = 0;	// ステージナンバー
	std::vector<std::unique_ptr<class Block>> m_blocks;	// 地面となるブロック
	std::unique_ptr<class MainCamera> m_camera;	// カメラ
	std::unique_ptr<class SnowBall> m_snowBall;	// カメラ

	std::unique_ptr<class TestObj> m_testObj;

public:
	Stage();
	~Stage();

	void Initalize(unsigned int stageIndex);
	void Update();
	void Draw();

	const std::vector<std::unique_ptr<class Block>>& GetBlockArray()const { return m_blocks; }
	unsigned int GetStageIndex() const { return m_stageIndex; }

private:
	void LoadData();
	void SaveData();
};

