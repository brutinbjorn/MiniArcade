#pragma once
namespace MiniLord
{
	class Grid;
	class GameObject;
	class Scene;
	namespace ObjectConstructorCursedArc
	{
		//void GameGridDigger(std::shared_ptr<GameObject>& newObj,const std::string& currentScene ,int collums, int rows, const glm::fvec2& TotalGridSize);

		void GameGridDigger(std::shared_ptr<GameObject>& newObj, const std::string& jsonFile);

		void DiggerScoreComponent(std::shared_ptr<GameObject> newObj);

		void DiggerGem(std::shared_ptr<GameObject>& newObj);

		void DiggerGoldBag(std::shared_ptr<GameObject>& newObj,Grid* grid, glm::ivec2 widthDepthIndex, glm::fvec2 sizeOfCells);
	}

}
