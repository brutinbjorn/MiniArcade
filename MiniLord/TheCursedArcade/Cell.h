#pragma once
#include "BaseComponent.h"

namespace MiniLord
{
	class SquareComponent;
}

enum CellDirections
{
	Cell_None = 0x00,
	Cell_Up = 0b0001,
	Cell_Right = 0b0010,
	Cell_Down = 0b0100,
	Cell_left = 0b1000,
	Cell_All = 0b1111
};

namespace MiniLord
{
	class Cell : public BaseComponent
	{
	public:
		Cell(float sizeOfCenter,char possibleDirections) : m_sizeOfCenter(sizeOfCenter), m_PossibleDirections(possibleDirections) {};
		~Cell() override = default;
		Cell(const Cell& other) = delete;
		Cell(Cell&& other) noexcept = delete;
		Cell& operator=(const Cell& other) = delete;
		Cell& operator=(Cell&& other) noexcept = delete;

		void Initialize() override{};
		void FixedUpdate(const float) override{};
		void Update(const float) override{};
		void LateUpdate(const float) override{};
		void Render() const override;

		char GetDirections() const { return m_PossibleDirections; };
		bool CheckIfOverlappingCenter(glm::fvec2 point);
		bool IsDiggedOut() { return m_IsDiggedOut; };
		void SetDiggedOut(bool setDiggedState);

		void SetCellSize(glm::fvec2 size) { m_SizeOfCell = size; }
	private:
		//SquareComponent* m_RectComp;
		char m_PossibleDirections;
		bool m_IsDiggedOut = true;
		float m_sizeOfCenter = 1.f;
		glm::fvec2 m_SizeOfCell = {};

	};
}

