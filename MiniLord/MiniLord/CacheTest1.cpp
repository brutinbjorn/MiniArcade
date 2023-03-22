#include "MiniLordPCH.h"
#include "CacheTest1.h"

#include "imgui.h"
#include "imgui_plot.h"


using namespace MiniLord;
void CacheTest1::Initialize()
{

}

void CacheTest1::Update(const float)
{
    if(m_ButtonInput)
    {
        GenerateTestData();
        m_TestHasRun = true;
    }
}

void CacheTest1::GuiRender()
{
	ImGui::Begin("Trash the cache with ints", nullptr );
    
	m_ButtonInput = ImGui::Button("Test with int array", { 60,30 });
	ImGui::SetWindowSize(ImVec2{ 600,400 });
	if(m_TestHasRun)
		ImGui::Plot("plot1", m_plot);
	ImGui::End();
}

void CacheTest1::GenerateTestData()
{
    const int amount = 100000000;
    int* integers = new int[amount];

    float largestnumber = 0.f;

    for (size_t i = 0; i < amount; i++)
    {
        integers[i] = 1;
    }

    for (int stepSize = 1; stepSize < 1024; stepSize *= 2)
    {
        auto start = std::chrono::high_resolution_clock().now();
        for (long i = 0; i < amount; i += stepSize)
        {
            integers[i] *= 2;
        }
        auto end = std::chrono::high_resolution_clock().now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "operation took " << elapsed / 1000.f << " : ms at stepsize: " << std::to_string(stepSize) << std::endl;

        m_TimeMeasuremtents.push_back(static_cast<float>(elapsed));

        if (largestnumber < elapsed)
            largestnumber = static_cast<float>(elapsed);

    }
    delete[] integers;




    m_plot.values.ys = m_TimeMeasuremtents.data();
    m_plot.values.count = static_cast<int>(m_TimeMeasuremtents.size());

    m_plot.scale.min = 0;
    m_plot.scale.max = largestnumber;

    m_plot.tooltip.show = true;
    m_plot.tooltip.format = "x=%.2f, y=%.2f";
    //m_plot.grid_x.show = true;
    //m_plot.grid_y.show = true;
    m_plot.frame_size = ImVec2(300, 300);
    m_plot.line_thickness = 1.f;
    m_plot.tooltip.show = true;
}
