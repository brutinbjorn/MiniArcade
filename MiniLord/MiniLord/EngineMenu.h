#pragma once
#include "Scene.h"
namespace MiniLord
{
	class EngineMenu : public Scene
	{
	public:
		EngineMenu(std::string name) : Scene(name) {};

		~EngineMenu() override = default;
		EngineMenu(const EngineMenu& other) = delete;
		EngineMenu(EngineMenu&& other) noexcept = delete;
		EngineMenu& operator=(const EngineMenu& other) = delete;
		EngineMenu& operator=(EngineMenu&& other) noexcept = delete;

		void Initialize() override;
	};
}

