#pragma once
#include "BaseComponent.h"
#include "SquareComponent.h"

namespace MiniLord
{
	class OverlapComp :public BaseComponent
	{
	public:
		OverlapComp(SDL_Rect sizeOfBox);
		~OverlapComp() override;
		OverlapComp(const OverlapComp& other) = delete;
		OverlapComp(OverlapComp&& other) noexcept = delete;
		OverlapComp& operator=(const OverlapComp& other) = delete;
		OverlapComp& operator=(OverlapComp&& other) noexcept = delete;

		void OnOverlapEvent(OverlapComp* other);
		bool OnColliderEvent(OverlapComp* other,glm::fvec2 directionOtherMoves);

		void SetOverlapState(bool IsOverLapping) { m_IsOverLapping = IsOverLapping; };
		bool GetOverlapState() const { return m_IsOverLapping; };
		SDL_Rect GetOverlapSquareInWorld() const;
		SDL_Rect GetOverLapSquare() { return m_Overlap; };

		void Initialize() override{};
		void FixedUpdate(const float) override{};
		void Update(const float) override{};
		void LateUpdate(const float) override{};
		void Render() const override{};

		bool GetIsOverlapper(){return m_GenerateOverLapEvent; }
		void SetIsOverlapper(bool isOverlapper) { m_GenerateOverLapEvent = isOverlapper; }
		bool GetIsCollider() const { return m_GenerateCollisionEvent; }
		void SetIsCollider(bool isCollider) { m_GenerateCollisionEvent = isCollider; }

	private:

		bool m_IsOverLapping = false;
		SDL_Rect m_Overlap;

		bool m_GenerateOverLapEvent = true;
		bool m_GenerateCollisionEvent = false;

	};
	
}

