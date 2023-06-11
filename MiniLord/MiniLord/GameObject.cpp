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
	for(uint32_t i = 0;i <m_pChildObjects.size(); i++)
	{
		//m_pChildObjects[i]->SetParentGameObject(nu)
		m_pChildObjects[i].release();
	}

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
	int icheck =0;
	for (auto& child : m_pChildObjects)
	{
		icheck++;
		child->Initialize();
	}
}

void GameObject::FixedUpdate(const float ft)
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->FixedUpdate(ft);
	}
	for (auto& child: m_pChildObjects)
		child->FixedUpdate(ft);
	
};

void GameObject::Update(const float dt)
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Update(dt);
	}
	for (auto& child : m_pChildObjects)
		child->Update(dt);

}

void GameObject::LateUpdate(const float lt)
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
		m_pComponents[i]->LateUpdate(lt);
	for (uint32_t i= 0; i < m_pChildObjects.size(); i++ )
		m_pChildObjects[i]->LateUpdate(lt);
	
}

void GameObject::Render() const
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
		m_pComponents[i]->Render();

	for (uint32_t i = 0; i < m_pChildObjects.size(); i++)
		m_pChildObjects[i]->Render();
	
}

void MiniLord::GameObject::GuiRender() const
{
	for (const auto& component : m_pComponents)
	{
		component->GuiRender();
	}
	for (auto& child : m_pChildObjects)
		child->GuiRender();

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

	m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), ToRemove), m_pComponents.end());

}

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
	if (m_pParentGameObject != nullptr)
	{
		auto it = std::find_if(m_pParentGameObject->m_pChildObjects.begin(), m_pParentGameObject->m_pChildObjects.end(),
			[this](const std::unique_ptr<GameObject>& obj) { return obj.get() == this; });

		if (it != m_pParentGameObject->m_pChildObjects.end())
		{;
			it->release();
			child = std::move(*it);
			m_pParentGameObject->m_pChildObjects.erase(it);
		}
	}

	m_pParentGameObject = newParent;
	if(m_pParentGameObject != nullptr)
	{
		if (child == nullptr)
			child = std::unique_ptr<GameObject>(this);
		m_pParentGameObject->m_pChildObjects.push_back(std::move(child));
	}
	
	//End parent logic.
}



