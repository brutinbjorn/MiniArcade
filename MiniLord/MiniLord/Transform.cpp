#include "MiniLordPCH.h"
#include "Transform.h"

void MiniLord::Transform::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void MiniLord::Transform::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}

void MiniLord::Transform::Translate(float x, float y, float z)
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;

}

void MiniLord::Transform::Translate(const glm::vec3& Translate)
{
	m_Position += Translate;
}
