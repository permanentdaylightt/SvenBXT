#ifdef CTIMER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CTimer.h
#else //CTIMER_H_RECURSE_GUARD

#define CTIMER_H_RECURSE_GUARD

#ifndef CTIMER_H_GUARD
#define CTIMER_H_GUARD
#pragma once

#ifdef __cplusplus

class CTimer
{
public:
	CTimer()
	{
		Init();
	}

	void Init()
	{
		ResetTimer();
	}

	void StartTimer()
	{
		m_bStarted = true;
		if (!m_bRunning)
		{
			m_startTime = std::chrono::steady_clock::now();
			m_bRunning = true;
		}
	}

	void StopTimer()
	{
		if (m_bRunning)
		{
			auto now = std::chrono::steady_clock::now();
			m_elapsedTime += std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();
			m_bRunning = false;
		}
	}

	void ResetTimer()
	{
		m_bRunning = false;
		m_elapsedTime = 0;
	}

	void SetTime(long long time)
	{
		m_elapsedTime = time;
	}

	
    void SyncTimer(long long serverTime, bool stop)
	{
		if (stop)
		{
			StopTimer();
			SetTime(serverTime);
		}
		else
		{
			if (m_bRunning)
			{
				auto now = std::chrono::steady_clock::now();
				long long currentElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count() + m_elapsedTime;
				long long adjustment = serverTime - currentElapsedTime;
				m_startTime += std::chrono::milliseconds(adjustment);
			}
			else
			{
				SetTime(serverTime);
				StartTimer();
			}
		}
	}

	long long GetTime() const
	{
		if (m_bRunning)
		{
			auto now = std::chrono::steady_clock::now();
			return m_elapsedTime + std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();
		}
		return m_elapsedTime;
	}

	int GetMilliseconds() const
	{
		return static_cast<int>(fmod(GetTime(), 1000.0));
	}

	int GetSeconds() const
	{
		double seconds = GetTime() / 1000.0;
		return static_cast<int>(fmod(seconds, 60.0));
	}

	int GetMinutes() const
	{
		double minutes = GetTime() / 60000.0;
		return static_cast<int>(fmod(minutes, 60.0));
	}

	int GetHours() const
	{
		double hours = GetTime() / 3600000.0;
		return static_cast<int>(fmod(hours, 24.0));
	}

	int GetDays() const
	{
		double days = GetTime() / 86400000.0;
		return static_cast<int>(days);
	}

	bool IsStopped() const
	{
		return m_bRunning ? false : true;
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
	long long m_elapsedTime; // elapsed time in milliseconds
	bool m_bRunning, m_bStarted;
};

#else //!__cplusplus
#error C++ compiler required to compile CTimer.h
#endif //__cplusplus

#endif //CTIMER_H_GUARD

#undef CTIMER_H_RECURSE_GUARD
#endif //CTIMER_H_RECURSE_GUARD