#include "MiniLordPCH.h"
#include "SquareComponent.h"

#include "GameObject.h"
#include "Renderer.h"

using namespace MiniLord;

SquareComponent::SquareComponent(const SDL_Rect& rect, const SDL_Color& color)
	:m_Rect(rect),m_color(color)
{
}

void SquareComponent::Update(const float)
{
 
}

void SquareComponent::Render() const
{
	if(m_IsRendered)
	{
		//TODO implement dirty flag.
		auto rectToRender = m_Rect;
		rectToRender.x = m_Rect.x + static_cast<int>(GetGameObject()->GetTransform().GetWorldPosition().x) ;
		rectToRender.y = m_Rect.y + static_cast<int>(GetGameObject()->GetTransform().GetWorldPosition().y) ;
		if(m_RenderFullRect)
		{
			Renderer::GetInstance().RenderFullRect(&rectToRender, m_color);
		}
		else
		{
			Renderer::GetInstance().RenderRect(&rectToRender, m_color);
		}
		
	}
}


bool SquareComponent::IsPointOverlapping(glm::fvec2 pointPos)
{
	auto actualRect = m_Rect;
	actualRect.x = m_Rect.x + static_cast<int>(GetGameObject()->GetTransform().GetWorldPosition().x) ;
	actualRect.y = m_Rect.y + static_cast<int>(GetGameObject()->GetTransform().GetWorldPosition().y) ;

	if (actualRect.x < pointPos.x && actualRect.x + actualRect.w > pointPos.x &&
		actualRect.y < pointPos.y && actualRect.y + actualRect.h > pointPos.y)
		return true;
	return false;

}

SDL_Rect SquareComponent::GetSquareInWorld()
{
	auto rectToRender = m_Rect;
	rectToRender.x = m_Rect.x + static_cast<int>(GetGameObject()->GetTransform().GetWorldPosition().x) ;
	rectToRender.y = m_Rect.y + static_cast<int>(GetGameObject()->GetTransform().GetWorldPosition().y) ;
	return rectToRender;
}
