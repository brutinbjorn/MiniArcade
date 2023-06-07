#pragma once
#include "box2d.h"
class b2ContactListener;

namespace MiniLord
{
	class Physics
	{
	public:
		//virtual Physics() = default;
		virtual ~Physics() = default;
		virtual b2World* GetWorld() { return nullptr; };
		virtual void AddContactListener(std::shared_ptr<b2ContactListener>) {};
	private:
	};

	class Box2DPhysics : public Physics
	{
	public:
		Box2DPhysics(glm::fvec2 gravity);;
		~Box2DPhysics() override;
		Box2DPhysics(const Box2DPhysics& other) = delete;
		Box2DPhysics(Box2DPhysics&& other) noexcept = delete;
		Box2DPhysics& operator=(const Box2DPhysics& other) = delete;
		Box2DPhysics& operator=(Box2DPhysics&& other) noexcept = delete;

		b2World* GetWorld() override { return &m_world; };

		 void AddContactListener(std::shared_ptr<b2ContactListener> contactListener) override;
	
	private:
		b2World m_world;
		std::vector<std::shared_ptr<b2ContactListener>> m_contactListeners;
	};



}

