#include "CursedArcadePCH.h"
#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SquareComponent.h"

using namespace MiniLord;

Grid::Grid(const std::string& CurrentSceneName, int widthAmount, int HeightAmount, glm::fvec2 size)
	:m_width(widthAmount),m_height(HeightAmount),m_SizeOfTheGrid(size), m_CurrentSceneName(CurrentSceneName)
{
	//GenerateCells();
}

void Grid::Initialize()
{
	//GenerateCells();
}

void Grid::GenerateCells()
{
	glm::fvec2 cellSize(m_SizeOfTheGrid.x/m_width,m_SizeOfTheGrid.y/m_height);

	auto rect = SDL_Rect(
		0, 
		0,
		static_cast<int>(cellSize.x), 
		static_cast<int>(cellSize.y));

	auto val = GetGameObject()->GetTransform().GetWorldPosition();
	glm::fvec2 position = glm::fvec2{ val.x, val.y}; //center

	for (int widthIndex = 0; widthIndex < m_width; ++widthIndex)
	{
		for (int heightIndex = 0; heightIndex < m_height; ++heightIndex)
		{
			//create the cell gameobject.
			auto scene = SceneManager::GetInstance().GetScene(m_CurrentSceneName);
			auto newCell = std::make_shared<GameObject>();
			scene->AddGameObject(newCell);

			newCell->GetTransform().SetPosition(
				position.x + static_cast<float>(widthIndex) * cellSize.x,
				position.y + static_cast<float>(heightIndex) * cellSize.y,
				0);
			//newCell->GetTransform().SetPosition(static_cast<float>(widthIndex/ m_width),static_cast<float>(heightIndex/ m_height),0);

			//color for testing.
			int r =  static_cast<int>( (255 * widthIndex / m_width) );
			int b =  static_cast<int>( (255 * heightIndex / m_height) );
			SDL_Color color = SDL_Color{ static_cast<unsigned char>(r),0 , static_cast<unsigned char>(b),60 };
			auto newSquare = new SquareComponent(rect, color);

			newCell->AddComponent(newSquare);
			newCell->SetParentGameObject(GetGameObject(), true);
			m_pcells.push_back(newCell.get());
		}
	}
}

std::vector<std::shared_ptr<GameObject>> Grid::CreateAndGetCells()
{
	std::vector<std::shared_ptr<GameObject>> cells;

	glm::fvec2 cellSize = glm::fvec2(m_SizeOfTheGrid.x / m_width, m_SizeOfTheGrid.y / m_height);

	auto val = GetGameObject()->GetTransform().GetWorldPosition();
	glm::fvec2 position = glm::fvec2{ val.x, val.y }; //center

	auto rect = SDL_Rect(0,0,
		static_cast<int>(cellSize.x),
		static_cast<int>(cellSize.y));

	for (int witdhIndex = 0; witdhIndex < m_width; ++witdhIndex)
	{
		for (int heightIndex = 0; heightIndex < m_height; ++heightIndex)
		{
			auto newCell = std::make_shared<GameObject>();
			newCell->GetTransform().SetPosition(
				position.x + static_cast<float>(witdhIndex) * cellSize.x,
				position.y + static_cast<float>(heightIndex) * cellSize.y, 0);

			int red = (255 * witdhIndex / m_width);
			int blue = (255 * heightIndex / m_height);

			SDL_Color color = SDL_Color{ static_cast<unsigned char>(red),0 , static_cast<unsigned char>(blue),60 };
			auto newSquare = new SquareComponent(rect, color);

			newCell->AddComponent(newSquare);
			//newCell->SetParentGameObject(GetGameObject(), true);
			m_pcells.push_back(newCell.get());
			cells.push_back(newCell);


		}
	}

	return cells;
}

