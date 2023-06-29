#pragma once
#include "GameObject.h"

enum class COLLIDE
{
	NONE,
	TOPBLOCK,
	LEFTBLOCK,
	RIGHTBLOCK,
	BOTTOMBLOCK,
};

class Blocks :
    public GameObject
{
private:
public:
	sf::RectangleShape block;
	sf::Vector2f direction;
	float speed;
	sf::Vector2f velocity;
	sf::Vector2f gravity;
	bool topSideCollide;
	bool leftSideCollide;
	bool rightSideCollide;
	bool bottomSideCollide;
	bool topBlockCollide;

	Blocks(const std::string n);
	virtual ~Blocks() override;

	virtual void SetPosition(float x, float y) override;
	virtual void SetPosition(const sf::Vector2f p) override;

	virtual void SetOrigin(Origins origin) override;
	virtual void SetOrigin(float x, float y) override;

	virtual void Init() override;	// 생성자 new 역할
	virtual void Release() override;	// 소멸자 delete 역할

	virtual void Reset() override;	// 값 세팅

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetBlock(int num);
	void SetPlayer();
	void SetVelocity(sf::Vector2f v);

	void MovePlayer(float dt);
	void CheckBlockCollide(Blocks* blockGo);
	void CheckSideCollide();
};

