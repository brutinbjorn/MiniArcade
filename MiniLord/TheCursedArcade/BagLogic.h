#pragma once
#include "BaseComponent.h"

namespace MiniLord
{
	class BagLogic: public BaseComponent
	{
	public:
		BagLogic() = default;
		~BagLogic() = default;
		BagLogic(const BagLogic& other) = delete;
		BagLogic(BagLogic&& other) noexcept = delete;
		BagLogic& operator=(const BagLogic& other) = delete;
		BagLogic& operator=(BagLogic&& other) noexcept = delete;

		void Initialize() override;
		void FixedUpdate(const float) override;
		void Update(const float) override;
		void LateUpdate(const float) override;
		void Render() const override;

	};
	
}

