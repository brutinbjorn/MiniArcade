#pragma once
namespace MiniLord
{
	class GameObject;
	class Scene;
	namespace ObjectConstructorCursedArc
	{
		void GameGridDigger(std::shared_ptr<GameObject>& newObj,const std::string& currentScene ,int collums, int rows, const glm::fvec2& TotalGridSize);
	}

}
