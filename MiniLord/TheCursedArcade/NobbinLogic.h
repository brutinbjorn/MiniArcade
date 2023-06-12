#pragma once
#include <BaseComponent.h>
#include <OverlapEvent.h>

#include "ActorComponent.h"
#include "CellLogic.h"
#include "Subject.h"

namespace MiniLord
{
	class RenderComponent;
	class CellLogic;
	class Grid;

	class NobbinLogic :
		public BaseComponent, public Interface::OverlapEvent
	{
	public:
		NobbinLogic(Grid* theGameGrid, RenderComponent* mainbodsprite, RenderComponent* HobbinSprite, ActorComponent* actor, float speed = 100.f, bool IsPLayerControlled = false);
		~NobbinLogic() override = default;
		NobbinLogic(const NobbinLogic& other) = delete;
		NobbinLogic(NobbinLogic&& other) noexcept = delete;
		NobbinLogic& operator=(const NobbinLogic& other) = delete;
		NobbinLogic& operator=(NobbinLogic&& other) noexcept = delete;

		bool ColliderEventBegin(GameObject* otherObject, glm::fvec2 otherMovement) override;
		void OverlapEventBegin(GameObject* OtherObject) override;

		void Initialize() override {};
		void FixedUpdate(const float) override{};
		void Update(const float) override;
		void LateUpdate(const float) override{};
		void Render() const override {};

		void GotHit();

		Subject& Getsubject()
		{
			return m_subject;
		};

	private:
		bool m_isPlayerControlled= false;

		Grid* m_grid = nullptr;
		Subject m_subject{};

		ActorComponent* m_pActor = nullptr;
		RenderComponent* m_pNobbinsprite = nullptr;
		RenderComponent* m_pHobbinSprite = nullptr;


		bool m_AteGold = false;

		glm::ivec2 m_lastdirectionGone{};
		glm::ivec2 m_LastCellPosition{};
		float m_speed = 100.f;

		CellLogic* m_formerCell = nullptr;
		CellLogic* m_currentCell = nullptr;
		GameObject* m_TargetCellToReach = nullptr;
		float m_MinDistanceToTarget = 1.5f;
	};

}
