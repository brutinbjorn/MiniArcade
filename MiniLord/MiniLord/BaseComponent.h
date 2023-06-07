#pragma once

#include <string>


namespace MiniLord
{
	class GameObject;

	class BaseComponent
	{
	public:
		friend class MiniLord::GameObject;

		virtual ~BaseComponent() = default;
		virtual void Initialize() = 0;
		virtual void FixedUpdate(const float ) = 0;
		virtual void Update(const float ) = 0;
		virtual void LateUpdate(const float ) = 0;
		virtual void Render() const = 0;

		virtual void GuiRender() {};
		

		//messages
		virtual bool Recieve(BaseComponent* ,const std::string&) {return false; };
	protected:
		BaseComponent() = default;
		MiniLord::GameObject* GetGameObject() const {return m_pParent; }
	private:
		MiniLord::GameObject* m_pParent = nullptr;

	};
}



