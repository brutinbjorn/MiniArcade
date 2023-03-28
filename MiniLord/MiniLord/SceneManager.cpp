#include "MiniLordPCH.h"
#include "SceneManager.h"
#include "Scene.h"

using namespace MiniLord;

void SceneManager::FixedUpdate(const float ft)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(ft);
	}
}
void SceneManager::Update(const float dt)
{
	for (auto& scene : m_Scenes)
	{
		if(scene->IsActive())
		scene->Update(dt);
	}
}

void SceneManager::LateUpdate(const float lt)
{
	for (auto& scene : m_Scenes)
	{
		if(scene->IsActive())
			scene->LateUpdate(lt);
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		if(scene->IsActive())
		scene->Render();
	}
}

void MiniLord::SceneManager::GuiRender()
{
	for (const auto& scene : m_Scenes)
	{
		if(scene->IsActive())
		scene->GuiRender();
	}
}

//Creates a Base Scene in the SceneManager
Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& newscene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(newscene);
	return *newscene;
}



Scene* SceneManager::GetScene(const std::string& name)
{
	for (const auto& scene : m_Scenes)
		if (scene.get()->GetName() == name)
			return scene.get();

	return nullptr;
}

void SceneManager::AddScene(std::shared_ptr<Scene> newScene)
{
	m_Scenes.push_back(newScene);
	//m_ActiveScene = newScene;
}

void SceneManager::PostInitialize()
{
	for (const auto& scene : m_Scenes)
	{
		scene->PostInitialize();
	}
}
