#include "MiniLordPCH.h"
#include "GameObject.h"

using namespace MiniLord;
GameObject::~GameObject()
{
	for (uint32_t i = 0; i < m_pComponents.size(); ++i)
	{
		delete m_pComponents[i];
	}
}

void GameObject::Initialize() const
{
	for (uint32_t i = 0; i < m_pComponents.size(); ++i)
	{
		m_pComponents[i]->Initialize();
	}
}

void GameObject::FixedUpdate(const float ft)
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->FixedUpdate(ft);
	}
};

void GameObject::Update(const float dt)
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Update(dt);
	}
}

void GameObject::LateUpdate(const float lt)
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->LateUpdate(lt);
	}
}

void GameObject::Render() const
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Render();
	}
}

void GameObject::AddComponent(BaseComponent* ToAdd)
{
	m_pComponents.push_back(ToAdd);
}

void GameObject::AddChildGameObject(std::shared_ptr<GameObject> newChild)
{
	newChild->m_spParentGameObject = this;
	m_pChildObjects.push_back(newChild);

}
