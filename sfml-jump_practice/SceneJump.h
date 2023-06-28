#pragma once
#include "Scene.h"
#include "Blocks.h"

enum class COLLIDE
{
	None,
	Left,
	Right,
	Top,
	Bottom
};

class SceneJump : public Scene
{
private:
	float halfWidth;
	float halfHeight;

	sf::Vector2f tempPosition;

public:
	SceneJump();
	virtual ~SceneJump() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	COLLIDE CheckCollide();
};

