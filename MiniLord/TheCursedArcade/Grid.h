#pragma once
#include "BaseComponent.h"


//digger grid size = 15 op 9

namespace MiniLord
{
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

		//old broken version
		//void GenerateCells();
		//std::vector<std::shared_ptr<GameObject>> CreateAndGetCells();
		//std::vector<std::shared_ptr<GameObject>> CreateAndGetCustomCells(glm::fvec2 sizeOfCells);
		//std::vector<std::shared_ptr<GameObject>> CreateAndGetCustomCellsDigger(glm::fvec2 sizeOfCells,const std::string& jsonPath);
		std::vector<std::shared_ptr<GameObject>> [[nodiscard]] CreateCellsAndLanesFromJSONFile(glm::fvec2 sizeOfCells);


		GameObject* GetCellAtPosition(glm::fvec2 possiblePosition);
	
		const glm::fvec2& GetPlayerStartPosition() { return m_PlayerStartPos; };
		const glm::fvec2& GetEnemySpawnPosition() { return m_EnemySpawnSpot; };

		int GetWidth() { return m_width; };
		int getHeight() { return m_height; }

		GameObject* GetCellFromArray(int depth, int width);
		GameObject* GetCellFromArray(int index);

		glm::fvec2 GetCellSize() { return m_CellSize; };
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

		int m_spacingForLanes = 4;

		glm::fvec2 m_PlayerStartPos;
		glm::fvec2 m_EnemySpawnSpot;

		glm::fvec2 m_CellSize;
	};

}

