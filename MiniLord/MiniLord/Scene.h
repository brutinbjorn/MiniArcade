#pragma once
#include "SceneManager.h"

namespace MiniLord
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		//adds the gameobject to the scene, so it gets its updates,render, etc.
		void AddGameObject(const std::shared_ptr<GameObject>& object);

		//place the game objects you want to add to the scene here.
		void Initialize() {};

		//initailizes the gameobjects.
		void PostInitialize();
		//fixed update for objects.
		void FixedUpdate(const float ft);
		//update for objects.
		void Update(const float dt);
		//late update for objects.
		void LateUpdate(const float lt);
		//Render the objects.
		void Render() const;
		//Gui Render;
		void GuiRender() const;

		[[nodiscard]] bool IsActive() { return m_IsActive; } ;
		void SetActive(bool active = true) { m_IsActive = active; };

		std::string GetName() { return m_Name; };

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		explicit Scene(const std::string& name);

	protected:
		bool m_IsActive = true;
		bool m_RunCleanUp = false;
		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};
		std::vector <std::shared_ptr<GameObject>> m_ObjectsToDelete{};
		static unsigned int m_IdCounter;
	};
}

