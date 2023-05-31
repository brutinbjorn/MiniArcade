#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace MiniLord
{
	class TextComponent;

	class LivesDisplayText :
	    public BaseComponent,public MiniLord::Interface::Observer
	{

	public:
		LivesDisplayText(TextComponent* myText, const std::string& livesText = "lives: ");
		~LivesDisplayText()override = default;
		LivesDisplayText(const LivesDisplayText& other) = delete;
		LivesDisplayText(LivesDisplayText&& other) noexcept = delete;
		LivesDisplayText& operator=(const LivesDisplayText& other) = delete;
		LivesDisplayText& operator=(LivesDisplayText&& other) noexcept = delete;

		void Initialize() override {};
		void FixedUpdate(const float) override {};
		void Update(const float) override ;
		void LateUpdate(const float) override {};
		void Render() const override {};
		void OnNotify(ObserverMessage msg, void* argPointer, int ArgLength) override;
		void OnNotifyDestruction(ObserverMessage msg, void* argPointer, int argLength) override;
	private:
		std::string m_Livestext = "";
		TextComponent* nm_textComp;

		int m_health = 0;
		int m_needsUpdate = true;


	};
	
}

