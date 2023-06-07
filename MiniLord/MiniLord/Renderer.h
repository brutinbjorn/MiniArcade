#pragma once
#include "MiniLordPCH.h"
#include "Singleton.h"

struct SDL_Window;
struct SDL_Rect;
namespace MiniLord
{
	class Texture2D;

	class Renderer : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render();
		void ImGuiRender();

		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, const double angle = 0) const;
		void RenderTexture(const Texture2D& texture, float x, float y, int width, int height, const double angle = 0) const;
		void RenderTexture(const Texture2D& texture, float x, float y, int width, int height, const SDL_Rect& srcRect, const double angle = 0) const;


		void RenderRect(const SDL_Rect* rectangle) const;
		void RenderRect(const SDL_Rect* rectangle, const SDL_Color color) const;

		void RenderFullRect(const SDL_Rect* rect, const SDL_Color color) const;

		glm::ivec2 GetWindowSize() const;
		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

	private:
		friend class Singleton<Renderer>;
		Renderer() = default;
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_pWindow = nullptr;
		SDL_Color m_clearColor = {0,0,120};

		bool m_ShowDemo{ true };
	};

	
}

