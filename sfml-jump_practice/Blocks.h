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

	virtual void Init() override;	// ������ new ����
	virtual void Release() override;	// �Ҹ��� delete ����

	virtual void Reset() override;	// �� ����

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetBlock(int num);
	void SetPlayer();
	void SetVelocity(sf::Vector2f v);

	void MovePlayer(float dt);
	void CheckBlockCollide(Blocks* blockGo);
	void CheckSideCollide();
};

