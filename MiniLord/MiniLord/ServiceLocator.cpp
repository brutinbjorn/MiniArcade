#include "MiniLordPCH.h"
#include "ServiceLocator.h"

MiniLord::NullSoundSystem MiniLord::ServiceLocator::default_ss;
MiniLord::SoundSystem* MiniLord::ServiceLocator::ss_instance = &default_ss;

//MiniLord::Physics MiniLord::ServiceLocator::default_physics;
//MiniLord::Physics* MiniLord::ServiceLocator::physics_instance = &default_physics;