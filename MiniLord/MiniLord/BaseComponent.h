#pragma once

#include <string>
namespace dae
{
	class GameObject;
}

class BaseComponent
{
public:
	virtual ~BaseComponent() = default;

	virtual void Initialize() = 0;
	virtual void FixedUpdate(const float ft) = 0;
	virtual void Update(const float dt) = 0;
	virtual void LateUpdate(const float lt) = 0;
	virtual void Render() const = 0;
	virtual void GuiRender() const {};

	//messages
	virtual bool Recieve(BaseComponent* ,const std::string&) {return false; };

protected:
	dae::GameObject* GetParent() const {return m_pParent; }
	BaseComponent() = default;

private:
	friend class dae::GameObject;
	dae::GameObject* m_pParent = nullptr;
};

