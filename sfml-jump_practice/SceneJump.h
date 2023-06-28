#pragma once
#include "Scene.h"
#include "Blocks.h"

class SceneJump : public Scene
{
private:
	int blockCount;
	std::vector<Blocks*> blockPool; // * ��� ��ü �޸�Ǯ

	float halfWidth;
	float halfHeight;

public:
	SceneJump();
	virtual ~SceneJump() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void CheckCollide();
	void MovePlayer(float dt);
	void MakeBlock();
};

