#include "MiniLordPCH.h"
#include "ActorComponent.h"

#include "GameObject.h"

void MiniLord::ActorComponent::Update(const float dt)
{

	GetGameObject()->GetTransform().Translate(m_Velocity.x * dt,m_Velocity.y * dt,0);
	m_Velocity = {};
}
