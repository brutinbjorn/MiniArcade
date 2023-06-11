#pragma once
#include "BagState.h"
#include "BaseComponent.h"
#include "OverLapEvent.h"

#include "Grid.h"
#include "RenderComponent.h"
#include "Subject.h"

namespace MiniLord
{


	class BagLogic: public BaseComponent, public Interface::OverlapEvent
	{
	public:
		BagLogic(Grid* grid,glm::ivec2 gridPos,glm::fvec2 sizeOfCell, RenderComponent* bag,RenderComponent* gold, float fallSpeed = 100.f);

		~BagLogic() override;
		BagLogic(const BagLogic& other) = delete;
		BagLogic(BagLogic&& other) noexcept = delete;
		BagLogic& operator=(const BagLogic& other) = delete;
		BagLogic& operator=(BagLogic&& other) noexcept = delete;

		void Initialize() override;
		void FixedUpdate(const float) override{};
		void Update(const float) override;
		void LateUpdate(const float) override {};
		void Render() const override{};

		Grid* GetGrid() { return m_pGrid; }

		glm::ivec2 GetPositionOnGrid() { return m_positionOnGrid; };
		void SetPositionOnGrid(glm::ivec2 pos) { m_positionOnGrid = pos; }

		void SetIsFalling(bool isFalling) { m_IsFalling = isFalling; }
		bool GetIsFalling() { return m_IsFalling; }

		void SetIsInmovable(bool isMovable) { m_IsInmovable = isMovable; }
		bool GetIsInmovable() { return m_IsInmovable; }

		float GetSpeed() { return m_speed; }

		void SwapToGoldSprite(bool useGoldSprite = true);
		bool GetIsGold() { return m_isGoldNow; };

		void OverlapEventBegin(GameObject* OtherObject) override;
		bool ColliderEventBegin(GameObject* otherObject, glm::fvec2 otherMovement) override;

		Subject& GetSubject() { return m_subject; };

	private:

		Subject m_subject;
		Grid* m_pGrid;
		glm::fvec2 m_sizeOfObjects;
		glm::ivec2 m_positionOnGrid;

		RenderComponent* m_BagSprite = nullptr;
		RenderComponent* m_GoldSprite = nullptr;

		bool m_isGoldNow = false;
		bool m_IsInmovable = true;
		bool m_IsFalling = false;

		float m_speed = 100.f; 

		BagState* m_state = nullptr;

	};
}

