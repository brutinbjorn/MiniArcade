 #pragma once
#include "MiniLordPCH.h"

#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <SDL_mixer.h>

namespace MiniLord
{
	struct SoundStats
	{
		int m_id = -1;
		float m_volume = 1.f;
		std::string m_filename = "NONE";
	};

	class SoundSystem // PURE VIRTUAL
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void PlaySound( int id, float volume) = 0;
		virtual void PlaySoundEffect( int id, float volume) = 0;
		virtual void LoadSound( int& id, const std::string& source) = 0;
		virtual void LoadSoundEffect( int& id, const std::string& source) = 0;
	};

	class NullSoundSystem final : public SoundSystem 
	{
	public:
		~NullSoundSystem() override = default;
		void PlaySound( int, float) override {}
		void PlaySoundEffect( int, float) override {};
		void LoadSound( int&, const std::string&) override {};
		void LoadSoundEffect( int&, const std::string&) override {};

	};


#ifdef USE_SDLMIXER2
	class SDLSoundSystem : public  SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;

		void PlaySound( int id, float volume) override;
		void PlaySoundEffect( int id, float volume) override;
		void LoadSound( int& id, const std::string& source) override;
		void LoadSoundEffect( int& id, const std::string& source) override;
		//void UnloadSound( int id);

	private:
		void Update();
		void I_playSound(int songId, float volume);
		void I_PlaySoundEffect( int effectId, float volume);
		void I_LoadSound();

		//squeue
		std::list<SoundStats> m_SoundQueue;

		static int m_currentAvailableSongID;
		std::map<int, Mix_Music*> m_Songs;
		static int m_currentAvailableEffectID;
		std::map<int, Mix_Chunk*> m_soundEffects;


		//thread
		std::atomic_bool m_IsMuted = false;
		std::atomic_bool m_PlayNextSong = false;
		std::atomic_bool m_IsStopping = false;

		// Music Update
		std::jthread m_MusicUpdateJThread;
		std::mutex m_MutexSoundsQueueChanging;
		std::condition_variable m_WorkAvailable;

		// Loading Update
		std::mutex m_mutexLoadQueueChanging;
		std::queue<std::pair<int,std::string>> m_SoundsPaths;
		
	};


#endif
}
