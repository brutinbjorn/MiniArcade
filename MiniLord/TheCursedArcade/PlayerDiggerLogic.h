#pragma once
#include <BaseComponent.h>
#include <PhysicsEvents.h>
#include <Subject.h>
#include "Grid.h"
#include "OverlapEvent.h"

namespace MiniLord
{
	class Scene;

	class PlayerDiggerLogic : public BaseComponent, public Interface::OverlapEvent
	{
	public:
		PlayerDiggerLogic(Grid* grideToInfluence,Scene* currentScene);
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
		void FireProjectile();

		void SavePlayerDirection(glm::fvec2 dirAndSpeed) { m_ShotDirection = dirAndSpeed; };
		Subject& GetSubject(){ return m_subject;} ;
		
		void GotHit();

		bool ColliderEventBegin(GameObject* otherObject, glm::fvec2 otherMovement) override;
		void OverlapEventBegin(GameObject* OtherObject) override;

	private:
		glm::fvec2 m_ShotDirection {1.f,0.f};
		Subject m_subject = Subject{};
		Grid* m_pGrid;
		Scene* m_pScene;

		float m_BulletTime = 10.f;
		float m_BulletTimeDelta = 0.f;
	};
}


