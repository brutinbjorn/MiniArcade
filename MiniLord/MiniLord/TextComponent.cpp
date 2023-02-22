#include "MiniLordPCH.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include <SDL_ttf.h>


#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"


MiniLord::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font,
                                       RenderComponent* RendComp):
	nm_pRenderComponent(RendComp),
	m_NeedsUpdate(true),
	m_Text(text),
	m_Font(font),
	m_color(SDL_Color{ 255,255,255 })
{
}

void MiniLord::TextComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		
		SDL_FreeSurface(surf);
		nm_pRenderComponent->SetTexture(new Texture2D(texture));
		m_NeedsUpdate = false;
	}
}

void MiniLord::TextComponent::Render() const
{

}

void MiniLord::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void MiniLord::TextComponent::SetColor(const SDL_Color& color)
{
	m_color = color;
	m_NeedsUpdate = true;
}
