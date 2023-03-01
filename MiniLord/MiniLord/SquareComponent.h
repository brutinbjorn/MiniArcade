#pragma once
#include "BaseComponent.h"
class SquareComponent :
    public BaseComponent
{
public:
	SquareComponent(const SDL_Rect& rect, const SDL_Color& color = {255,255,255,255});
	~SquareComponent() override = default;
	SquareComponent(const SquareComponent& other) = delete;
	SquareComponent(SquareComponent&& other) noexcept = delete;
	SquareComponent& operator=(const SquareComponent& other) = delete;
	SquareComponent& operator=(SquareComponent&& other) noexcept = delete;

	void Initialize() override {};
	void FixedUpdate(const float) override {};
	void Update(const float) override{};
	void LateUpdate(const float) override {};
	void Render() const override;

private:
	SDL_Rect m_Rect = SDL_Rect{};
	SDL_Color m_color = SDL_Color{};
	glm::ivec2 m_offset = { 0,0 };

};

