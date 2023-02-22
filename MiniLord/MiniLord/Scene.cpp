#include "MiniLordPCH.h"
#include "Scene.h"
#include "GameObject.h"

//using namespace dae;

using namespace MiniLord;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name(name)
{}
Scene::~Scene() = default;

void Scene::AddGameObject(const std::shared_ptr<GameObject>&object)
{
	m_Objects.push_back(object);
}

void Scene::PostInitialize()
{
	for (auto& object : m_Objects)
	{
		object->Initialize();
	}
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
	for (auto& object : m_Objects)
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
		for (int i = 0; i < int(m_Objects.size()); ++i)
		{
			if (m_Objects[i]->IsMarkedForDeletion())
			{
				m_Objects[i].swap(m_Objects.back());
				m_Objects.pop_back();
			}
		}
		m_RunCleanUp = false;
	}



}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

