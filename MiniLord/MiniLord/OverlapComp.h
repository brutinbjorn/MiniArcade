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

		void SetOverlap(bool IsOverLapping) { m_IsOverLapping = IsOverLapping; };
		bool IsOverlapping() const { return m_IsOverLapping; };
		SDL_Rect GetOverlapSquareInWorld() const;


		void Initialize() override{};
		void FixedUpdate(const float) override{};
		void Update(const float) override{};
		void LateUpdate(const float) override{};
		void Render() const override{};
	private:

		bool m_IsOverLapping = false;
		SDL_Rect m_Overlap;

	};
	
}

