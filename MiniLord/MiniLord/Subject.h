#pragma once
#include "Observer.h"
#include "algorithm"
namespace MiniLord
{
	//class BaseComponent;
	class Subject
	{
	public:
		Subject() = default;
		~Subject()
		{
			//for (auto observer : m_observers)
			//	if(observer != nullptr)
			//		observer->OnNotifyDestruction(ObserverMessage::Msg_DESTROYER_FIRED);
		}

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) noexcept = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) noexcept = delete;

		void AddObserver(Interface::Observer* newObserver)
		{
			if(newObserver != nullptr)
			{
				m_observers.push_back(newObserver);
				m_numberObservers++;
			}
		}
		void RemoveObserver(Interface::Observer* oldObserver)
		{
			auto val = std::remove(m_observers.begin(), m_observers.end(), oldObserver);
			m_numberObservers--;

		}

		void Notify(ObserverMessage msg, void* argPointer = nullptr, int argsize = 0) const
		{
			for (int i = 0; i < m_numberObservers; i++)
			{
				m_observers[i]->OnNotify(msg, argPointer, argsize);
			}
		}

	protected:
		std::vector<Interface::Observer*> m_observers{};
		int m_numberObservers = 0;

	};

}

