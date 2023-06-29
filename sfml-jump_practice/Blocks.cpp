#include "stdafx.h"
#include "Blocks.h"
#include "Framework.h"

Blocks::Blocks(const std::string n)
	: GameObject(n), direction(0.f,0.f), speed(300.f), velocity(0.f,0.f), gravity(0.f, 2000.f)
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
		block.setFillColor(sf::Color::Green);
		break;
	case 3:
		block.setSize(sf::Vector2f(182.f, halfHeight));
		SetOrigin(Origins::BR);
		SetPosition(FRAMEWORK.GetWindowSize().x, FRAMEWORK.GetWindowSize().y);
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

void Blocks::SetVelocity(sf::Vector2f v)
{
	velocity = v;

	//velocity += gravity * dt
	//SetPosition(block.getPosition() + velocity * dt); // 여기에 넣으면 getKeyDown 한번 할 때 setPosition 한번만 됨
}

void Blocks::MovePlayer(float dt)
{
	// 좌우 이동
	sf::Vector2f tempPosition = block.getPosition();
	tempPosition.x += direction.x * speed * dt;

	// 상하 이동
	if (velocity == sf::Vector2f{ 0.f,0.f })
	{
		velocity = { 0.f,0.f };
	}
	else
	{
		velocity += gravity * dt;
	}

	block.setPosition(tempPosition + velocity * dt);
}

void Blocks::CheckBlockCollide(Blocks* blockGo)
{
	sf::FloatRect playerBound = block.getGlobalBounds(); // 플레이어 객체 바운드
	sf::FloatRect blockBound = blockGo->block.getGlobalBounds(); // 블록 객체 바운드
	sf::FloatRect tempRect;
	topBlockCollide = false;

	if (playerBound.intersects(blockBound, tempRect))
	{
		if (tempRect.width > tempRect.height)
		{
			if (playerBound.top == tempRect.top) // bottom
			{
				block.setPosition(block.getPosition().x, blockBound.top + blockBound.height + 50.f);
				velocity = { 0.f, 100.f };
			}
			else if (playerBound.top < tempRect.top) // top
			{
				block.setPosition(block.getPosition().x, blockBound.top);
				velocity = { 0.f, 100.f };
				topBlockCollide = true;
			}
		}
		else if (tempRect.width < tempRect.height)
		{
			if (playerBound.left == tempRect.left) // right
			{
				block.setPosition(blockBound.left+blockBound.width + 25.f, block.getPosition().y);
			}
			else if (playerBound.left < tempRect.left) // left
			{
				block.setPosition(blockBound.left - 25.f, block.getPosition().y);
			}
		}
	}
}

void Blocks::SCheckBlockCollide(Blocks* blockGo)
{
	sf::FloatRect playerBound = block.getGlobalBounds(); // 플레이어 객체 바운드
	sf::FloatRect blockBound = blockGo->block.getGlobalBounds(); // 블록 객체 바운드
	sf::FloatRect tempRect;
	topBlockCollide = false;

	// 김혜준
	//if (playerBound.intersects(blockBound, tempRect))
	//{
	//	if (tempRect.width > tempRect.height) // 상 하 충돌
	//	{
	//		bool asdasd = false;
	//		asdasd = playerBound.top+playerBound.height >= tempRect.top;
	//			if (asdasd) // bottom
	//			{
	//				topBlockCollide = true;
	//				std::cout << "바텀충돌" << std::endl;
	//				velocity = { 0.f, -500.f }; // 올라가는 가속도 증가
	//				if ((playerBound.top + playerBound.height) <= tempRect.top)
	//					asdasd = false;
	//			}
	//	}
	//}

	// 김민지
	if (playerBound.intersects(blockBound, tempRect))
	{
		if (tempRect.width > tempRect.height) // 상 하 충돌 시
		{
			if (playerBound.top == tempRect.top) // bottom
			{
				std::cout << "아랫면" << std::endl;
				velocity = { 0.f, -500.f };
				//topBlockCollide = true;
			}

		}
			//if (playerBound.top + playerBound.height <= blockBound.top)
			//{
			//	std::cout << "윗면" << std::endl;
			//	block.setPosition(block.getPosition().x, blockBound.top);
			//	velocity = { 0.f, 100.f };
			//	topBlockCollide = true;
			//}
	}
}

void Blocks::CheckSideCollide()
{
	sf::FloatRect tempRect = block.getGlobalBounds();

	topSideCollide = tempRect.top <= 0.f;
	leftSideCollide = tempRect.left <= 0.f;
	rightSideCollide = tempRect.left + tempRect.width >= FRAMEWORK.GetWindowSize().x;
	bottomSideCollide = tempRect.top + tempRect.height >= FRAMEWORK.GetWindowSize().y;

	if (topSideCollide)
	{
		block.setPosition(block.getPosition().x, 50.f);
		velocity = { 0.f, 100.f };
	}

	if (bottomSideCollide)
	{
		block.setPosition(block.getPosition().x, FRAMEWORK.GetWindowSize().y);
		velocity = { 0.f, 0.f };
	}

	if (leftSideCollide)
	{
		block.setPosition(25.f, block.getPosition().y);
	}
	
	if (rightSideCollide)
	{
		block.setPosition(FRAMEWORK.GetWindowSize().x - 25.f, block.getPosition().y);
	}
}
