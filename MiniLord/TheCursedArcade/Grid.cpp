#include "CursedArcadePCH.h"
#include "Grid.h"

#include "CellLogic.h"
#include "GameObject.h"
#include "JsonManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SquareComponent.h"
#include "ObjectConstructorCursedArc.h"

using namespace MiniLord;

//Grid::Grid(const std::string& CurrentSceneName, int widthAmount, int HeightAmount, glm::fvec2 size)
//	:m_width(widthAmount),m_height(HeightAmount),m_SizeOfTheGrid(size), m_CurrentSceneName(CurrentSceneName)
//{
//	//GenerateCells();
//}

Grid::Grid(const std::string& JSonfile/*,const glm::fvec2& gridSize*/)
	:m_jsonFile(JSonfile)//,m_SizeOfTheGrid(gridSize)
{

}

void Grid::Initialize()
{
	//GenerateCells();
}

//void Grid::GenerateCells()
//{
//	glm::fvec2 cellSize(m_SizeOfTheGrid.x/m_width,m_SizeOfTheGrid.y/m_height);
//
//	auto rect = SDL_Rect(
//		0, 
//		0,
//		static_cast<int>(cellSize.x), 
//		static_cast<int>(cellSize.y));
//
//	auto val = GetGameObject()->GetTransform().GetWorldPosition();
//	glm::fvec2 position = glm::fvec2{ val.x, val.y}; //center
//
//	for (int widthIndex = 0; widthIndex < m_width; ++widthIndex)
//	{
//		for (int heightIndex = 0; heightIndex < m_height; ++heightIndex)
//		{
//			//create the cell gameobject.
//			auto scene = SceneManager::GetInstance().GetScene(m_CurrentSceneName);
//			auto newCell = std::make_shared<GameObject>();
//			scene->AddGameObject(newCell);
//
//			newCell->GetTransform().SetPosition(
//				position.x + static_cast<float>(widthIndex) * cellSize.x,
//				position.y + static_cast<float>(heightIndex) * cellSize.y,
//				0);
//			//newCell->GetTransform().SetPosition(static_cast<float>(widthIndex/ m_width),static_cast<float>(heightIndex/ m_height),0);
//
//			//color for testing.
//			int r =  static_cast<int>( (255 * widthIndex / m_width) );
//			int b =  static_cast<int>( (255 * heightIndex / m_height) );
//			SDL_Color color = SDL_Color{ static_cast<unsigned char>(r),0 , static_cast<unsigned char>(b),60 };
//			auto newSquare = new SquareComponent(rect, color);
//
//			newCell->AddComponent(newSquare);
//			newCell->SetParentGameObject(GetGameObject(), true);
//			m_pcells.push_back(newCell.get());
//		}
//	}
//}
//std::vector<std::shared_ptr<GameObject>> Grid::CreateAndGetCells()
//{
//	std::vector<std::shared_ptr<GameObject>> cells;
//
//	glm::fvec2 cellSize = glm::fvec2(m_SizeOfTheGrid.x / m_width, m_SizeOfTheGrid.y / m_height);
//
//	auto val = GetGameObject()->GetTransform().GetWorldPosition();
//	glm::fvec2 position = glm::fvec2{ val.x, val.y }; //center
//
//	auto rect = SDL_Rect(0,0,
//		static_cast<int>(cellSize.x),
//		static_cast<int>(cellSize.y));
//
//	for (int witdhIndex = 0; witdhIndex < m_width; ++witdhIndex)
//	{
//		for (int heightIndex = 0; heightIndex < m_height; ++heightIndex)
//		{
//			auto newCell = std::make_shared<GameObject>();
//			newCell->GetTransform().SetPosition(
//				position.x + static_cast<float>(witdhIndex) * cellSize.x,
//				position.y + static_cast<float>(heightIndex) * cellSize.y, 0);
//
//			int red = (255 * witdhIndex / m_width);
//			int blue = (255 * heightIndex / m_height);
//
//			SDL_Color color = SDL_Color{ static_cast<unsigned char>(red),0 , static_cast<unsigned char>(blue),60 };
//			auto newSquare = new SquareComponent(rect, color);
//
//			newCell->AddComponent(newSquare);
//			//newCell->SetParentGameObject(GetGameObject(), true);
//			m_pcells.push_back(newCell.get());
//			cells.push_back(newCell);
//
//		}
//	}
//
//	return cells;
//}
//
//std::vector<std::shared_ptr<GameObject>> Grid::CreateAndGetCustomCells(glm::fvec2 sizeOfCells)
//{
//	std::vector<std::shared_ptr<GameObject>> cells;
//
//	glm::fvec2 offsetToTopLeft = { sizeOfCells.x * m_width / 2,sizeOfCells.y * m_height / 2 };
//	auto centerPosition = GetGameObject()->GetTransform().GetWorldPosition();
//	glm::fvec2 TopLeftNoCellOffset = glm::fvec2(centerPosition.x - offsetToTopLeft.x, centerPosition.y - offsetToTopLeft.y);
//
//	auto rect = SDL_Rect(0, 0,
//		static_cast<int>(sizeOfCells.x),
//		static_cast<int>(sizeOfCells.y));
//
//	for (int witdhIndex = 0; witdhIndex < m_width; ++witdhIndex)
//	{
//		for (int heightIndex = 0; heightIndex < m_height; ++heightIndex)
//		{
//			auto newCell = std::make_shared<GameObject>();
//			newCell->GetTransform().SetPosition(
//				TopLeftNoCellOffset.x + static_cast<float>(witdhIndex) * sizeOfCells.x,
//				TopLeftNoCellOffset.y + static_cast<float>(heightIndex) * sizeOfCells.y, 0);
//
//			int red = (255 * witdhIndex / m_width);
//			int blue = (255 * heightIndex / m_height);
//
//
//			SDL_Color color = SDL_Color{ static_cast<unsigned char>(red),0 , static_cast<unsigned char>(blue),60 };
//			auto newSquare = new SquareComponent(rect, color);
//
//			newCell->AddComponent(newSquare);
//			//newCell->SetParentGameObject(GetGameObject(), true);
//			m_pcells.push_back(newCell.get());
//			cells.push_back(newCell);
//
//		}
//	}
//	return cells;
//
//}
//
//std::vector<std::shared_ptr<GameObject>> Grid::CreateAndGetCustomCellsDigger(glm::fvec2 sizeOfCells,
//	const std::string&)
//{
//	std::vector<std::shared_ptr<GameObject>> cells;
//
//	glm::fvec2 offsetToTopLeft = {0,0 };
//	auto centerPosition = GetGameObject()->GetTransform().GetWorldPosition();
//	glm::fvec2 TopLeftNoCellOffset = glm::fvec2(centerPosition.x - offsetToTopLeft.x, centerPosition.y - offsetToTopLeft.y);
//
//
//	auto rect = SDL_Rect(static_cast<int>(-sizeOfCells.x/2), static_cast<int>( -sizeOfCells.y / 2), //AddCellOffset
//		static_cast<int>(sizeOfCells.x),
//		static_cast<int>(sizeOfCells.y));
//
//	glm::fvec2 TopleftWithCellOffset{ TopLeftNoCellOffset.x + rect.x,TopLeftNoCellOffset.y + rect.y };
//
//
//	for (int witdhIndex = 0; witdhIndex < m_width; ++witdhIndex)
//	{
//		for (int heightIndex = 0; heightIndex < m_height; ++heightIndex)
//		{
//			auto newCell = std::make_shared<GameObject>();
//			newCell->GetTransform().SetPosition(
//				TopLeftNoCellOffset.x + static_cast<float>(witdhIndex) * sizeOfCells.x,
//				TopLeftNoCellOffset.y + static_cast<float>(heightIndex) * sizeOfCells.y, 0);
//
//			int red = (255 * witdhIndex / m_width);
//			int blue = (255 * heightIndex / m_height);
//
//			SDL_Color color = SDL_Color{ static_cast<unsigned char>(red),0 , static_cast<unsigned char>(blue),60 };
//			auto newSquare = new SquareComponent(rect, color);
//
//			newCell->AddComponent(newSquare);
//			//newCell->SetParentGameObject(GetGameObject(), true);
//			
//			char currentDirection = CellDirections::Cell_All;
//			currentDirection -= (heightIndex == 0) * Cell_Up;
//			currentDirection -= (witdhIndex == 0) * Cell_Left;
//			currentDirection -= (heightIndex == m_height - 1) * Cell_Down;
//			currentDirection -= (witdhIndex == m_width - 1) * Cell_Right;
//
//			auto cellLogic = new CellLogic(5,currentDirection);
//			cellLogic->SetCellSize(sizeOfCells);
//
//			newCell->AddComponent(cellLogic);
//
//			m_pcells.push_back(newCell.get());
//
//			newCell->SetParentGameObject(GetGameObject(), true);
//			cells.push_back(newCell);
//		}
//	}
//	return cells;
//}

