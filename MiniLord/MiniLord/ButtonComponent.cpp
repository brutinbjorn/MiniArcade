#include "MiniLordPCH.h"
#include "ButtonComponent.h"

#include "Renderer.h"

void MiniLord::ButtonComponent::Render() const
{
#if _DEBUG
	Renderer::GetInstance().RenderRect(&m_ButtonSize,m_debugColor);

#endif

}
