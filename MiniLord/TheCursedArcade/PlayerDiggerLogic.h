#pragma once
#include <BaseComponent.h>
#include <PhysicsEvents.h>
#include <Subject.h>
#include "Grid.h"

namespace MiniLord
{
	
	class PlayerDiggerLogic : public BaseComponent, public Interface::PhysicsEvents
	{
	public:
		PlayerDiggerLogic(Grid* grideToInfluence);
		~PlayerDiggerLogic() override = default;
		PlayerDiggerLogic(const PlayerDiggerLogic& other) = delete;
		PlayerDiggerLogic(PlayerDiggerLogic&& other) noexcept = delete;
		PlayerDiggerLogic& operator=(const PlayerDiggerLogic& other) = delete;
		PlayerDiggerLogic& operator=(PlayerDiggerLogic&& other) noexcept = delete;

		void Initialize() override {};
		void FixedUpdate(const float) override{};
		void Update(const float) override;
		void LateUpdate(const float) override{};
		void Render() const override{};

		Subject& GetSubject(){ return m_subject;};
		
		void GotHit();
		void OnCollisionEnter(CollisionComponent* other) override;
	private:
		Subject m_subject = Subject{};
		Grid* m_pGrid;
	};
}


