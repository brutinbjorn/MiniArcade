#include "MiniLordPCH.h"
#include "GameObject.h"

using namespace MiniLord;
MiniLord::GameObject::GameObject()
{
	m_Transform = new Transform();
	AddComponent(m_Transform);
}
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

void MiniLord::GameObject::GuiRender() const
{
	for (const auto& component : m_pComponents)
	{
		component->GuiRender();
	}
}


//void GameObject::SetPosition(float x, float y)
//{
//	m_Transform.SetPosition(x, y, 0);
//}

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
//FEEDBACK
//TODO static assert is aangeraden.
// ook zit meschien? met de raar geval dat er shit messed up geraakt door de parent/child tree?? 
void MiniLord::GameObject::SetParentGameObject(GameObject* ParentGameobject)
{
	if (m_pParentGameObject) // if the object already has a parent?
	{
		m_pParentGameObject->m_pChildObjects.erase( // remove this object from the list of its former parent.
			std::remove(m_pParentGameObject->m_pChildObjects.begin(), m_pParentGameObject->m_pChildObjects.end(), this),
			m_pParentGameObject->m_pChildObjects.end());

		m_pParentGameObject = nullptr;
	}

	if(ParentGameobject != nullptr) // if the parent is a thing. (Not Scene).
		ParentGameobject->m_pChildObjects.emplace_back(ParentGameobject); // add to children
	m_pParentGameObject = ParentGameobject; // set parent

}



//void GameObject::SetParentObject(GameObject* newParent, bool keepWorldPosition)
//{
//	if (m_pParentGameObject && m_pParentGameObject != newParent) // former parent must be removed
//		m_pParentGameObject->RemoveChildObject(this); // former parent removes the (this) child.
//
//	AddChildObject(this, keepWorldPosition);
//	//TODO Update transforms
//}
//
//void GameObject::AddChildObject(GameObject* newChildObject, bool keepWorldPosition)
//{
//	newChildObject->SetParentObject(this,keepWorldPosition);
//	m_pChildObjects.push_back(newChildObject);
//}
//
//// erases the childobject 
//void GameObject::RemoveChildObject(GameObject* childObject)
//{
//
//	auto result = std::find(m_pChildObjects.begin(), m_pChildObjects.end(), childObject);
//	if (result != m_pChildObjects.end())
//	{
//		m_pChildObjects.erase(std::remove(m_pChildObjects.begin(),m_pChildObjects.end(),result), m_pChildObjects.end());
//	}
//	childObject->m_pParentGameObject = nullptr;
//	// remove parent relation from the child.
//}


//void GameObject::AddChildGameObject(std::shared_ptr<GameObject> newChild)
//{
//	newChild->m_pParentGameObject = this;
//	m_pChildObjects.push_back(newChild);
//
//}
