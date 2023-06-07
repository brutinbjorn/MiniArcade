#include "RenderComponent.h"
#include "MiniLordPCH.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Transform.h"


using namespace MiniLord;

RenderComponent::~RenderComponent()
{
	delete m_pTexture;
	delete m_pSrcRect;
}

void RenderComponent::Render() const
{
	SDL_Rect testRect;

	if (m_pTexture)
	{
		//printf("rendering");
		//const Transform = Transform();

		const glm::vec3& pos = GetGameObject()->GetTransform().GetWorldPosition() + glm::vec3(m_offset, 0);
		testRect.x = int(pos.x);
		testRect.y = int(pos.y);
		testRect.w = int(m_Size.x);
		testRect.h = int(m_Size.y);
		//Renderer::GetInstance().RenderRect(&testRect, SDL_Color{ 255,255,255,255 });
		if (!m_IsSizeSet)
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Rotation);
		else if (!m_pSrcRect)
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Size.x, m_Size.y, m_Rotation);
		else
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Size.x, m_Size.y, *m_pSrcRect, m_Rotation);
	}

}


void RenderComponent::SetSize(int x, int y)
{

	m_IsSizeSet = true;
	m_Size.x = x;
	m_Size.y = y;
}

void RenderComponent::SetOffset(int x, int y)
{
	m_offset.x = static_cast<float>(x);
	m_offset.y = static_cast<float>(y);
}

void RenderComponent::SetTexture(const std::string& filename, bool QuarryTexture)
{
	if (m_pTexture)
		delete m_pTexture;
	m_pTexture = MiniLord::ResourceManager::GetInstance().LoadTexture(filename);

	// resetTexture Size;
	if(QuarryTexture)
		SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_Size.x, &m_Size.y);
	

}

void RenderComponent::SetTexture(MiniLord::Texture2D* texture2D, bool QuarryTexture)
{
	if (m_pTexture)
		delete m_pTexture;
	m_pTexture = texture2D;
	if(QuarryTexture)
		SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_Size.x, &m_Size.y);
	
}

void RenderComponent::SetSourceRect(SDL_Rect rect)
{
	delete m_pSrcRect;
	m_pSrcRect = new SDL_Rect{rect.x,rect.y,rect.w,rect.h};
}

glm::fvec2 RenderComponent::GetTextureSize() const
{
	int x =0 , y = 0;
	int errorValue = SDL_QueryTexture(m_pTexture->GetSDLTexture(),nullptr,nullptr,&x,&y);
	if (errorValue) {
		SDL_GetError();
		return glm::fvec2{};
	}
	glm::fvec2 size = glm::fvec2(x, y);
	return size;
}
