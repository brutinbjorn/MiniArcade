#include "MiniLordPCH.h"
#include "SoundSystem.h"

using namespace MiniLord;

SDLSoundSystem::SDLSoundSystem()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error" << Mix_GetError << std::endl;
	else
		std::cout << "SDL mix started" << std::endl;

	m_MusicUpdateJThread = std::jthread([this] {this->Update(); });
}

SDLSoundSystem::~SDLSoundSystem()
{
	std::cout << "sound system request stop \n" << std::endl;
	m_IsStopping = true;
	m_WorkAvailable.notify_one();

	m_MusicUpdateJThread.join();

	m_SoundQueue.clear();

	for (std::map<int, Mix_Music*>::iterator songIter = m_Songs.begin(); songIter != m_Songs.end(); songIter++)
	{
		Mix_FreeMusic(songIter->second);
	}

	for (std::map<int, Mix_Chunk*>::iterator effectIter = m_soundEffects.begin(); effectIter != m_soundEffects.end(); effectIter++)
	{
		Mix_FreeChunk(effectIter->second);
	}

	Mix_CloseAudio();
	Mix_Quit();

}

void SDLSoundSystem::PlaySound( int id, float volume)
{
	float clampedVol = std::clamp(volume, 0.f, 1.f);

	SoundStats newSound{ id,clampedVol,"No Name" };
	std::lock_guard mLock{ m_MutexSoundsQueueChanging }; // lock when accessing soundQueue
	m_SoundQueue.push_back(newSound);

	m_WorkAvailable.notify_one();
}

void SDLSoundSystem::PlaySoundEffect( int id, float volume)
{
	//RECONS no list to add soundeffects ???
	float clampedVol = std::clamp(volume, 0.f, 1.f);

	I_PlaySoundEffect(id, (clampedVol));
}

//TODO loaden zou op second thread moeten gebeuren
void SDLSoundSystem::LoadSound( int& id, const std::string& source)
{
	//TODO load should not happen here, but in the thread;
	//std::string fullpath = "../Data/sounds/";
	//fullpath.append(source);
	//Mix_Music* music = Mix_LoadMUS(fullpath.c_str());

	//if (music != nullptr)
	//{
	//	//m_currentAvailableSongID++;
	//	id = static_cast<int>(m_Songs.size());
	//	m_Songs[id] = music;
	//	std::cout << "music loaded at: " << id << std::endl;
	//}
	//else
	//	std::cout << "no music found at: " << fullpath << " error: " << Mix_GetError << std::endl;
	m_MutexSoundsQueueChanging.lock();
	id = static_cast<int>(m_SoundsPaths.size());
	m_MutexSoundsQueueChanging.unlock();

	std::lock_guard m_Lock{ m_mutexLoadQueueChanging };
	m_SoundsPaths.push({ id,source });
}


void SDLSoundSystem::LoadSoundEffect( int& id, const std::string& source)
{
	std::string fullpath = "../Data/sounds/";
	fullpath.append(source);

	
	Mix_Chunk* effect = Mix_LoadWAV(fullpath.c_str());
	if (effect != nullptr)
	{
		id = static_cast<int>(m_soundEffects.size());
		m_soundEffects[id] = effect;
		std::cout << "effect loaded at: " << id << std::endl;
	}
	else
		std::cout << "no effect found at: " << fullpath << " error: " << Mix_GetError << std::endl;
}



void SDLSoundSystem::Update()
{
	do // keep running until stop is triggered
	{
		bool HasAudio = false;
		SoundStats soundToPlay;
		std::unique_lock mlock{ m_MutexSoundsQueueChanging }; // lock when accessing SoundQueue
		if (!m_SoundQueue.empty() && 0 == Mix_PlayingMusic()) //loading stuff from the stack.
		{
			soundToPlay = m_SoundQueue.front();
			m_SoundQueue.pop_front();
			HasAudio = true;
		}
		mlock.unlock();

		if (HasAudio) // check if there are songs to play AND is the current music not playing?
		{
			if (!m_IsMuted)
			{
				I_playSound(soundToPlay.m_id, soundToPlay.m_volume);
			}
		}

		mlock.lock();
		if (m_SoundQueue.empty()) // if sound Queue is empty wait until you get message to do stuff
			m_WorkAvailable.wait(mlock);
		else
		{
			mlock.unlock();
		}

		//TODO add loading section.


	} while (!m_IsStopping);

	std::cout << "update sound ended" << std::endl;
}

//internal
void SDLSoundSystem::I_playSound( int songId, float volume)
{
	int ConvertedVolume = static_cast<int>(std::clamp(volume, 0.f, 1.f) * MIX_MAX_VOLUME);

	int channel = Mix_PlayMusic(m_Songs[songId], 1);
	if (channel == -1)
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
	Mix_Volume(channel, ConvertedVolume);
	std::cout << "playing music id: " << songId << "  on channel " << channel << std::endl;

}

//TODO denk niet dat playSoundEffect zo raar zit, wordt gewoon direct gecalled van de playSoundEffect???

//internal
void SDLSoundSystem::I_PlaySoundEffect( int effectId, float volume)
{
	int ConvertedVolume = static_cast<int>(std::clamp(volume, 0.f, 1.f) * MIX_MAX_VOLUME);

	Mix_VolumeChunk(m_soundEffects[effectId], ConvertedVolume);
	Mix_PlayChannel(-1, m_soundEffects[effectId], 0);
}

void SDLSoundSystem::I_LoadSound()
{
	m_mutexLoadQueueChanging.lock();
	auto thepair = m_SoundsPaths.front();
	m_SoundsPaths.pop();
	m_mutexLoadQueueChanging.unlock();

	std::string fullpath = "../Data/sounds/";
	Mix_Music* music = Mix_LoadMUS(fullpath.c_str());
	fullpath.append(thepair.second);

	if (music != nullptr)
	{
		//m_currentAvailableSongID++;
		//id = static_cast<int>(m_Songs.size());
		m_Songs[thepair.first] = music;
		std::cout << "music loaded at: " << thepair.first << std::endl;
	}
	else
		std::cout << "no music found at: " << fullpath << " error: " << Mix_GetError << std::endl;


}

