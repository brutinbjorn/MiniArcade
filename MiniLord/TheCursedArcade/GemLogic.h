#pragma once
#include <BaseComponent.h>
#include "box2d.h"
#include "PhysicsEvents.h"
#include "Subject.h"
#include "OverlapEvent.h"

namespace MiniLord
{
	class OverlapComp;

	class GemLogic :
		public BaseComponent, public Interface::OverlapEvent
	{
	public:
		GemLogic() = default;
		~GemLogic()override = default;
		GemLogic(const GemLogic& other) = delete;
		GemLogic(GemLogic&& other) noexcept = delete;
		GemLogic& operator=(const GemLogic& other) = delete;
		GemLogic& operator=(GemLogic&& other) noexcept = delete;

		void AddToObserver(Interface::Observer* ob) { m_subject.AddObserver(ob); };
		void RemoveFromObserver(Interface::Observer* ob) { m_subject.RemoveObserver(ob); }
		void Initialize() override{};
		void FixedUpdate(const float) override{};
		void Update(const float) override{}; 
		void LateUpdate(const float) override{};
		void Render() const override{};

		void OverlapEventBegin(GameObject* OtherObject) override;
		bool ColliderEventBegin(GameObject* otherObject, glm::fvec2 otherMovement) override;
		Subject m_subject;
	};
	
}

