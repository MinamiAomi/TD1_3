#include "Stage.h"
#include <fstream>
#include <string>
#include <iomanip> // std::setw�̂���
#include <cassert>
#include "Block.h"
#include "MainCamera.h"
#include "json.hpp"
#include "Input.h"
#include "TestObj.h"
#include "SnowBall.h"
#include "Game.h"

std::string Stage::s_stageDataFileName = "Stage.json";

Stage::Stage()
{

}

Stage::~Stage()
{
}

void Stage::Initalize(unsigned int stageIndex)
{
	m_stageIndex = stageIndex;
	m_camera.reset(new MainCamera);
	m_camera->Initalize();
	m_snowBall.reset(new SnowBall);
	m_snowBall->Initalize();
	LoadData();
	m_testObj.reset(new TestObj);
	m_testObj->Initalize(m_camera->GetCameraTransform());
	
}

void Stage::Update()
{
	auto input = Input::GetInstance();

	m_camera->Update();
	
	m_snowBall->Update();

	if (Game::IsDebugMode()) {
		if (input->IsMouseTrigger(kMouseButtonLeft)) {
			//m_blocks.emplace_back();
		}


	}
	
	for (auto& it : m_blocks) {
		it->Update();
	}

	m_snowBall->SetCollider();
	for (auto& it : m_blocks) {
		it->SetCollider();
	}
		
	m_snowBall->Collision(m_blocks);
	
	if (Game::IsDebugMode()) {
		m_testObj->Update();
	}

}

void Stage::Draw()
{
	for (auto& it : m_blocks) {
		it->Draw(m_camera->GetCameraTransform());
	}
	m_snowBall->Draw(m_camera->GetCameraTransform());
	if (Game::IsDebugMode()) {
		m_testObj->Draw(m_camera->GetCameraTransform());
	}
}

void Stage::LoadData()
{
	// json�̃f�[�^���i�[�����
	nlohmann::json jsonObj;
	// �ǂݍ��ݐ�p�t�@�C�����J��
	std::ifstream jsonInFile(s_stageDataFileName);
	assert(jsonInFile);
	if (jsonInFile) {
		// �ǂݍ���
		jsonInFile >> jsonObj;
		// z���̕���ǂݍ���
		float zwidth = jsonObj.at("zwidth");
		// �X�e�[�W�z��̃X�e�[�W�ԍ��v�f���擾
		const auto& data = jsonObj.at("stage").at(m_stageIndex);
		// �u���b�N�v�f���擾
		for (const auto& block : data.at("blocks")) {
			auto addBlock = std::make_unique<Block>();
			addBlock->Initalize(block, zwidth, m_camera->GetWorldCenterTransform());
			m_blocks.push_back(std::move(addBlock));
		}
	}
	else {
		BlockJsonData emptyBlock = {};
		jsonObj = {
			{ "zwidth", 10 },
			{ "stage", {
				{
					{ "blocks",
						emptyBlock
					}
				}

				}
			}
		};

		std::ofstream jsonOutFile(s_stageDataFileName);
		// Json�N���X�ɏ�������(setw�ŃC���f���g�������w��)
		jsonOutFile << std::setw(4) << jsonObj << std::endl;
	}

}

void Stage::SaveData()
{

	nlohmann::json jsonObj;
	
	// �ǂݍ��ݐ�p�t�@�C�����J��
	std::ifstream jsonInFile(s_stageDataFileName);
	assert(jsonInFile);
	// �ǂݍ���
	jsonInFile >> jsonObj;

	auto& curStageJson = jsonObj.at("stage").at(m_stageIndex);
	
	nlohmann::json blocks;
	for (const auto& it : m_blocks) {
		blocks.push_back(static_cast<BlockJsonData>(*it));
	}
	curStageJson.at("blocks") = blocks;

	std::ofstream jsonOutFile(s_stageDataFileName);
	// Json�N���X�ɏ�������(setw�ŃC���f���g�������w��)
	jsonOutFile << std::setw(4) << jsonObj << std::endl;


}
