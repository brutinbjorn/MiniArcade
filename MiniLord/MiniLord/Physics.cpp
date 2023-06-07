
#include "MiniLordPCH.h"
#include "Physics.h"
#include "box2d.h"



MiniLord::Box2DPhysics::Box2DPhysics(glm::fvec2 gravity):
	m_world(b2Vec2{gravity.x,gravity.y})
{}

MiniLord::Box2DPhysics::~Box2DPhysics()
{

}

void MiniLord::Box2DPhysics::AddContactListener(std::shared_ptr<b2ContactListener> contactListener)
{
	m_contactListeners.push_back(contactListener);
	m_world.SetContactListener(contactListener.get());
}
