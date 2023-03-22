#pragma once
#include "Scene.h"
namespace MiniLord
{
	class ImGuiScene :public Scene
	{
	public:
		ImGuiScene(const std::string& sceneName): Scene(sceneName) {}

		~ImGuiScene() override = default;
		ImGuiScene(const ImGuiScene& other) = delete;
		ImGuiScene(ImGuiScene&& other) noexcept = delete;
		ImGuiScene& operator=(const ImGuiScene& other) = delete;
		ImGuiScene& operator=(ImGuiScene&& other) noexcept = delete;

		void Initialize() override;
	};
	
}

