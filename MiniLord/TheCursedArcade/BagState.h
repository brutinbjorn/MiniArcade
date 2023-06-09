#pragma once
#include "GameObject.h"


namespace MiniLord
{
	//class BagLogic;

	class BagState
	{
	public:
		BagState() = default;
		virtual ~BagState() = default;
		virtual void OnEnter(GameObject*) = 0;
		virtual BagState* Update(GameObject* bag) = 0;
	};


	class BurriedState :public BagState
	{
	public:
		BurriedState() = default;

		void OnEnter(GameObject*) override{};
		BagState* Update(GameObject*) override;

	};

	class ComprimisedState :public BagState
	{
	public:
		ComprimisedState(float time =3.f): m_timer(time){};

		void OnEnter(GameObject*) override;
		BagState* Update(GameObject*) override;
	private:
		glm::ivec2 m_originalOffset = {};
		float m_timer;
		float m_DoRandomOffsetAt = 0.5;
		float m_offsetTime = 0;
	};

	class FallingState: public BagState
	{
	public:
		FallingState() =default;

		void OnEnter(GameObject*) override;
		BagState* Update(GameObject*) override;
	private:
		glm::ivec2 m_lastPos = {};
		int m_CellsPassed = 0;
	};

	class RestState: public  BagState
	{
	public:
		RestState() = default;

		void OnEnter(GameObject*) override ;
		BagState* Update(GameObject*) override;
	private:

	};
	class GoldState: public BagState
	{
	public:
		GoldState() = default;

		void OnEnter(GameObject*) override;
		BagState* Update(GameObject*) override { return nullptr; };
	private:

	};



}