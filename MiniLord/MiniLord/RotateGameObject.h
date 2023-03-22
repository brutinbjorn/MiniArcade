#pragma once
#include "BaseComponent.h"

class RotateGameObject : public BaseComponent
{
public:
	
	RotateGameObject(float RotationSpeed, float distance);
	~RotateGameObject() override = default;

	// Inherited via BaseComponent
	virtual void Initialize() override {};
	virtual void FixedUpdate(const float) override {};
	virtual void Update(const float) override;
	virtual void LateUpdate(const float) override {};
	virtual void Render() const override {};
private:
	float m_RotationSpeed = 1.0f;
	float m_Distance = 10.f;
	float m_RotationDelta = 0.0f;
};

