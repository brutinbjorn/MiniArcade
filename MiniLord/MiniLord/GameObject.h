#pragma once
#include "Transform.h"
#include "BaseComponent.h"


namespace MiniLord
{
	class GameObject final
	{
	public:
		//construct/destruct
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		//update/render logic.
		void Initialize() const;
		void FixedUpdate(const float ft);
		void Update(const float dt);
		void LateUpdate(const float lt);
		void Render() const;

		void SetPosition(float x, float y);
		Transform* GetTransform() { return &m_Transform; };

		//component logic.
		template <typename T>
		T* GetComponent();
		void AddComponent(BaseComponent* ToAdd);
		void RemoveComponent(BaseComponent* ToRemove);

		void SetMarkForDeletion(bool mark = true) { m_MarkForDeletion = mark; }
		bool IsMarkedForDeletion() const { return  m_MarkForDeletion; }

		//REDUNDENT send function, cleanup, change or remove.
		//bool Send(BaseComponent* sender, const std::string& msg);
		//bool Recieve(BaseComponent* sender, const std::string& msg);

	private:

		std::vector<BaseComponent*> m_pComponents = std::vector<BaseComponent*>();

		//parent/child relationship
		std::shared_ptr<GameObject> m_pParentGameObject = nullptr;
		std::vector<std::shared_ptr<GameObject>> m_pChildObjects = std::vector<std::shared_ptr<GameObject>>();

		Transform m_Transform;
		bool m_MarkForDeletion = false;
	};

	template <typename T>
	T* GameObject::GetComponent()
	{
		for (BaseComponent* bc : m_pComponents)
		{
			if (dynamic_cast<T*>(bc))
				return dynamic_cast<T*>(bc);
		}
		return nullptr;
	};
	
}
