#pragma once
#include "BaseComponent.h"

namespace MiniLord
{
    class DemoImguiComponent :
        public BaseComponent
    {
    public:

        DemoImguiComponent() = default;
        ~DemoImguiComponent() = default;
        DemoImguiComponent(const DemoImguiComponent& other) = delete;
        DemoImguiComponent(DemoImguiComponent&& other) noexcept = delete;
        DemoImguiComponent& operator=(const DemoImguiComponent& other) = delete;
        DemoImguiComponent& operator=(DemoImguiComponent&& other) noexcept = delete;

        void Initialize() override {}
        void Update(const float) override {}
        void LateUpdate(const float) override {}
        void FixedUpdate(const float) override {}
        void Render() const override {}
        void GuiRender() override;
        
    };
}

