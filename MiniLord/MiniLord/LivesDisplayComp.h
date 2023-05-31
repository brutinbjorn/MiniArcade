#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "RenderComponent.h"

namespace MiniLord
{
	class LivesDisplayComp  final: public BaseComponent, public Interface::Observer
	{
	public:
		LivesDisplayComp(const std::string& filePath,int startLives,glm::fvec2 spacing = {10,0}):
		m_FilePath(filePath),
		m_Spacing(spacing),
		m_NmberOfHeartsToDraw(startLives)
		{}

		~LivesDisplayComp() override = default;

		LivesDisplayComp(const LivesDisplayComp& other) = delete;
		LivesDisplayComp(LivesDisplayComp&& other) noexcept = delete;
		LivesDisplayComp& operator=(const LivesDisplayComp& other) = delete;
		LivesDisplayComp& operator=(LivesDisplayComp&& other) noexcept = delete;

		//Base Comp 
		void Initialize() override ;
		void FixedUpdate(const float) override {};
		void Update(const float) override;
		void LateUpdate(const float) override {};
		void Render() const override {};
		//observer

		//void OnNotify(ObserverMessage msg) override;
		void OnNotify(ObserverMessage msg, void* argPointer = nullptr, int ArgLength = 0) override;
		void OnNotifyDestruction(ObserverMessage msg, void* argPointer = nullptr, int argLength = 0) override;
	private:
		std::vector<RenderComponent*> m_heartsToRender{};
		const std::string m_FilePath;
		glm::fvec2 m_Spacing {10.f,0};
		int m_NmberOfHeartsToDraw = 0;
		bool m_IsHealthDirty = false;

	};
	
}

