#pragma once
namespace MiniLord
{
	namespace Interface
	{
		class Observer;
	}

	class Grid;
	class GameObject;
	class Scene;
	namespace ObjectConstructorCursedArc
	{
		//void GameGridDigger(std::shared_ptr<GameObject>& newObj,const std::string& currentScene ,int collums, int rows, const glm::fvec2& TotalGridSize);

		void GameGridDigger(std::shared_ptr<GameObject> newObj, const std::string& jsonFile);

		void DiggerScoreComponent(std::shared_ptr<GameObject> newObj);

		void DiggerGem(std::shared_ptr<GameObject> newObj, Interface::Observer* obs);

		void DiggerGoldBag(std::shared_ptr<GameObject> newObj, Grid* grid, glm::ivec2 widthDepthIndex, glm::fvec2 sizeOfCells, Interface::Observer* obs);

		void DiggerNobbin(std::shared_ptr<GameObject> newobj,Grid* grid, glm::fvec2 sizeOfOBject, Interface::Observer* obs);

		void PlayerOne(std::shared_ptr<GameObject> newObj, Scene* currentScene, Grid* grid, Interface::Observer* obs, glm::ivec2 objSize, bool usesController);

		void PlayerTwo(std::shared_ptr<GameObject> newObj, Scene* currentScene, Grid* grid, Interface::Observer* obs, glm::ivec2 objSize,bool usesController);

		void PlayerNobbin(std::shared_ptr<GameObject> newObj, Grid* grid, glm::fvec2 sizeOfOBject, Interface::Observer* obs, bool usesController);

		void PlayerBullet(std::shared_ptr<GameObject> newObj, Grid* grid,glm::fvec2 dirAndSpeed, glm::ivec2 objSize);
	}

}
