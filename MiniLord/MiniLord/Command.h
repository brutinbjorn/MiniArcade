#pragma once
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
	SwapSquareColor(const SquareComponent)
private:
	SwapSquareColor* m_pSquare;
};