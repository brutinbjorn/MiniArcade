#pragma once

#include "MiniLordPCH.h"
#include "BaseComponent.h"
#include "Transform.h"

namespace MiniLord
{
	class Texture2D;

	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent() = default;
		virtual ~RenderComponent() override;

		void Initialize() override {}; 
		void FixedUpdate(const float ) override {};
		void Update(const float) override {};
		void LateUpdate(const float ) override {};
		void Render() const override;


		//void SetPosition(float x, float y, float z = 0);
		//void SetPosition(glm::vec3 pos);
		void SetSize(int x, int y);
		void SetOffset(int x, int y);
		void SetRotation(double rot) { m_Rotation = rot; };
		void SetTexture(const std::string& filename, bool QuarryTexture = true);
		void SetTexture(Texture2D* texture2D, bool QuarryTexture = true);
		void SetSourceRect(SDL_Rect rect);

		glm::fvec2 GetTextureSize() const;


	protected:
		Texture2D* m_pTexture = nullptr;
		SDL_Rect* m_pSrcRect = nullptr;
		//Transform m_transform;

		bool m_IsSizeSet = false;
		bool m_IsBoundToOtherComp = false;
		glm::ivec2 m_Size{0,0};
		glm::vec2 m_offset{ 0,0 };
		double m_Rotation = 0.0;
	};

}
