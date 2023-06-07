#pragma once
#include "b2_contact.h"
#include "b2_world_callbacks.h"
#include "CollisionComponent.h"

namespace MiniLord
{
	class ContactListener :
	    public b2ContactListener
	{
	    void BeginContact(b2Contact* contact) override
	    {
	        b2Fixture* fixA = contact->GetFixtureA();
	        b2Fixture* fixB = contact->GetFixtureB();

	        b2Body* bodyA = fixA->GetBody();
	        b2Body* bodyB = fixB->GetBody();

			b2BodyUserData userDataA = bodyA->GetUserData();
	        b2BodyUserData userDataB = bodyB->GetUserData();

	        std::cout << "Contact detected between objects: ";

			CollisionComponent* collA = reinterpret_cast<CollisionComponent*>(userDataA.pointer);
	        CollisionComponent* collB = reinterpret_cast<CollisionComponent*>(userDataB.pointer);


			if (collA != nullptr && collB != nullptr)
			{
				try
				{
					collA->OnCollisionEnter(collB);
					collB->OnCollisionEnter(collA);
				}
				catch (...) { std::cout << "COllisionComp lost in the trigger" << std::endl; }
			}


	    }
	};
}

