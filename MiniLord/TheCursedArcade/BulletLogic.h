#pragma once
#include <BaseComponent.h>
#include <OverlapEvent.h>

 namespace MiniLord
 {
	 class Grid;
	 class ActorComponent;

	 class BulletLogic :
		public BaseComponent,public Interface::OverlapEvent
	{
	public:
		BulletLogic(glm::fvec2 dir,Grid* grid);
		~BulletLogic()override = default;
		BulletLogic(const BulletLogic& other) = delete;
		BulletLogic(BulletLogic&& other) noexcept = delete;
		BulletLogic& operator=(const BulletLogic& other) = delete;
		BulletLogic& operator=(BulletLogic&& other) noexcept = delete;

		void OverlapEventBegin(GameObject* OtherObject) override;
		bool ColliderEventBegin(GameObject* , glm::fvec2 ) override {return false;};

		void Initialize() override;
		void FixedUpdate(const float) override{};
		void Update(const float) override;
		void LateUpdate(const float) override{};
		void Render() const override{};
	private:
		glm::fvec2 m_directionAndSpeed;
		ActorComponent* m_pActor;
		Grid* m_pGrid;

	};
 }

