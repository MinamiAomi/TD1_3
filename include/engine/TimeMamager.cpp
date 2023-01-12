#include "TimeManager.h"
#include <cassert>

TimeManager* TimeManager::GetInstance()
{
	static TimeManager instance;
	return &instance;
}

void TimeManager::Update()
{
	// ���݂̎��Ԃ��擾
	auto nowTime = std::chrono::steady_clock::now();
	// �o�ߎ��Ԃ��v�Z
	std::chrono::duration<float> elapsedTime = nowTime - m_preTime;
	m_deltaTime = elapsedTime.count();

	m_preTime = std::chrono::steady_clock::now();
}

size_t TimeManager::CreateTimer(float waitTime_sec)
{
	size_t result = 0;
	// �g���Ă��Ȃ��^�C�}�[��T��
	while (result < kTimerMaxCount)
	{
		// �������烋�[�v�𔲂���
		if (m_timers[result].isUse == false) {
			break;
		}
		result++;
	}
	// ������Ȃ�����
	assert(result < kTimerMaxCount);
	
	m_timers[result].isUse = true;
	m_timers[result].start = std::chrono::steady_clock::now();
	m_timers[result].waitTime = waitTime_sec;

	return result;
}

void TimeManager::ReStartTimer(size_t number)
{
	assert(number < kTimerMaxCount);
	assert(m_timers[number].isUse == true);
	m_timers[number].start = std::chrono::steady_clock::now();
}

void TimeManager::ReleaseTimer(size_t number)
{
	assert(number < kTimerMaxCount);
	m_timers[number].isUse = false;
	m_timers[number].start = std::chrono::steady_clock::now();
	m_timers[number].waitTime = 0.0f;
}

bool TimeManager::IsElapsedTimer(size_t number)
{
	assert(number < kTimerMaxCount);
	assert(m_timers[number].isUse == true);

	auto nowTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsedTime = nowTime - m_timers[number].start;

	if (m_timers[number].waitTime < elapsedTime.count()) {
		return true;
	}
	return false;
}

TimeManager::TimeManager() {
	m_preTime = std::chrono::steady_clock::now();
}