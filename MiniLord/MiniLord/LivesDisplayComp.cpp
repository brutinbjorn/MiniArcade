#include "MiniLordPCH.h"
#include "LivesDisplayComp.h"

#include "GameObject.h"


void MiniLord::LivesDisplayComp::Initialize()
{
	for (int i = 0; i <= m_NmberOfHeartsToDraw; ++i)
	{
		auto Sprite = new RenderComponent();
		Sprite->SetTexture(m_FilePath);
		Sprite->SetOffset(static_cast<int>(m_Spacing.x) * i, static_cast<int>(m_Spacing.y) * i);
		Sprite->SetSize(10, 10);
		GetGameObject()->AddComponent(Sprite);
		m_heartsToRender.push_back(Sprite);
	}
}

void MiniLord::LivesDisplayComp::Update(const float)
{
	if(m_NmberOfHeartsToDraw != static_cast<int>(m_heartsToRender.size()))
	{
		if(m_NmberOfHeartsToDraw > static_cast<int>(m_heartsToRender.size()))
		{
			for(int i = static_cast<int>(m_heartsToRender.size()); i < m_NmberOfHeartsToDraw;i++)
			{
				auto Sprite = new RenderComponent();
				Sprite->SetTexture(m_FilePath);
				Sprite->SetOffset(static_cast<int>(m_Spacing.x) * i, static_cast<int>(m_Spacing.y) * i);
				Sprite->SetSize(10, 10);
				GetGameObject()->AddComponent(Sprite);
				m_heartsToRender.push_back(Sprite);
			}
		}
		else if(m_NmberOfHeartsToDraw < static_cast<int>(m_heartsToRender.size()))
		{
			for (int i = m_NmberOfHeartsToDraw; i < static_cast<int>(m_heartsToRender.size()); ++i)
			{
				//auto comp = m_heartsToRender.
				auto comp = m_heartsToRender.back();
				GetGameObject()->RemoveComponent(comp);
				delete comp;
				m_heartsToRender.pop_back();
				//delete comp;
			}
		}

	}
}


void MiniLord::LivesDisplayComp::DirectSetLives(int lives)
{
	m_NmberOfHeartsToDraw = lives;
}

void MiniLord::LivesDisplayComp::OnNotify(ObserverMessage msg, void* argPointer, int argSize)
{
	if(msg == ObserverMessage::Msg_PLAYER_LIFE_CHANGED)
	{
		if(argPointer == nullptr)
		{
			m_NmberOfHeartsToDraw -= 1;
		}
		else if(argSize == sizeof(int))
		{
			m_NmberOfHeartsToDraw = *static_cast<int*>(argPointer);
		}
	}
}

void MiniLord::LivesDisplayComp::OnNotifyDestruction(ObserverMessage , void* , int ) 
{
	m_NmberOfHeartsToDraw = 0;
}
