#pragma once
#include "BaseComponent.h"

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

		void FixedUpdate(const float) override {};
		void Initialize() override {};
		void LateUpdate(const float) override{};
		void Render() const override {};
		void Update(const float) override;
		void GuiRender() override {};
		void AddVelocity(glm::fvec2& move) { m_Velocity += move; };



	private:
		glm::fvec2 m_Velocity;//???


	};
}

