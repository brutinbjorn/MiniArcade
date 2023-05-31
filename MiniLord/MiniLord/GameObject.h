#pragma once
#include "Transform.h"
#include "BaseComponent.h"


namespace MiniLord
{
	class GameObject final
	{
	public:
		//construct/destruct
		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		//update/render logic.
		void Initialize() const;
		void FixedUpdate(const float ft);
		//TODO choose where to calculate the transform of this object (world/relative + parent child. use a dirty flag.).
		void Update(const float dt);
		void LateUpdate(const float lt);
		void Render() const;
		void GuiRender() const;

		Transform& GetTransform()
		{
			return *m_Transform;
		}; 
		//TODO expand on this cuz this is only the transform relative to the world. no consistent parent/child or world/Relative position
		//local transform is primary data, world transform is derived, same as textComp, path is primary data, texture is derived.
		//primary data is the temp file, secundairy data is the saved file. (.0w0.)


		//component logic.
		template <typename T>
		T* GetComponent();
		void AddComponent(BaseComponent* ToAdd);
		void RemoveComponent(BaseComponent* ToRemove);

		void SetMarkForDeletion(bool mark = true) { m_MarkForDeletion = mark; }
		bool IsMarkedForDeletion() const { return  m_MarkForDeletion; }

		void SetParentGameObject(GameObject* newParent,bool worldPositionStays);

		GameObject* GetParentGameObject() const { return m_pParentGameObject; };
		std::vector<std::unique_ptr<GameObject>>& GetChildren() { return m_pChildObjects; };
		//void SetParentObject(GameObject* newParent, bool keepWorldPosition);
		//void AddChildObject(GameObject* newChildObject, bool keepWorldPosition);
		//void RemoveChildObject(GameObject* childObject);

		//REDUNDENT send function, cleanup, change or remove.
		//bool Send(BaseComponent* sender, const std::string& msg);
		//bool Recieve(BaseComponent* sender, const std::string& msg);

	private:

		std::vector<BaseComponent*> m_pComponents = {};

		//parent/child relationship
		GameObject* m_pParentGameObject = nullptr;
		std::vector<std::unique_ptr<GameObject>> m_pChildObjects = {};

		Transform* m_Transform;
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
