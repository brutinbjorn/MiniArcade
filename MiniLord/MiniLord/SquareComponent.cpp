#include "MiniLordPCH.h"
#include "SquareComponent.h"

#include "GameObject.h"
#include "Renderer.h"

using namespace MiniLord;

SquareComponent::SquareComponent(const SDL_Rect& rect, const SDL_Color& color)
	:m_Rect(rect),m_color(color)
{
}

void SquareComponent::Render() const
{
	auto rectToRender = m_Rect;
	rectToRender.x = m_Rect.x + static_cast<int>(GetGameObject()->GetTransform().GetWorldPosition().x) + m_offset.x;
	rectToRender.y = m_Rect.y + static_cast<int>(GetGameObject()->GetTransform().GetWorldPosition().y) + m_offset.y;
	Renderer::GetInstance().RenderFullRect(rectToRender, m_color);
}
