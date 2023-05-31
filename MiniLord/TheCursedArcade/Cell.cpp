#include "CursedArcadePCH.h"
#include "Cell.h"

#include "GameObject.h"
#include "Renderer.h"


void MiniLord::Cell::Render() const
{
	SDL_Rect centerTest = SDL_Rect(-5, -5, 5, 5);
	Renderer::GetInstance().RenderRect(&centerTest);
	if(m_PossibleDirections & CellDirections::Cell_Up)
	{
		SDL_Rect UpDirection = SDL_Rect(-2, 2, 2, static_cast<int>( - (m_SizeOfCell.y + 2)));
		Renderer::GetInstance().RenderRect(&UpDirection,SDL_Color{255,0,0,255});
	}
}

bool MiniLord::Cell::CheckIfOverlappingCenter(glm::fvec2 point)
{
	auto worldPos = GetGameObject()->GetTransform().GetWorldPosition();
	glm::fvec2 worldPos2D = { worldPos.x, worldPos.y };
	if(std::abs(glm::distance(worldPos2D,point)) >=  m_sizeOfCenter)
		return false;
	return true;
}

void MiniLord::Cell::SetDiggedOut(bool setDiggedState)
{
	m_IsDiggedOut = setDiggedState;


}
