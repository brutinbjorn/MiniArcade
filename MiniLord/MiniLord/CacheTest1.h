#pragma once
#include "BaseComponent.h"
#include "imgui_plot.h"

namespace MiniLord
{
	class CacheTest1 :
	    public BaseComponent
	{
	public:
		CacheTest1() = default;
		~CacheTest1() = default;
		CacheTest1(const CacheTest1& other) = delete;
		CacheTest1(CacheTest1&& other) noexcept = delete;
		CacheTest1& operator=(const CacheTest1& other) = delete;
		CacheTest1& operator=(CacheTest1&& other) noexcept = delete;

		void Initialize() override;
		void Update(const float) override ;
		void LateUpdate(const float) override {};
		void FixedUpdate(const float) override {};
		void Render() const override {};
		void GuiRender() override;


	private:
		void GenerateTestData();
		std::vector<float> m_TimeMeasuremtents {};
		bool m_TestHasRun = false;

		//ImGuiStuff
		ImGui::PlotConfig m_plot;
		bool m_ButtonInput = false;

	};
	
}

