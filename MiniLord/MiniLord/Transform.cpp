#include "MiniLordPCH.h"
#include "Transform.h"

#include <functional>

#include "GameObject.h"

const glm::fvec3& MiniLord::Transform::GetWorldPosition()
{
	if (m_IsDirty)
	{
		UpdateWorld();
	}
	return m_WorldPosition;
}

const glm::fvec3& MiniLord::Transform::GetWorldRotation()
{
	if (m_IsDirty)
	{
		UpdateWorld();
	}
	return m_WorldRotation;
}

const glm::fvec3& MiniLord::Transform::GetWorldScale()
{
	if (m_IsDirty)
	{
		UpdateWorld();
	}
	return m_WorldScale;
}
//TODO Dirty flag normally needs to update the children, instead of  having the children ask the parent.
//
//
//
// moet nog eens kijken naar lambdas auto l = [](){}
//forward declaration is best als het alleen een pointer returned in header files.
//als het een object nodig heeft is het best om het te includen in de header.


void MiniLord::Transform::SetPosition(float x, float y, float z)
{
	SetDirty();
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
}

void MiniLord::Transform::SetPosition(const glm::fvec3& pos)
{
	SetDirty();
	m_LocalPosition = pos;
}

void MiniLord::Transform::SetRotation(const glm::fvec3& newRotation)
{ 
	SetDirty();
	m_LocalRotation = newRotation;
}

void MiniLord::Transform::SetRotation(float XRotation, float YRotation, float ZRotation)
{
	SetDirty();
	m_LocalRotation.x = XRotation;
	m_LocalRotation.y = YRotation;
	m_LocalRotation.z = ZRotation;

}

void MiniLord::Transform::SetScale(const glm::fvec3& newScale)
{
	SetDirty();
	m_LocalScale = newScale;
}

void MiniLord::Transform::SetScale(float XScale, float YScale, float ZScale)
{
	SetDirty();
	m_LocalScale.x = XScale;
	m_LocalScale.y = YScale;
	m_LocalScale.z = ZScale;

}

void MiniLord::Transform::Translate(float x, float y, float z)
{
	SetDirty();
	m_LocalPosition.x += x;
	m_LocalPosition.y += y;
	m_LocalPosition.z += z;

}

void MiniLord::Transform::Translate(const glm::fvec3& Translate)
{
	SetDirty();
	m_LocalPosition += Translate;
}

void MiniLord::Transform::SetDirty() // moet de children zijn
{
	m_IsDirty = true;
	if (auto parent = GetGameObject())
	{
		auto& children = parent->GetChildren();
		for (uint32_t i = 0; i < children.size(); ++i)
		{
			children[i]->GetTransform().SetDirty();
		}
	}
}

void MiniLord::Transform::UpdateWorld()
{
	if (m_IsDirty)
	{
		auto thisob = this->GetGameObject();
		GameObject* ob = thisob->GetParentGameObject(); // get the parent. 
		if (ob == nullptr)
		{
			m_WorldPosition = m_LocalPosition;
			m_WorldRotation = m_LocalRotation;
			m_WorldScale = m_LocalScale;
			//std::cout << "Dirty flag trigger, no parent, pos:"<< m_LocalPosition.x << ":" << m_LocalPosition.y << ":" << "/n";
		}
		else
		{
			auto parentTransform = ob->GetTransform();
			m_WorldPosition = m_LocalPosition + parentTransform.GetWorldPosition();
			m_WorldRotation = m_LocalRotation + parentTransform.GetWorldRotation();
			m_WorldScale = m_LocalScale * parentTransform.GetWorldScale();
			//std::cout << "Dirty flag trigger, no parent, pos:"<< m_WorldPosition.x << ":" << m_WorldPosition.y << ":" << "/n";

		}
	}
	m_IsDirty = false;
}


MiniLord::Transform::Transform()
	:m_LocalPosition(0, 0, 0)
	, m_LocalRotation(0, 0, 0)
	, m_LocalScale(1, 1, 1)
{
}
