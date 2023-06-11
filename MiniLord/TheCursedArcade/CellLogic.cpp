#include "CursedArcadePCH.h"
#include "CellLogic.h"

#include "GameObject.h"
#include "Renderer.h"
#include "SquareComponent.h"


using namespace MiniLord;
CellLogic::CellLogic(float sizeOfCenter, char possibleDirections, SquareComponent* square, int index,int width, int height)
	:m_RectComp(square), m_PossibleDirections(possibleDirections), m_sizeOfCenter(sizeOfCenter),
	m_cellIndex(index),m_Width(width),m_Height(height),m_cellDepthWidth(width,height)
{

}

void CellLogic::Initialize()
{
	if (m_RectComp)
		m_RectComp->RenderFullSquare(!m_IsDiggedOut);

}

void CellLogic::Render() const
{
	//SDL_Rect centerTest = SDL_Rect(-5, -5, 5, 5);
	//Renderer::GetInstance().RenderRect(&centerTest);
	//if(m_PossibleDirections & CellDirections::Cell_Up)
	//{
	//	SDL_Rect UpDirection = SDL_Rect(-2, 2, 2, static_cast<int>( - (m_SizeOfCell.y + 2)));
	//	Renderer::GetInstance().RenderRect(&UpDirection,SDL_Color{255,0,0,255});
	//}
}

bool CellLogic::CheckIfOverlappingCenter(glm::fvec2 point)
{
	auto worldPos = GetGameObject()->GetTransform().GetWorldPosition();
	glm::fvec2 worldPos2D = { worldPos.x, worldPos.y };
	if(std::abs(glm::distance(worldPos2D,point)) >=  m_sizeOfCenter)
		return false;
	return true;
}

bool CellLogic::CheckIfInCell(glm::fvec2 )
{
//	if()
	return false;
}

void CellLogic::SetDiggedOut(bool setDiggedState)
{
	m_IsDiggedOut = setDiggedState;

	if (m_RectComp)
		m_RectComp->RenderFullSquare(!m_IsDiggedOut);

}
