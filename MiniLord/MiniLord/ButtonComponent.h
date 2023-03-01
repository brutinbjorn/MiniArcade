#pragma once
#include "MiniLordPCH.h"
#include "BaseComponent.h"

namespace MiniLord
{
	class ButtonComponent :
	    public BaseComponent
	{
	public:
		ButtonComponent() = default;
		~ButtonComponent() override = default;
		ButtonComponent(const ButtonComponent& other) = delete;
		ButtonComponent(ButtonComponent&& other) noexcept = delete;
		ButtonComponent& operator=(const ButtonComponent& other) = delete;
		ButtonComponent& operator=(ButtonComponent&& other) noexcept = delete;

		void Initialize() override {};
		void FixedUpdate(const float) override {};
		void Update(const float ) override {};
		void LateUpdate(const float ) override {};
		void Render() const override;

#if _DEBUG
		void GuiRender() override {};
#endif

		void SetSquare(const SDL_Rect& newRect) { m_ButtonSize = newRect; }
	protected:

	private:
		SDL_Rect m_ButtonSize;

#if _DEBUG
		SDL_Color m_debugColor;
#endif
	};
	
}

