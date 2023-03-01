#pragma once

#include <SDL_pixels.h>
#include <memory>
#include "BaseComponent.h"


namespace MiniLord
{
	class RenderComponent;	
	class Font;
	
	class TextComponent final: public BaseComponent
	{
	public:
		TextComponent(
			const std::string& text, 
			const std::shared_ptr<Font>& font,
			RenderComponent* RendComp);
		~TextComponent() override = default;

		void Initialize() override {};
		void FixedUpdate(const float ) override {};
		void Update(float ) override ;
		void LateUpdate(const float ) override {};
		void Render() const override {};

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
	
	protected:
		bool m_NeedsUpdate;
		//RECONS DIRECT LINK??
		RenderComponent* nm_pRenderComponent;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		SDL_Color m_color;
		
	};
}