std::vector<std::shared_ptr<GameObject>> Grid::CreateCellsAndLanesFromJSONFile(glm::fvec2 sizeOfCells)
{
	std::vector<std::shared_ptr<GameObject>> CellObjectsToReturn;
	auto json = JsonManager::GetInstance().LoadJsonDoc(m_jsonFile);
	nlohmann::json jSizeOb = json["SizeOfGrid"];
	nlohmann::json jAr = json["Level01"];

//	auto witdh = jSizeOb.value();

	//"x": 15,
	//"y" : 10



	auto centerPosition = GetGameObject()->GetTransform().GetWorldPosition();
	glm::fvec2 TopLeftNoCellOffset = glm::fvec2(centerPosition.x - (sizeOfCells.x * 15 / 2), centerPosition.y - (sizeOfCells.y * 10 / 2));



	auto rect = SDL_Rect(static_cast<int>(-sizeOfCells.x / 2), static_cast<int>(-sizeOfCells.y / 2), //AddCellOffset
		static_cast<int>(sizeOfCells.x),
		static_cast<int>(sizeOfCells.y));

	glm::fvec2 TopleftWithCellOffset{ TopLeftNoCellOffset.x + sizeOfCells.x/2,TopLeftNoCellOffset.y + sizeOfCells.y/2 };
	int maxDepth = static_cast<int>(jAr.size());
	int maxWidth = 0;
	if (jAr.is_array())
	{
		int depth = 0;
		for (nlohmann::json::iterator row = jAr.begin(); row != jAr.end(); ++row)
		{
			if (row->is_array())
			{
				//maxHeight
				int width = 0;
				maxWidth = static_cast<int>(row->size());
				for (nlohmann::json::iterator Line = row->begin(); Line != row->end(); ++Line)
				{

					//GameObject
					auto CellToAdd = std::make_shared<GameObject>();
					auto cellPosition = glm::fvec2{
						TopleftWithCellOffset.x + static_cast<float>(width) * sizeOfCells.x,
						TopleftWithCellOffset.y + static_cast<float>(depth) * sizeOfCells.y };

					CellToAdd->GetTransform().SetPosition(cellPosition.x, cellPosition.y, 0);
					//End GameObject

					
					 //SquareComps
					SDL_Color color = SDL_Color{100,100 , 0,255 };
					auto newSquare = new SquareComponent(rect, color);
					CellToAdd->AddComponent(newSquare);
					//end SquareComps

					//CellLogicComp
					char currentDirection = CellDirections::Cell_All;
					currentDirection -= (depth == 0) * Cell_Up;
					currentDirection -= (width == 0) * Cell_Left;
					currentDirection -= (depth == maxDepth - 1) * Cell_Down;
					currentDirection -= (width == maxWidth - 1) * Cell_Right;
							
					auto cellLogic = new CellLogic(5, currentDirection,newSquare);



					// add the lanes for movement on the cell.
					auto horizontal = SDL_Rect(-5, -(5 + rect.h / 2), +5, 5 + rect.h / 2);
					auto horizontalLane = new SquareComponent(horizontal, SDL_Color{ 255,0 , 0,255 });
					cellLogic->SetHorizontalLane(horizontalLane);
					CellToAdd->AddComponent(horizontalLane);
					m_pHorizontalLanes.push_back(horizontalLane);

					auto vertical = SDL_Rect(-5, -(5 + rect.h / 2), +5, 5 + rect.h / 2);
					auto verticalLane = new SquareComponent(vertical, SDL_Color{ 255,0 , 0,255 });
					cellLogic->SetVerticalLane(verticalLane);
					CellToAdd->AddComponent(verticalLane);
					m_pHorizontalLanes.push_back(verticalLane);



					if (Line.value().is_number())
					{
						auto val = Line.value().get<int>();

						if (val & 0b001) // BASIC DIGGOUT CHECK
							cellLogic->SetDiggedOut(false);

						if (val & 0b010) // Get player position
							m_PlayerStartPos = cellPosition;

						if (val & 0b100) // Get Enemy spawn point.
							m_EnemySpawnSpot = cellPosition;

						if (val & 0b1000)
						{
							auto gem = std::make_shared<GameObject>();
							ObjectConstructorCursedArc::DiggerGem(gem);
							gem->GetTransform().SetPosition(cellPosition.x, cellPosition.y, 0);

							m_Gems.push_back(gem.get());
							gem->SetParentGameObject(CellToAdd.get(), true);
							CellObjectsToReturn.push_back(gem);
						}
						if (val & 0b10000)
						{
							auto Bag = std::make_shared<GameObject>();
							ObjectConstructorCursedArc::DiggerGoldBag(Bag);

							Bag->GetTransform().SetPosition(cellPosition.x, cellPosition.y, 0);
							m_Bags.push_back(Bag.get());
							CellObjectsToReturn.push_back(Bag);
							cellLogic->SetDirections(Cell_None);
						}
					}
					cellLogic->SetCellSize(sizeOfCells);


					CellToAdd->AddComponent(cellLogic);
					CellToAdd->SetParentGameObject(GetGameObject(), true);
					CellObjectsToReturn.push_back(CellToAdd);
					m_pcells.push_back(CellToAdd.get());
					width++;
				}
			}
			depth++;
		}
	}

	std::vector<std::shared_ptr<GameObject>> Lanes;
	glm::ivec2 ExtraSizesOfLanes{ 4,4 };



	return CellObjectsToReturn;
}


::GameObject* Grid::GetCellAtPosition(glm::fvec2 possiblePosition)
{
	for (int i = 0; i < m_pcells.size(); ++i)
	{
		if (m_pcells[i]->GetComponent<SquareComponent>()->IsPointOverlapping(possiblePosition))
			return m_pcells[i];
	}
	return nullptr;
}

char Grid::GetPossibleDirections(glm::fvec2 )
{
	return 0;
}





