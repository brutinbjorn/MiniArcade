#include "MiniLordPCH.h"
#include "ButtonComponent.h"

#include "InputManager.h"
#include "Renderer.h"

MiniLord::ButtonComponent::ButtonComponent(SquareComponent* square, std::unique_ptr<Command>  Command)
	:m_pCommand(std::move(Command)), m_pSquareComp(square)
{
}






void MiniLord::ButtonComponent::Update(const float)
{

	if(InputManager::GetInstance().MouseWentDown())
	{
		std::cout << "button was pressed" << std::endl;

		auto pos = InputManager::GetInstance().GetMousePosition();
		if (m_pSquareComp->IsPointOverlapping(pos))
		{
#if _DEBUG
			std::cout << "overlap succeeded" << std::endl;
#endif

			m_pCommand->Execute();
		}
	}

}

void MiniLord::ButtonComponent::Render() const
{
#if _DEBUG
	//Renderer::GetInstance().RenderRect(&m_ButtonSize,m_debugColor);
#endif 
}
