#include "TimeManager.h"
#include <cassert>

TimeManager* TimeManager::GetInstance()
{
	static TimeManager instance;
	return &instance;
}

void TimeManager::Update()
{
	// 現在の時間を取得
	auto nowTime = std::chrono::steady_clock::now();
	// 経過時間を計算
	std::chrono::duration<float> elapsedTime = nowTime - m_preTime;
	m_deltaTime = elapsedTime.count();

	m_preTime = std::chrono::steady_clock::now();
}

size_t TimeManager::CreateTimer(float waitTime_sec)
{
	size_t result = 0;
	// 使われていないタイマーを探す
	while (result < kTimerMaxCount)
	{
		// 見つけたらループを抜ける
		if (m_timers[result].isUse == false) {
			break;
		}
		result++;
	}
	// 見つからなかった
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