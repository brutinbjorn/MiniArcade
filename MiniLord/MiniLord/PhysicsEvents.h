#pragma once

namespace MiniLord
{
	class CollisionComponent;
}

namespace MiniLord::Interface
{
	class PhysicsEvents
	{
	public:
		virtual void OnCollisionEnter(CollisionComponent* other) = 0;
	};
}


