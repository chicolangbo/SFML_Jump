#include "stdafx.h"
#include "Blocks.h"
#include "Framework.h"

Blocks::Blocks(const std::string n)
	: GameObject(n), direction(1.f,0.f), speed(500.f)
{
}

Blocks::~Blocks()
{
	
}

void Blocks::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	block.setPosition(position);
}

void Blocks::SetPosition(const sf::Vector2f p)
{
	position = p;
	block.setPosition(p);
}

void Blocks::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(block, origin);
	}
}

void Blocks::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	block.setOrigin(x, y);
}

void Blocks::Init()
{
}

void Blocks::Release()
{
}

void Blocks::Reset()
{
}

void Blocks::Update(float dt)
{
}

void Blocks::Draw(sf::RenderWindow& window)
{
	window.draw(block);
}

void Blocks::SetBlock(int num)
{
	float halfWidth = FRAMEWORK.GetWindowSize().x / 2.f;
	float halfHeight = FRAMEWORK.GetWindowSize().y / 2.f;

	SetActive(true);
	block.setFillColor(sf::Color::Cyan);

	switch (num)
	{
	case 0:
		block.setSize(sf::Vector2f(182.f, halfHeight));
		SetOrigin(Origins::BL);
		SetPosition(0.f, FRAMEWORK.GetWindowSize().y);
		break;
	case 1:
		block.setSize(sf::Vector2f(182.f, 100.f));
		SetOrigin(Origins::TL);
		SetPosition(364.f, halfHeight - 100.f);
		break;
	case 2:
		block.setSize(sf::Vector2f(182.f, 100.f));
		SetOrigin(Origins::TL);
		SetPosition(728.f, halfHeight - 100.f);
		break;
	case 3:
		block.setSize(sf::Vector2f(182.f, halfHeight));
		SetOrigin(Origins::BL);
		SetPosition(1092.f, FRAMEWORK.GetWindowSize().y);
		break;
	}
}

void Blocks::SetPlayer()
{
	float halfWidth = FRAMEWORK.GetWindowSize().x / 2.f;
	float halfHeight = FRAMEWORK.GetWindowSize().y / 2.f;

	SetActive(true);
	block.setFillColor(sf::Color::Yellow);
	block.setSize(sf::Vector2f(50.f, 50.f));
	SetOrigin(Origins::BC);
	SetPosition(halfWidth, FRAMEWORK.GetWindowSize().y);
}

void Blocks::MovePlayer(float dt)
{
	// �¿� �̵�
	sf::Vector2f tempPosition = GetPosition();
	tempPosition.x += direction.x * speed * dt;
	SetPosition(tempPosition);
}
