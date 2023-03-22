#include "MiniLordPCH.h"
#include "RotateGameObject.h"
#include "GameObject.h"

RotateGameObject::RotateGameObject(float RotationSpeed, float distance)
	:m_Distance(distance),m_RotationSpeed(RotationSpeed)
{
}

void RotateGameObject::Update(const float dt)
{
	auto parent = GetGameObject();

	m_RotationDelta += dt * m_RotationSpeed;
	if (m_RotationDelta > 360.f) m_RotationDelta -= 360.f; //FEEDBACK, forgot decreasing m_Rot, so going into infinity.

	glm::fvec3 newPosition = glm::fvec3(std::cosf(m_RotationDelta), std::sinf(m_RotationDelta ), 0);
	newPosition *= m_Distance;
	parent->GetTransform().SetPosition(newPosition);
}
