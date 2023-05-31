#pragma once
#include "Scene.h"

namespace MiniLord
{
	namespace SceneFactory
	{
		std::shared_ptr<Scene> DefaultDAEScene(const std::string& name = "defaultScene");

		std::shared_ptr<Scene> OrbitingGameObjects(const std::string& name = "OrbitingObjects");

		std::shared_ptr<Scene> MovingGameObjects(const std::string& name = "movingGameObjects");

		std::shared_ptr<Scene> ObserverTest(const std::string& name = "ObserverTest");

		std::shared_ptr<Scene> GuiSceneTest(const std::string& name = "ImGuiScene");

		std::shared_ptr<Scene> ButtonScene(const std::string& name = "ButtonTest");

	};
	
}

