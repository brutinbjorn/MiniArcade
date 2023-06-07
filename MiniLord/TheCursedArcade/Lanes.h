#pragma once
#include <BaseComponent.h>

namespace MiniLord
{
	class Lanes :
	    public BaseComponent
	{
	public:
		Lanes() = default;
		~Lanes() override = default;
		Lanes(const Lanes& other) = delete;
		Lanes(Lanes&& other) noexcept = delete;
		Lanes& operator=(const Lanes& other) = delete;
		Lanes& operator=(Lanes&& other) noexcept = delete;

		//1 is UpDown,2 =LeftRight,3=None
		char GetDirectionAtSpot();

	private:
		void FixedUpdate(const float) override {};
		void Initialize() override{};
		void Update(const float) override {};
		void LateUpdate(const float) override {};
		void Render() const override {};

		char GetDirections = 0b01;


	};
}