std::vector<std::shared_ptr<GameObject>> Grid::CreateAndGetCustomCells(glm::fvec2 sizeOfCells)
{
	std::vector<std::shared_ptr<GameObject>> cells;

	glm::fvec2 offsetToTopLeft = { sizeOfCells.x * m_width / 2,sizeOfCells.y * m_height / 2 };
	auto centerPosition = GetGameObject()->GetTransform().GetWorldPosition();
	glm::fvec2 TopLeftNoCellOffset = glm::fvec2(centerPosition.x - offsetToTopLeft.x, centerPosition.y - offsetToTopLeft.y);

	auto rect = SDL_Rect(0, 0,
		static_cast<int>(sizeOfCells.x),
		static_cast<int>(sizeOfCells.y));

	for (int witdhIndex = 0; witdhIndex < m_width; ++witdhIndex)
	{
		for (int heightIndex = 0; heightIndex < m_height; ++heightIndex)
		{
			auto newCell = std::make_shared<GameObject>();
			newCell->GetTransform().SetPosition(
				TopLeftNoCellOffset.x + static_cast<float>(witdhIndex) * sizeOfCells.x,
				TopLeftNoCellOffset.y + static_cast<float>(heightIndex) * sizeOfCells.y, 0);

			int red = (255 * witdhIndex / m_width);
			int blue = (255 * heightIndex / m_height);


			SDL_Color color = SDL_Color{ static_cast<unsigned char>(red),0 , static_cast<unsigned char>(blue),60 };
			auto newSquare = new SquareComponent(rect, color);

			newCell->AddComponent(newSquare);
			//newCell->SetParentGameObject(GetGameObject(), true);
			m_pcells.push_back(newCell.get());
			cells.push_back(newCell);

		}
	}
	return cells;

}

std::vector<std::shared_ptr<GameObject>> Grid::CreateAndGetCustomCellsDigger(glm::fvec2 sizeOfCells,
	const std::string&)
{
	std::vector<std::shared_ptr<GameObject>> cells;

	glm::fvec2 offsetToTopLeft = { sizeOfCells.x * m_width / 2,sizeOfCells.y * m_height / 2 };
	auto centerPosition = GetGameObject()->GetTransform().GetWorldPosition();
	glm::fvec2 TopLeftNoCellOffset = glm::fvec2(centerPosition.x - offsetToTopLeft.x, centerPosition.y - offsetToTopLeft.y);


	auto rect = SDL_Rect(static_cast<int>(-sizeOfCells.x/2), static_cast<int>( -sizeOfCells.y / 2), //AddCellOffset
		static_cast<int>(sizeOfCells.x),
		static_cast<int>(sizeOfCells.y));

	glm::fvec2 TopleftWithCellOffset{ TopLeftNoCellOffset.x + rect.x,TopLeftNoCellOffset.y + rect.y };


	for (int witdhIndex = 0; witdhIndex < m_width; ++witdhIndex)
	{
		for (int heightIndex = 0; heightIndex < m_height; ++heightIndex)
		{
			auto newCell = std::make_shared<GameObject>();
			newCell->GetTransform().SetPosition(
				TopLeftNoCellOffset.x + static_cast<float>(witdhIndex) * sizeOfCells.x,
				TopLeftNoCellOffset.y + static_cast<float>(heightIndex) * sizeOfCells.y, 0);

			int red = (255 * witdhIndex / m_width);
			int blue = (255 * heightIndex / m_height);

			SDL_Color color = SDL_Color{ static_cast<unsigned char>(red),0 , static_cast<unsigned char>(blue),60 };
			auto newSquare = new SquareComponent(rect, color);

			newCell->AddComponent(newSquare);
			//newCell->SetParentGameObject(GetGameObject(), true);
			
			char currentDirection = CellDirections::Cell_All;
			currentDirection -= (heightIndex == 0) * Cell_Up;
			currentDirection -= (witdhIndex == 0) * Cell_left;
			currentDirection -= (heightIndex == m_height - 1) * Cell_Down;
			currentDirection -= (witdhIndex == m_width - 1) * Cell_Right;

			auto cellLogic = new Cell(5,currentDirection);
			cellLogic->SetCellSize(sizeOfCells);

			newCell->AddComponent(cellLogic);
			m_pcells.push_back(newCell.get());
			cells.push_back(newCell);
		}
	}
	return cells;

}




