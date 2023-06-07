#pragma once
#include "MiniLordPCH.h"

#include "Physics.h"
#include "SoundSystem.h"

namespace MiniLord
{
	class ServiceLocator
	{
		static SoundSystem* ss_instance;
		static NullSoundSystem default_ss;

		//static Physics* physics_instance;
		//static Physics default_physics;
	public:
		static SoundSystem& GetSoundSystem() { return *ss_instance; };

		//static Physics& GetPhysics() { return *physics_instance; };

		static void RegisterSoundSystem(SoundSystem* ss)
		{
			if (ss_instance != nullptr && ss_instance != &default_ss)
				delete ss_instance;
			ss_instance = ss == nullptr ? &default_ss : ss;
		}

		//static void RegisterPhysics(Physics* physics)
		//{
		//	if (physics_instance != nullptr && physics_instance != &default_physics)
		//		delete physics_instance;
		//	physics_instance = physics == nullptr ? &default_physics : physics;
		//}

		static void CleanUpServices()
		{
			delete ss_instance;
		//	delete physics_instance;
		}



	};

}
