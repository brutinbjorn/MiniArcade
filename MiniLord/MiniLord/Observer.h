#pragma once



namespace MiniLord
{

	enum class ObserverMessage
	{
		Msg_UNKOWN = -1,
		Msg_DESTROYER_FIRED = 0,
		Msg_PLAYER_LIFE_CHANGED = 1,
		Msg_SCORE_CHANGED = 2
	};
	
}

namespace MiniLord::Interface
{
	/**
	 * \brief
	 * Observer is a "interface" class. should be added to exsisting classes/Components.
	 */
	class Observer
	{
	public:
		virtual ~Observer() = default;
		//virtual void OnNotify(ObserverMessage msg = ObserverMessage::Msg_UNKOWN) = 0;
		virtual void OnNotify(ObserverMessage msg, void* argPointer = nullptr, int ArgLength = 0) = 0;
		virtual void OnNotifyDestruction(ObserverMessage msg = ObserverMessage::Msg_DESTROYER_FIRED, void* argPointer = nullptr, int argLength = 0) = 0;
	private:
		//Observer() = delete;
	};
	
}

