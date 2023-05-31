#pragma once
#include "b2_body.h"
#include "BaseComponent.h"

namespace MiniLord
{
	class Box2DComponent :public BaseComponent
	{
	public:
		Box2DComponent() = default;
		~Box2DComponent() override = default;
		Box2DComponent(const Box2DComponent& other) = delete;
		Box2DComponent(Box2DComponent&& other) noexcept = delete;
		Box2DComponent& operator=(const Box2DComponent& other) = delete;
		Box2DComponent& operator=(Box2DComponent&& other) noexcept = delete;

		void Initialize() override {};
		void FixedUpdate(const float) override {};
		void Update(const float) override {};
		void LateUpdate(const float) override {};
		void Render() const override {};
		void GuiRender() override {};
		bool Recieve(BaseComponent*, const std::string&) override {};

	private:
		//b2Body m_Body;
	};
	
}

