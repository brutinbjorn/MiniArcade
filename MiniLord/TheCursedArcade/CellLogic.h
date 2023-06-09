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
	Cell_Left = 0b1000,
	Cell_All = 0b1111
};

namespace MiniLord
{
	class CellLogic : public BaseComponent
	{
	public:
		CellLogic(float sizeOfCenter, char possibleDirections, SquareComponent* square, int index, int width, int height);
		~CellLogic() override = default;
		CellLogic(const CellLogic& other) = delete;
		CellLogic(CellLogic&& other) noexcept = delete;
		CellLogic& operator=(const CellLogic& other) = delete;
		CellLogic& operator=(CellLogic&& other) noexcept = delete;

		void Initialize() override;
		void FixedUpdate(const float) override{};
		void Update(const float) override{};
		void LateUpdate(const float) override{};
		void Render() const override;

		char GetDirections() const { return m_PossibleDirections; }
		void SetDirections(char newVal) { m_PossibleDirections = newVal; }

		bool CheckIfOverlappingCenter(glm::fvec2 point);
		bool CheckIfInCell(glm::fvec2 point);

		int GetIndex() { return m_cellIndex; }
		//glm::vec2 getDepthAndWitdhPos() { return m_cellDepthWitdh; }
		int GetWidthIndex() { return m_Width; };
		int GetDepthIndex() { return m_Height; }
		glm::ivec2 GetWidthDepth(){ return m_cellDepthWidth; }

		bool IsDiggedOut() { return m_IsDiggedOut; }
		void SetDiggedOut(bool setDiggedState);

		void SetCellSize(glm::fvec2 size) { m_SizeOfCell = size; }

		void SetHorizontalLane(SquareComponent* horizontalLane) { m_HorizontalLane = horizontalLane; }
		void SetVerticalLane(SquareComponent* verticalLane) { m_VerticalLane = verticalLane; }
		SquareComponent* GetHorizontalLane() const {return m_HorizontalLane; }
		SquareComponent* GetVerticalLane() const { return m_VerticalLane; }


	private:
		SquareComponent* m_RectComp;
		SquareComponent* m_HorizontalLane;
		SquareComponent* m_VerticalLane;

		glm::fvec2 m_SizeOfCell = {};
		glm::ivec2 m_cellDepthWidth ={};

		char m_PossibleDirections;
		float m_sizeOfCenter = 1.f;

		int m_cellIndex = -1;
		int m_Width = -1;
		int m_Height = -1;

		bool m_IsDiggedOut = false;
	};
}

