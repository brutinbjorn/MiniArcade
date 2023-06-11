#include "MiniLordPCH.h"
#include "Scene.h"
#include "GameObject.h"
//using namespace dae;

using namespace MiniLord;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name(name)
{}

void Scene::AddGameObject(const std::shared_ptr<GameObject>&object)
{
	if (m_IsInitialized == false)
		m_Objects.push_back(object);
	else
		m_objectsToAddPostLaunch.push_back(object);

//	object->Initialize();
}

void Scene::PostInitialize()
{
	int i = 0;
	for (auto object : m_Objects)
	{
		if(object->GetParentGameObject() == nullptr)
			object->Initialize();
		i++;
	}
	m_IsInitialized = true;
}

void Scene::FixedUpdate(const float ft)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(ft);
	}
}

void Scene::Update(const float dt)
{
	for (auto& object : m_Objects) //TODO This ignores the parent/child Relationship, make the scene the parent, or make the parent responcible for updating the children.
	{
		object->Update(dt);
	}
}

void Scene::LateUpdate(const float lt)
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate(lt);
		if (object->IsMarkedForDeletion())
			m_RunCleanUp = true;
	}

	if (m_RunCleanUp)
	{
		m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(),
			[](const std::shared_ptr<GameObject>& obj) { return obj->IsMarkedForDeletion(); }),
			m_Objects.end());

		for (auto& object : m_Objects)
			object->SetParentGameObject(nullptr, true);

		m_RunCleanUp = false;
	}

	if(!m_objectsToAddPostLaunch.empty())
	{
		for (uint32_t i = 0; i < m_objectsToAddPostLaunch.size(); ++i)
		{
			m_Objects.emplace_back(m_objectsToAddPostLaunch[i]);
			m_objectsToAddPostLaunch[i]->Initialize();
		}
		m_objectsToAddPostLaunch.clear();
	}

		// TODO Replace with erase,remove;
		//for (int i = 0; i < int(m_Objects.size()); ++i)
		//{
		//	if (m_Objects[i]->IsMarkedForDeletion())
		//	{
		//		m_Objects[i].swap(m_Objects.back());
		//		m_Objects.pop_back();
		//	}
		//}
		//m_RunCleanUp = false;
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::GuiRender() const
{
	for (const auto& object : m_Objects)
	{
		object->GuiRender();
	}
}


