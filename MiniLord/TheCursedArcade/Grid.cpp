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

std::vector<std::shared_ptr<GameObject>> Grid::CreateCellsAndLanesFromJSONFile(const std::string& levelName,glm::fvec2 sizeOfCells,Interface::Observer* obs)
{
	std::vector<std::shared_ptr<GameObject>> CellObjectsToReturn{};
	auto json = JsonManager::GetInstance().LoadJsonDoc(m_jsonFile);
	nlohmann::json jSizeOb = json["SizeOfGrid"];
	nlohmann::json jAr = json[levelName];

	m_pCells.clear();
	m_CellSize = sizeOfCells;
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
		int depthID = 0;
		for (nlohmann::json::iterator row = jAr.begin(); row != jAr.end(); ++row)
		{
			
			int widthID = 0;
			m_height = static_cast<int>(jAr.size());

			if (row->is_array())
			{
				m_width = maxWidth = static_cast<int>(row->size());
				for (nlohmann::json::iterator Line = row->begin(); Line != row->end(); ++Line)
				{

					//GameObject
					auto CellToAdd = std::make_shared<GameObject>();
					auto cellPosition = glm::fvec2{
						TopleftWithCellOffset.x + static_cast<float>(widthID) * sizeOfCells.x,
						TopleftWithCellOffset.y + static_cast<float>(depthID) * sizeOfCells.y };

					CellToAdd->GetTransform().SetPosition(cellPosition.x, cellPosition.y, 0);
					//End GameObject

					
					 //SquareComps
					SDL_Color color = SDL_Color{100,100 , 0,255 };
					auto newSquare = new SquareComponent(rect, color);
					CellToAdd->AddComponent(newSquare);
					//end SquareComps

					//CellLogicComp
					char currentDirection = CellDirections::Cell_All;
					currentDirection -= (depthID == 0) * Cell_Up;
					currentDirection -= (widthID == 0) * Cell_Left;
					currentDirection -= (depthID == maxDepth - 1) * Cell_Down;
					currentDirection -= (widthID == maxWidth - 1) * Cell_Right;
							
					auto cellLogic = new CellLogic(5, currentDirection,newSquare,depthID * m_width + widthID,widthID,depthID);



					// add the lanes for movement on the cell.
					auto horizontal = SDL_Rect(
						-m_spacingForLanes,
						-(m_spacingForLanes + rect.h / 2),
						+m_spacingForLanes * 2, 
						2 * 5 + rect.h );

					auto horizontalLane = new SquareComponent(horizontal, SDL_Color{ 255,0 , 0,255 });
					cellLogic->SetHorizontalLane(horizontalLane);
					CellToAdd->AddComponent(horizontalLane);


					auto vertical = SDL_Rect(
						-(m_spacingForLanes + rect.w /2),
						-m_spacingForLanes,
						2 * m_spacingForLanes + rect.w,
						m_spacingForLanes * 2);

					auto verticalLane = new SquareComponent(vertical, SDL_Color{ 0,0 , 255,255 });
					cellLogic->SetVerticalLane(verticalLane);
					CellToAdd->AddComponent(verticalLane);


					cellLogic->SetCellSize(sizeOfCells);
					CellToAdd->AddComponent(cellLogic);
					CellToAdd->SetParentGameObject(GetGameObject(), true);
					CellObjectsToReturn.emplace_back(CellToAdd);

					m_pCells.push_back(CellToAdd.get());

					if (Line.value().is_number())
					{
						auto val = Line.value().get<int>();

						if (val & 0b001) // BASIC DIGGOUT CHECK
							cellLogic->SetDiggedOut(true);

						if (val & 0b010) // Get player position
						{
							m_pl1StartPosSet = true;
							m_PlayerStartPos = cellPosition;
						}

						if (val & 0b100) // Get Enemy spawn point.
						{
							m_SpawnSet = true;
							m_EnemySpawnSpot = cellPosition;
						}


						if (val & 0b1000)
						{
							auto gem = std::make_shared<GameObject>();
							ObjectConstructorCursedArc::DiggerGem(gem,obs);
							gem->GetTransform().SetPosition(cellPosition.x, cellPosition.y, 0);

							m_pGems.push_back(gem.get());
							//gem->SetParentGameObject(CellToAdd.get(), true);
							CellObjectsToReturn.emplace_back(gem);
						}
						if (val & 0b10000)
						{
							auto Bag = std::make_shared<GameObject>();
							ObjectConstructorCursedArc::DiggerGoldBag(Bag,this,glm::ivec2(widthID,depthID), sizeOfCells,obs);

							Bag->GetTransform().SetPosition(cellPosition.x, cellPosition.y, 0);
							//Bag->SetParentGameObject(GetGameObject(), true);
							m_pBags.push_back(Bag.get());
							CellObjectsToReturn.emplace_back(Bag);
							//cellLogic->SetDirections(Cell_None);
						}
						if(val & 0b100000)
						{
							m_pl2StartPosSet = true;
							m_PlayerTwoStartPos = cellPosition;
						}
					}
					widthID++;
				}
			}
			depthID++;
		}
	}

	for(uint32_t i = 0; i < CellObjectsToReturn.size(); i++)
		m_stuffMade.push_back(CellObjectsToReturn[i]);

	return CellObjectsToReturn;
}


::GameObject* Grid::GetCellAtPosition(glm::fvec2 possiblePosition)
{
	for (uint32_t i = 0; i < m_pCells.size(); ++i)
	{
		if (m_pCells[i]->GetComponent<SquareComponent>()->IsPointOverlapping(possiblePosition))
			return m_pCells[i];
	}
	return nullptr;
}



GameObject* Grid::GetCellFromArray(int depth, int width)
{
	if (depth >= m_height || depth < 0)
		return nullptr;
	if (width >= m_width || width < 0)
		return nullptr;

	uint32_t row = depth * m_width;
	uint32_t ID = row + width;
	if(ID >= m_pCells.size())
		return nullptr;

	return m_pCells[ID];
}

GameObject* Grid::GetCellFromArray(int index)
{
	if (static_cast<uint32_t>(index) >= m_pCells.size())
		return nullptr;

	return m_pCells[index];
}

std::vector<GameObject*> Grid::GetNeighboursOfCell(CellLogic* cell)
{
	std::vector<GameObject*> result {};

	auto currentDepth = cell->GetDepthIndex();
	auto currentWidth = cell->GetWidthIndex();

	if (auto cellUp = GetCellFromArray(currentDepth - 1, currentWidth))
		result.push_back(cellUp);

	if (auto cellDown = GetCellFromArray(currentDepth + 1, currentWidth))
		result.push_back(cellDown);

	if (auto cellLeft = GetCellFromArray(currentDepth, currentWidth - 1))
		result.push_back(cellLeft);

	if (auto cellRight = GetCellFromArray(currentDepth, currentWidth + 1))
		result.push_back(cellRight);

	return result;
}

void Grid::ResetGameField()
{
	for (uint32_t i = 0; i < m_stuffMade.size(); i++)
	{
		if (m_stuffMade[i].expired() == false)
			m_stuffMade[i].lock()->SetMarkForDeletion(true);
	}
	//m_stuffMade.clear();

	m_pl1StartPosSet = false;
	m_pl2StartPosSet = false;
	
}





