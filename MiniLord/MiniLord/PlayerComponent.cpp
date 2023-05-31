#include "MiniLordPCH.h"
#include "PlayerComponent.h"

void MiniLord::PlayerComponent::Initialize()
{
	std::string msg = "PlayerInit";
	m_Subject.Notify(ObserverMessage::Msg_PLAYER_LIFE_CHANGED,&m_lives,sizeof(m_lives));
}
