#include "MiniLordPCH.h"
#include "ActorComponent.h"

#include "GameObject.h"
#include "OverlapManager.h"

void MiniLord::ActorComponent::LateUpdate(const float dt)
{
	bool isBlocked = false;

	if (m_HasOverLap && m_HasOverLap->GetIsCollider())
		isBlocked = OverlapManager::GetInstance().CheckIfOverLapIsGonneHappen(m_HasOverLap, {m_Velocity * dt});
	//if (m_Velocity.x > 1)
	//	std::cout << "is moving" << std::endl;

	if (isBlocked == false) // is not blocked, can make move.
		GetGameObject()->GetTransform().Translate(m_Velocity.x * dt, m_Velocity.y * dt, 0);



	m_Velocity = glm::fvec2(0,0);
}

void MiniLord::ActorComponent::Initialize()
{
	auto hasOverlap = GetGameObject()->GetComponent<OverlapComp>();

	if (hasOverlap)
		m_HasOverLap = hasOverlap;

}

