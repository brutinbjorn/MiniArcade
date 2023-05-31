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
	//TODONE swap with erase,remove.
	//RECONS swap to smart pointers.

	m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), ToRemove), m_pComponents.end());

	//for (auto i = m_pComponents.begin(); i != m_pComponents.end(); i++)
	//{
	//	if (*i == ToRemove)
	//	{
	//		i.operator*()->m_pParent = nullptr;
	//		m_pComponents.erase(i);
	//		delete *i;
	//		break;
	//	}
	//}

}
//FEEDBACK
//TODO static assert is aangeraden.
// ook zit meschien? met de raar geval dat er shit messed up geraakt door de parent/child tree?? 
void MiniLord::GameObject::SetParentGameObject(GameObject* newParent, bool worldPosStays)
{


	//transform logic
	if (newParent == nullptr)
		GetTransform().SetPosition(GetTransform().GetWorldPosition());
	else
	{
		if (worldPosStays)
			GetTransform().SetPosition(GetTransform().GetWorldPosition() - newParent->GetTransform().GetWorldPosition());
		GetTransform().SetDirty();
	}
	//end transform logic.


	//Parent logic
	std::unique_ptr<GameObject> child = nullptr;
	if(m_pParentGameObject != nullptr)
	{
		for(auto it = m_pParentGameObject->m_pChildObjects.begin(); it != m_pParentGameObject->m_pChildObjects.end(); ++it)
			if(it->get() == this)
			{
				child = std::move(*it);
				m_pParentGameObject->m_pChildObjects.erase(it);
			}
	}
	else
	{
		m_pParentGameObject = newParent;
		if(m_pParentGameObject != nullptr){
			if (child == nullptr)
				child = std::unique_ptr<GameObject>(this);
			m_pParentGameObject->m_pChildObjects.emplace_back(std::move(child));
		}
	}
	//End parent logic.


}



