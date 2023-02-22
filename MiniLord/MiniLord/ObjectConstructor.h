
namespace MiniLord
{
	class GameObject;
	namespace ObjectConstructor
	{
		std::shared_ptr<GameObject> RenderObject(const std::string& TexturePath, float Xpos = 0, float Ypos = 0);

	}
}


//{
//	std::shared_ptr<dae::GameObject> BasicActor(const std::string& RenderFile);
//
//	std::shared_ptr<dae::GameObject> HealthBar(const glm::vec3& pos, const std::string& img);
//
//	std::shared_ptr<dae::GameObject> ScoreBar(const std::string& FontFile, const std::string& Text, unsigned int size, const glm::fvec2& pos);
//
//	std::shared_ptr<dae::GameObject> BaseButton(const glm::vec3& pos, const SDL_Rect& relativeRect ,const std::shared_ptr<dae::Font>& font);
//
//	std::shared_ptr<dae::GameObject> TextObject(const std::string& FontFile, const std::string& text, unsigned int size,  glm::fvec2 pos);
//}
