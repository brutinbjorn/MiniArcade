#pragma once
#include "Singleton.h"


namespace MiniLord
{
	class TimeManager :
		public Singleton<TimeManager>
	{
	public:
		void init();

		void start();
		void Update();

		uint32_t GetFPS() const { return m_FPS; };
		uint32_t GetFixedUpdatesToDo() { return m_FixedUpdatesToDo; };

		float GetDeltaTime() const { return m_DeltaTime; };
		float GetLagDelay() const { return m_lag; };
		float GetMsPerUpdate() const { return m_msPerUpdate; };
		bool ShouldDoFixedUpdateAndLowerLag();
		bool IsRunning() const { return m_IsRunning; };
		void PrintTime(bool DoPrint = true);
	private:
		friend class Singleton<TimeManager>;
		TimeManager() = default;

		std::chrono::high_resolution_clock m_HClock = std::chrono::high_resolution_clock();
		std::chrono::steady_clock::time_point m_currentTime;
		std::chrono::steady_clock::time_point m_lastTime;

		uint32_t m_FPS = 0;
		uint32_t m_FPSCount = 0;
		uint32_t m_FixedUpdatesToDo = 0;
		float m_lag = 0.f;
		float m_FPSTimer = 0.f;
		float m_TotalTime = 0.f;
		float m_msPerUpdate = 0.02f;
		float m_DeltaTime = 0.f;
		float m_ElapsedTime = 0.f;
		float m_PrintTimer = 0.f;

		int m_DesiredFPS = 120; // TODO implement this.
		bool m_IsRunning = false;
		bool m_PrintTimeConsole = false;
	};
}

