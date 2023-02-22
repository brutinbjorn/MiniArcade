#include "MiniLordPCH.h"
#include "Texture2D.h"
#pragma warning(push)
#pragma warning(disable:26812)
#pragma warning(disable:26819)
#include "SDL.h"
#pragma warning(pop)

MiniLord::Texture2D::~Texture2D()
{
	std::cout << "Texture popped" << std::endl;
	SDL_DestroyTexture(m_Texture);
}


SDL_Texture* MiniLord::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

MiniLord::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;

}
