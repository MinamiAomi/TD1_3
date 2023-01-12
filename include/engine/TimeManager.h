#pragma once
#include <chrono>
#include <array>

class TimeManager
{

private:
	struct Timer
	{
		bool isUse = false;
		std::chrono::steady_clock::time_point start;
		float waitTime = 0.0f;
	};

private:
	// �^�C�}�[�̍ő吔
	static const int kTimerMaxCount = 10;

private:
	// �f���^�^�C��
	float m_deltaTime;
	// �O��̎���
	std::chrono::steady_clock::time_point m_preTime;
	// �^�C�}�[�̔z��
	std::array<Timer, kTimerMaxCount> m_timers;

public:
	static TimeManager* GetInstance();
	
	void Update();
	// �f���^�^�C��
	float deltaTime() const { return m_deltaTime; }

	// �^�C�}�[�𐶐�
	size_t CreateTimer(float waitTime_sec);
	// �^�C�}�[�����X�^�[�g����
	void ReStartTimer(size_t number);
	// �^�C�}�[���������
	void ReleaseTimer(size_t number);
	// �^�C�}�[���o�߂�����
	bool IsElapsedTimer(size_t number);

private:
	TimeManager();
	~TimeManager() = default;
	TimeManager(const TimeManager&) = delete;
	const TimeManager& operator=(const TimeManager&) = delete;
};

namespace Time 
{
	// �f���^�^�C��
	inline float deltaTime() { return TimeManager::GetInstance()->deltaTime(); }
	// �^�C�}�[�𐶐�
	inline size_t CreateTimer(float waitTime_sec) { return TimeManager::GetInstance()->CreateTimer(waitTime_sec); }
	// �^�C�}�[�����X�^�[�g����
	inline void ReStartTimer(size_t number) { return TimeManager::GetInstance()->ReStartTimer(number); }
	// �^�C�}�[���������
	inline void ReleaseTimer(size_t number) { return TimeManager::GetInstance()->ReleaseTimer(number); }
	// �^�C�}�[���o�߂�����
	inline bool IsElapsedTimer(size_t number) { return TimeManager::GetInstance()->IsElapsedTimer(number); }

}