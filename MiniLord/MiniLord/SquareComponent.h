#pragma once
#include "BaseComponent.h"
 namespace MiniLord
 {
	class SquareComponent :
	    public BaseComponent
	{
	public:
		SquareComponent(const SDL_Rect& rect, const SDL_Color& color = {255,255,255,255});
		~SquareComponent() override = default;
		SquareComponent(const SquareComponent& other) = delete;
		SquareComponent(SquareComponent&& other) noexcept = delete;
		SquareComponent& operator=(const SquareComponent& other) = delete;
		SquareComponent& operator=(SquareComponent&& other) noexcept = delete;

		void Initialize() override {};
		void FixedUpdate(const float) override {};
		void Update(const float) override;
		void LateUpdate(const float) override {};
		void Render() const override;

		const SDL_Color& GetColor() { return m_color;};
		void SetColor(const SDL_Color& color){m_color = color;};

		void ToggleRendering(bool isBeingRendered = true) { m_IsRendered = isBeingRendered; };
		bool IsPointOverlapping(glm::fvec2 pointPos);
		void RenderFullSquare(bool renderFull = true) { m_RenderFullRect = renderFull; };

		//bool IsSquareOverlapping(SquareComponent);

		SDL_Rect GetRectangle() { return m_Rect; };
		SDL_Rect GetSquareInWorld();
		glm::ivec2 GetOffset() { return m_offset; };

	private:
		SDL_Rect m_Rect = SDL_Rect{}; 
		SDL_Color m_color = SDL_Color{};
		glm::ivec2 m_offset = { 0,0 };

		bool m_IsRendered = true;
		bool m_RenderFullRect = false;

	};
 }

