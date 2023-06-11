#pragma once
#include "MiniLordPCH.h"
#include "BaseComponent.h"

namespace MiniLord
{
	class SquareComponent;
	class Command;

	class ButtonComponent :
	    public BaseComponent
	{
	public:
		ButtonComponent(SquareComponent* ButtonSquare, std::unique_ptr<Command> Command);
		~ButtonComponent() override = default;
		ButtonComponent(const ButtonComponent& other) = delete;
		ButtonComponent(ButtonComponent&& other) noexcept = delete;
		ButtonComponent& operator=(const ButtonComponent& other) = delete;
		ButtonComponent& operator=(ButtonComponent&& other) noexcept = delete;

		void Initialize() override {};
		void FixedUpdate(const float) override {};
		void Update(const float ) override;
		void LateUpdate(const float ) override {};
		void Render() const override;

#if _DEBUG
		void GuiRender() override {};
#endif

	protected:

	private:
		std::unique_ptr<Command> m_pCommand = nullptr;
		SquareComponent* m_pSquareComp = nullptr;

#if _DEBUG
		SDL_Color m_debugColor = {255,0,255,255};
#endif
	};
	
}

