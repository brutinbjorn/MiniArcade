#pragma once

namespace MiniLord::Interface
{
	class OverlapEvent
	{
	public:
		OverlapEvent() = default;
		virtual ~OverlapEvent() = default;
		virtual void OverlapEventBegin(GameObject *OtherObject) = 0;

		virtual bool ColliderEventBegin(GameObject * otherObject, glm::fvec2 otherMovement) = 0;
	};
}
