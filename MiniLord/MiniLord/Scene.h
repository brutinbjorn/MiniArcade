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
		virtual void Initialize() {};
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



		bool IsActive() { return m_IsActive; };
		bool SetActive(bool active = true) { m_IsActive = active; };

		std::string GetName() { return m_Name; };

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		explicit Scene(const std::string& name);

	protected:
		bool m_IsActive = false;
		bool m_RunCleanUp = false;
		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter;
	};
}

