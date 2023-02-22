#pragma once

#include <glm/glm.hpp>

namespace MiniLord
{
	class Transform final
	{
	public:
		//get current world position
		const glm::vec3& GetPosition() const { return m_Position; }

		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& pos);

		// add to current position.
		void Translate(float x, float y, float z);
		void Translate(const glm::vec3& Translate);
	private:
		glm::vec3 m_Position;
	};
}

