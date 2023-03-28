#pragma once
#include "ActorComponent.h"
#include "BaseComponent.h"

namespace MiniLord
{
	class PlayerComponent :
	    public BaseComponent
	{
	public:
		PlayerComponent(ActorComponent* ActorToControl):m_pActorComp(ActorToControl) {};
		~PlayerComponent()override = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

		void Initialize() override;
		void FixedUpdate(const float) override;
		void Update(const float) override;
		void LateUpdate(const float) override;
		void Render() const override;
		void GuiRender() override;

	private:
		ActorComponent* m_pActorComp = nullptr;
	};
}

