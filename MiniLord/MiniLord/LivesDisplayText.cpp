#include "MiniLordPCH.h"
#include "LivesDisplayText.h"

#include "TextComponent.h"


MiniLord::LivesDisplayText::LivesDisplayText(TextComponent* myText, const std::string& livesText)
	:nm_textComp(myText)
	,m_Livestext(livesText)
{
}

void MiniLord::LivesDisplayText::Update(const float)
{
	if (m_needsUpdate && nm_textComp)
	{
		nm_textComp->SetText(m_Livestext + std::to_string(m_health));
		m_needsUpdate = false;
	}
}

void MiniLord::LivesDisplayText::OnNotify(ObserverMessage msg, void* argPointer, int ArgLength)
{
	if (msg == ObserverMessage::Msg_PLAYER_LIFE_CHANGED && ArgLength == sizeof(int) && argPointer != nullptr)
	{
		m_health = *static_cast<int*>(argPointer);
		m_needsUpdate = true;
	}
}

void MiniLord::LivesDisplayText::OnNotifyDestruction(ObserverMessage , void* , int )
{

}
