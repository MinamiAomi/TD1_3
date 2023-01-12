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
	// タイマーの最大数
	static const int kTimerMaxCount = 10;

private:
	// デルタタイム
	float m_deltaTime;
	// 前回の時間
	std::chrono::steady_clock::time_point m_preTime;
	// タイマーの配列
	std::array<Timer, kTimerMaxCount> m_timers;

public:
	static TimeManager* GetInstance();
	
	void Update();
	// デルタタイム
	float deltaTime() const { return m_deltaTime; }

	// タイマーを生成
	size_t CreateTimer(float waitTime_sec);
	// タイマーをリスタートする
	void ReStartTimer(size_t number);
	// タイマーを解放する
	void ReleaseTimer(size_t number);
	// タイマーが経過したか
	bool IsElapsedTimer(size_t number);

private:
	TimeManager();
	~TimeManager() = default;
	TimeManager(const TimeManager&) = delete;
	const TimeManager& operator=(const TimeManager&) = delete;
};

namespace Time 
{
	// デルタタイム
	inline float deltaTime() { return TimeManager::GetInstance()->deltaTime(); }
	// タイマーを生成
	inline size_t CreateTimer(float waitTime_sec) { return TimeManager::GetInstance()->CreateTimer(waitTime_sec); }
	// タイマーをリスタートする
	inline void ReStartTimer(size_t number) { return TimeManager::GetInstance()->ReStartTimer(number); }
	// タイマーを解放する
	inline void ReleaseTimer(size_t number) { return TimeManager::GetInstance()->ReleaseTimer(number); }
	// タイマーが経過したか
	inline bool IsElapsedTimer(size_t number) { return TimeManager::GetInstance()->IsElapsedTimer(number); }

}