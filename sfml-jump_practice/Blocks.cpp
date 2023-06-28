#include "stdafx.h"
#include "Blocks.h"

Blocks::Blocks(const std::string n)
	: GameObject(n)
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
