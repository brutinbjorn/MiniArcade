#include "MiniLordPCH.h"
#include "Renderer.h"

#include "SceneManager.h"
#include "Texture2D.h"

#pragma warning(push)
#pragma warning(disable:26495)
#include "imgui.h"
#include <backends/imgui_impl_sdl.h>
#include "backends/imgui_impl_opengl2.h" 
#pragma warning(pop)


using namespace MiniLord;

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Renderer::Init(SDL_Window* window)
{

	std::printf("Render init\n");
	m_pWindow = window;

	//TODO think if vsync is fucking up you physics or update time.

	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void Renderer::Render()
{

	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);
	SceneManager::GetInstance().Render();

#ifdef _DEBUG
	ImGuiRender();
#endif // _DEBUG
	SDL_RenderPresent(m_Renderer);
}

void Renderer::ImGuiRender()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();

	SceneManager::GetInstance().GuiRender();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void MiniLord::Renderer::RenderTexture(const Texture2D& texture, float x, float y, const double angle) const
{

	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, nullptr, SDL_FLIP_NONE);
}

void MiniLord::Renderer::RenderTexture(const Texture2D& texture, float x, float y, int width, int height,
	const double angle) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, nullptr, SDL_FLIP_NONE);
}

void MiniLord::Renderer::RenderTexture(const Texture2D& texture, float x, float y, int width, int height,
	const SDL_Rect& srcRect, const double angle) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dst, angle, nullptr, SDL_FLIP_NONE);
}

void Renderer::RenderRect(const SDL_Rect* rectangle) const
{
	SDL_SetRenderDrawColor(m_Renderer, 100, 100, 100, 255);
	SDL_RenderDrawRect(m_Renderer, rectangle);
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);


}
void Renderer::RenderRect(const SDL_Rect* rectangle, const SDL_Color color) const
{
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(m_Renderer, rectangle);
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

}

void Renderer::RenderFullRect(const SDL_Rect& rect, const SDL_Color color) const
{
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(m_Renderer, &rect);
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

}

glm::ivec2 Renderer::GetWindowSize() const
{
	glm::ivec2 value;
	SDL_GetRendererOutputSize(m_Renderer, &value.x, &value.y);
	return value;
}
