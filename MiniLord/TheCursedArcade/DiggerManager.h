#pragma once
#include <BaseComponent.h>
#include <Observer.h>

namespace MiniLord
{
	class DiggerManager : public BaseComponent, public Interface::Observer
	{
	public:
		DiggerManager(GameObject* ScoreObject);
		~DiggerManager() override = default;
		DiggerManager(const DiggerManager& other) = delete;
		DiggerManager(DiggerManager&& other) noexcept = delete;
		DiggerManager& operator=(const DiggerManager& other) = delete;
		DiggerManager& operator=(DiggerManager&& other) noexcept = delete;

		void OnNotify(ObserverMessage msg, void* argPointer, int ArgLength) override;
		void OnNotifyDestruction(ObserverMessage msg, void* argPointer, int argLength) override;
		

	private:
		void Initialize() override{};
		void FixedUpdate(const float) override{};
		void Update(const float) override {};
		void LateUpdate(const float) override{};
		void Render() const override{};

		int m_Currentscore = 0;
		int m_lives = 3;
		int m_GemsInARow = 0;

		GameObject* m_ScoreObject = nullptr;
		GameObject* m_LivesObject = nullptr;
	};


}


