#pragma once
#include "BaseComponent.h"
#include "imgui_plot.h"


namespace MiniLord
{

	class CacheTest2 :
	    public BaseComponent
	{
	public:
		CacheTest2() = default;
		~CacheTest2() override = default;
		CacheTest2(const CacheTest2& other) = delete;
		CacheTest2(CacheTest2&& other) noexcept = delete;
		CacheTest2& operator=(const CacheTest2& other) = delete;
		CacheTest2& operator=(CacheTest2&& other) noexcept = delete;


		void Initialize() override {};
		void FixedUpdate(const float) override {};
		void Update(const float) override;
		void LateUpdate(const float) override {};
		void Render() const override {};
		void GuiRender() override;
	private:

		void GenerateTestDataOne();
		std::vector<float> m_TimeMeasuremtentsTestOne{};
		bool m_TestOneHasRun = false;
		bool m_ButtonTestOnePressed = false;
		ImGui::PlotConfig m_plotOne {};

		void GenerateTestDataTwo();
		std::vector<float> m_TimeMeasuremtentsTestTwo{};
		bool m_TestTwoHasRun = false;
		bool m_ButtonTestTwoPressed = false;
		ImGui::PlotConfig m_PlotTwo {};


	};
	
}

