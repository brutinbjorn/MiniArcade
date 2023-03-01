#include "MiniLordPCH.h"
#include "FPSRenderComponent.h"

#include "TextComponent.h"
#include "TimeManager.h"

MiniLord::FPSRenderComponent::FPSRenderComponent(TextComponent* TextComp)
	:m_pTextComp(TextComp)
{
}

void MiniLord::FPSRenderComponent::Update(const float dt)
{
	m_TimeToUpdateDelta += dt;
	if (m_TimeToUpdate <= m_TimeToUpdateDelta)
	{
		m_TimeToUpdateDelta -= m_TimeToUpdate;
		if(m_pTextComp)
		{
			m_pTextComp->SetText("FPS: " + std::to_string(TimeManager::GetInstance().GetFPS()));
		}
	}
}
