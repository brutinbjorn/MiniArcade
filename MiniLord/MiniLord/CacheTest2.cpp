#include "MiniLordPCH.h"
#include "CacheTest2.h"

struct TestTransform
{
    float matrix[16] = {
        1,1,1,1,
        1,1,1,1,
        1,1,1,1
    };
};

struct TestGameObject3D
{
    TestTransform transform;
    int ID =0;
};

struct TestGameObject3DAlt
{
    TestTransform* transform;
    int ID = 0;
};


using namespace MiniLord;
void CacheTest2::Update(const float)
{
	if (m_ButtonTestOnePressed)
	{
		GenerateTestDataOne();
		m_TestOneHasRun = true;
	}
	if(m_ButtonTestTwoPressed)
	{
		GenerateTestDataTwo();
		m_TestTwoHasRun = true;
	}

}

void MiniLord::CacheTest2::GuiRender()
{
	ImGui::Begin("Trash the cache with Objects", nullptr);
	ImGui::SetWindowSize(ImVec2{ 600,400 });

	m_ButtonTestOnePressed = ImGui::Button("Test with transform var", { 200,30 });
	if (m_TestOneHasRun)
		ImGui::Plot("plot1", m_plotOne);
	m_ButtonTestTwoPressed = ImGui::Button("Test with tramsform pointer", { 200,30 });
	if (m_TestTwoHasRun)
		ImGui::Plot("plot1", m_PlotTwo);

	ImGui::End();
}

void MiniLord::CacheTest2::GenerateTestDataOne()
{
	const int amount = 10000000; //lowered a bit from trashthecache.
	//TestTransform* transforms = new TestTransform[amount];
	//TestGameObject3DAlt* GobjAlt = new TestGameObject3DAlt[amount];
	TestGameObject3D* Gobj = new TestGameObject3D[amount];

	for (size_t i = 0; i < amount; i++)
	{
		Gobj[i].transform.matrix[0] = 1;
	}

	m_TimeMeasuremtentsTestOne.clear();
	long largest = 0;
	//std::cout << "begin transform var" << std::endl;
	for (int stepSize = 1; stepSize < 1024; stepSize *= 2)
	{
		auto start = std::chrono::high_resolution_clock().now();
		for (int i = 0; i < amount; i += stepSize)
		{
			Gobj[i].transform.matrix[0] = 1;
		}
		auto end = std::chrono::high_resolution_clock().now();
		auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "operation took " << elapsed / 1000.f << " : ms at stepsize: " << std::to_string(stepSize) << std::endl;
		m_TimeMeasuremtentsTestOne.push_back(static_cast<float>(elapsed));

		if (largest < elapsed) largest = static_cast<long>(elapsed);
	}
	delete[] Gobj;

	m_plotOne.values.ys = m_TimeMeasuremtentsTestOne.data();
	m_plotOne.values.count = static_cast<int>(m_TimeMeasuremtentsTestOne.size());

	m_plotOne.scale.min = 0;
	m_plotOne.scale.max = static_cast<float>(largest);

	m_plotOne.tooltip.show = true;
	m_plotOne.tooltip.format = "x=%.2f, y=%.2f";
	//m_plot.grid_x.show = true;
	//m_plot.grid_y.show = true;
	m_plotOne.frame_size = ImVec2(300, 300);
	m_plotOne.line_thickness = 1.f;
	m_plotOne.tooltip.show = true;

}

void MiniLord::CacheTest2::GenerateTestDataTwo()
{
	const int amount = 10000000; //lowered a bit from trashthecache.
	TestTransform* transforms = new TestTransform[amount];
	TestGameObject3DAlt* GobjAlt = new TestGameObject3DAlt[amount];
	//TestGameObject3D* Gobj = new TestGameObject3D[amount];

	for (size_t i = 0; i < amount; i++)
	{
		GobjAlt[i].transform = &transforms[i];
		GobjAlt[i].transform->matrix[0] = 1;
	}

	m_TimeMeasuremtentsTestTwo.clear();
	long largest = 0;
	//std::cout << "begin transform pointers" << std::endl;
	for (int stepSize = 1; stepSize < 1024; stepSize *= 2)
	{
		auto start = std::chrono::high_resolution_clock().now();
		for (int i = 0; i < amount; i += stepSize)
		{
			(GobjAlt[i]).transform->matrix[0] = 1;
		}
		auto end = std::chrono::high_resolution_clock().now();
		auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "operation took " << elapsed / 1000.f << " : ms at stepsize: " << std::to_string(stepSize) << std::endl;
		m_TimeMeasuremtentsTestTwo.push_back(static_cast<float>(elapsed));

		if (largest < elapsed) largest = static_cast<long>(elapsed);
	}
	delete[] GobjAlt;
	delete[] transforms;

	m_PlotTwo.values.ys = m_TimeMeasuremtentsTestTwo.data();
	m_PlotTwo.values.count = static_cast<int>(m_TimeMeasuremtentsTestTwo.size());

	m_PlotTwo.scale.min = 0;
	m_PlotTwo.scale.max = static_cast<float>(largest);

	m_PlotTwo.tooltip.show = true;
	m_PlotTwo.tooltip.format = "x=%.2f, y=%.2f";
	//m_plot.grid_x.show = true;
	//m_plot.grid_y.show = true;
	m_PlotTwo.frame_size = ImVec2(300, 300);
	m_PlotTwo.line_thickness = 1.f;
	m_PlotTwo.tooltip.show = true;

}




