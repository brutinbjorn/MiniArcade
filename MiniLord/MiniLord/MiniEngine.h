#pragma once
//#include "MiniLordPCH.h"

namespace MiniLord
{
	class MiniEngine
	{
	public:
		void Initialize();
		void Cleanup();
		void run();

		virtual void LoadGame();
		void FixedUpdate(const float );
		void Update(const float );
		void LateUpdate(const float );

		void Render() const;
	private:
		static const int MsPerFrame = 8; //16 for 60 fps, 33 for 30 fps

	#ifdef USE_SDL2
		SDL_Window* m_Window{};
	#endif

	};
}

