#include "MiniLordPCH.h"
#include "CollisionComponent.h"

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "b2_world.h"
#include "GameObject.h"
#include "ServiceLocator.h"

#include "PhysicsEvents.h" 
void MiniLord::CollisionComponent::Initialize()
{
	//auto pos = GetGameObject()->GetTransform().GetWorldPosition();
	//m_groundBodyDef = {};

	//m_groundBodyDef.type = b2_dynamicBody;
	//m_groundBodyDef.position.Set(pos.x,pos.y);
	//m_groundBodyDef.fixedRotation = true;

	//auto world = ServiceLocator::GetPhysics().GetWorld();
	//m_pBody = world->CreateBody(&m_groundBodyDef);

	//b2PolygonShape shape;
	//shape.SetAsBox(m_bodySize.x, m_bodySize.y);

	//b2FixtureDef fixture{};
	//fixture.shape = &shape;
	//fixture.userData.pointer = reinterpret_cast<uintptr_t>(this);

	//m_pBody->CreateFixture(&fixture);

	//m_pBody->SetTransform(pos.x,pos,0);
}

void MiniLord::CollisionComponent::FixedUpdate(const float)
{
	
}

void MiniLord::CollisionComponent::Update(const float)
{

	//auto currentPhysicsPos = m_pBody->GetTransform().p;
	//GetGameObject()->GetTransform().Translate(currentPhysicsPos.x,currentPhysicsPos.y,0);
}

void MiniLord::CollisionComponent::Render() const
{
	
}

void MiniLord::CollisionComponent::OnCollisionEnter(CollisionComponent* other)
{
	for (auto comp : GetGameObject()->GetComponents())
	{
		if(auto val = dynamic_cast<Interface::PhysicsEvents*>(comp))
		{
			val->OnCollisionEnter(other);
		}
	};
}
