#pragma once
#include "BaseComponent.h"
namespace MiniLord
{
	class TextComponent;

	class FPSRenderComponent :
	    public BaseComponent
	{
	public:
		FPSRenderComponent(TextComponent* textComp);
		~FPSRenderComponent() = default;
		FPSRenderComponent(const FPSRenderComponent& other) = delete;
		FPSRenderComponent(FPSRenderComponent&& other) noexcept = delete;
		FPSRenderComponent& operator=(const FPSRenderComponent& other) = delete;
		FPSRenderComponent& operator=(FPSRenderComponent&& other) noexcept = delete;

		void Initialize() override {};
		void FixedUpdate(const float ) override {};
		void Update(const float ) override;
		void LateUpdate(const float ) override {};
		void Render() const override {};
#if _DEBUG
		void GuiRender() override {};
#endif

	private:
		TextComponent* m_pTextComp;
		float m_TimeToUpdate = 1.f;
		float m_TimeToUpdateDelta = 0.f;

	};
}

