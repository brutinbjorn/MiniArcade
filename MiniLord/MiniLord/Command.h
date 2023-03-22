#pragma once
#include "SquareComponent.h"

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

class OpenSceneCommand final : public Command
{
public:
	OpenSceneCommand(const std::string& Scene):m_SSceneName(Scene){};
private:
	std::string m_SSceneName = {};

};

class SwapSquareColor final : public Command
{
public:
	SwapSquareColor(SquareComponent* square, const SDL_Color& colorToSwapTo):m_pSquare(square),m_ColorOn(colorToSwapTo),m_ColorOff (square->GetColor()){};
	SwapSquareColor(SquareComponent* square, const SDL_Color& colorWhenOff,const SDL_Color& colorWhenOn):m_pSquare(square),m_ColorOff(colorWhenOff),m_ColorOn(colorWhenOn){};
private:
	SquareComponent* m_pSquare = nullptr;
	SDL_Color m_ColorOn = {};
	SDL_Color m_ColorOff = {};
};