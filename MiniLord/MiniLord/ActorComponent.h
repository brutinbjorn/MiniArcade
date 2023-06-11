#pragma once
#include "BaseComponent.h"
#include "OverlapComp.h"

namespace MiniLord
{
	class ActorComponent final: public BaseComponent
	{
	public:
		ActorComponent() = default;
		~ActorComponent() override = default;
		ActorComponent(const ActorComponent& other) = delete;
		ActorComponent(ActorComponent&& other) noexcept = delete;
		ActorComponent& operator=(const ActorComponent& other) = delete;
		ActorComponent& operator=(ActorComponent&& other) noexcept = delete;

		void Initialize() override ;
		void FixedUpdate(const float) override {};
		void Update(const float) override{};
		void LateUpdate(const float) override;
		void Render() const override {};
		void GuiRender() override {};
		void AddVelocity(glm::fvec2& move) { m_Velocity += move; };
		void OverWriteVelocity(glm::fvec2 newVelocity) { m_Velocity = newVelocity; };


		//might get overwritten in the init, as actor wil try to look if the parent has one.
		void SetOverlapComponent(OverlapComp* overlapComp) { m_HasOverLap = overlapComp; };

	private:
		glm::fvec2 m_Velocity;
		OverlapComp* m_HasOverLap = nullptr;

	};
}

