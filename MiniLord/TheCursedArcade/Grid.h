#pragma once
#include "BaseComponent.h"
#include "Observer.h"


//digger grid size = 15 op 9

namespace MiniLord
{
	class CellLogic;
	class SquareComponent;


	class Grid : public BaseComponent
	{
	public:
		//Grid(const std::string& CurrentSceneName,int width, int height, glm::fvec2 Gridsize);
		Grid(const std::string& JSonfile/*, const glm::fvec2& gridSize*/);

		~Grid() override = default;
		Grid(const Grid& other) = delete;
		Grid(Grid&& other) noexcept = delete;
		Grid& operator=(const Grid& other) = delete;
		Grid& operator=(Grid&& other) noexcept = delete;
		
		void Initialize() override;
		void FixedUpdate(const float) override {};
		void Update(const float) override {};
		void LateUpdate(const float) override {};
		void Render() const override {};


		std::vector<std::shared_ptr<GameObject>> [[nodiscard]] CreateCellsAndLanesFromJSONFile(const std::string& lvlName, glm::fvec2 sizeOfCells,Interface::Observer* obs);


		GameObject* GetCellAtPosition(glm::fvec2 possiblePosition);

		bool IsPlayer1StartSpotSet() const { return m_pl1StartPosSet; };
		const glm::fvec2& GetPlayerStartPosition() const { return m_PlayerStartPos; };
		bool IsPlayer2StartSpotSet() const { return m_pl2StartPosSet; };
		const glm::fvec2& GetPlayerTwoStartPosition() const { return m_PlayerTwoStartPos; }
		bool IsEnemySpawnSet() const { return m_SpawnSet; }
		const glm::fvec2& GetEnemySpawnPosition() const { return m_EnemySpawnSpot; };

		int GetWidth() { return m_width; };
		int getHeight() { return m_height; }

		GameObject* GetCellFromArray(int depth, int width);
		GameObject* GetCellFromArray(int index);

		std::vector<GameObject*> GetNeighboursOfCell(CellLogic* cell);

		glm::fvec2 GetCellSize() { return m_CellSize; };
		void ResetGameField();
	private:

		int m_width = 0, m_height = 0;
		glm::fvec2 m_SizeOfTheGrid = glm::fvec2();

		std::string m_jsonFile;
		std::string m_CurrentSceneName;

		std::vector<GameObject*> m_pCells;
		std::vector<GameObject*> m_pGems;
		std::vector<GameObject*> m_pBags;

		std::vector<SquareComponent*> m_pHorizontalLanes;
		std::vector<SquareComponent*> m_pVerticalLanes;

		std::vector<std::weak_ptr<GameObject>> m_stuffMade{};

		int m_spacingForLanes = 4;

		bool m_pl1StartPosSet = false;
		glm::fvec2 m_PlayerStartPos {};
		bool m_pl2StartPosSet = false; 
		glm::fvec2 m_PlayerTwoStartPos {};

		bool m_SpawnSet = false;
		glm::fvec2 m_EnemySpawnSpot;

		glm::fvec2 m_CellSize;
	};

}

