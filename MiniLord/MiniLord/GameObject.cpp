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

void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0);
}

void GameObject::AddComponent(BaseComponent* ToAdd)
{
	if (ToAdd->m_pParent != nullptr && ToAdd->m_pParent != this)
		ToAdd->m_pParent->RemoveComponent(ToAdd);

	ToAdd->m_pParent = this;
	m_pComponents.push_back(ToAdd);
}

void GameObject::RemoveComponent(BaseComponent* ToRemove)
{
	//RECONS, deleting a component can break dependency of other comps if: InterLinked.
	//TODO swap with erase,remove.
	//RECONS swap to smart pointers.

	for (auto i = m_pComponents.begin(); i != m_pComponents.end(); i++)
	{
		if (*i == ToRemove)
		{
			i.operator*()->m_pParent = nullptr;
			m_pComponents.erase(i);
			delete *i;
			break;
		}
	}

}

//void GameObject::AddChildGameObject(std::shared_ptr<GameObject> newChild)
//{
//	newChild->m_pParentGameObject = this;
//	m_pChildObjects.push_back(newChild);
//
//}
