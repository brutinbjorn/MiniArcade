#pragma once
#include "b2_body.h"
#include "BaseComponent.h"

namespace MiniLord
{


	//Adds collision to the object that triggers the OnCollisionEnter in other components of the parent.
	class CollisionComponent :public BaseComponent
	{
	public:
		CollisionComponent(glm::fvec2 cubeSize): m_bodySize(cubeSize){};
		~CollisionComponent() override = default;
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;

		void Initialize() override;
		void FixedUpdate(const float) override;;
		void Update(const float) override ;
		void LateUpdate(const float) override {};
		void Render() const override ;
		void GuiRender() override {};

		void OnCollisionEnter(CollisionComponent* other);
		//bool Recieve(BaseComponent*, const std::string&) override {};

		b2Body* GetBody() { return m_pBody; };
	private:
		//b2Body m_Body;
		glm::fvec2 m_bodySize;
		b2BodyDef m_groundBodyDef;
		b2Body* m_pBody =nullptr;
		//groundBodyDef.position.Set(0.0f, -10.0f);
	};
	
}

