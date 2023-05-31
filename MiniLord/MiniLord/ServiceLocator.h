#pragma once
#include "MiniLordPCH.h"
#include "SoundSystem.h"

namespace MiniLord
{
	class ServiceLocator
	{
		static SoundSystem* ss_instance;
		static NullSoundSystem default_ss;
	public:
		static SoundSystem& GetSoundSystem() { return *ss_instance; };

		static void RegisterSoundSystem(SoundSystem* ss)
		{
			if (ss_instance != nullptr && ss_instance != &default_ss)
				delete ss_instance;
			ss_instance = ss == nullptr ? &default_ss : ss;
		}

		static void CleanUpSoundSystem()
		{
			delete ss_instance;
		}

	};

}
