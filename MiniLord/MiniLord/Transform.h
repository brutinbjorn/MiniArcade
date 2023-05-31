#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace MiniLord
{
	//class TransformGameObject;
	class Transform : public BaseComponent
	{
	public:
		//RECONS move the entire transform into the gameobject? prevents copies from transforms, if it is a entire seperate object it can be copied, but needs the link to the game object
		//Transform(const GameObject* relatedGameObject) : m_parent(relatedGameObject){};
		Transform();

		//get current world position
		//const glm::fvec3& GetRelativePosition() const { return m_Position; }
		//const glm::ivec3& GetWorldPosition() const { return { }; };
		[[nodiscard]] const glm::fvec3& GetLocalPosition() const { return m_LocalPosition; };
		[[nodiscard]] const glm::fvec3& GetLocalRotation() const { return m_LocalRotation; };
		[[nodiscard]] const glm::fvec3& GetLocalScale() const { return m_LocalScale; }

		const glm::fvec3& GetWorldPosition();
		const glm::fvec3& GetWorldRotation();
		const glm::fvec3& GetWorldScale();

		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::fvec3& pos);

		void SetRotation(const glm::fvec3& newRotation);
		void SetRotation(float XRotation, float YRotation, float ZRotation);

		void SetScale(const glm::fvec3& newScale);
		void SetScale(float XScale, float YScale, float ZScale);

		// add too current position.
		void Translate(float x, float y, float z);
		void Translate(const glm::fvec3& Translate);

		void SetDirty();


	private:
		//const GameObject* m_parent = nullptr;
		void UpdateWorld();
		bool m_IsDirty = false;

		glm::fvec3 m_LocalPosition;
		glm::fvec3 m_LocalRotation;
		glm::fvec3 m_LocalScale;

		glm::fvec3 m_WorldPosition;
		glm::fvec3 m_WorldRotation;
		glm::fvec3 m_WorldScale;

		// Inherited via BaseComponent
		virtual void Initialize() override {};
		virtual void FixedUpdate(const float) override {};
		virtual void Update(const float) override {};
		virtual void LateUpdate(const float) override {};
		virtual void Render() const override {};
	};
}

