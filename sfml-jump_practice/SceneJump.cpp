#include "stdafx.h"
#include "SceneJump.h"
#include "Framework.h"
#include "TextGo.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include <string>

#define BLOCKCOUNT	5

SceneJump::SceneJump()
	: Scene(SceneId::Game),
	halfWidth(FRAMEWORK.GetWindowSize().x / 2.f),
	halfHeight(FRAMEWORK.GetWindowSize().y / 2.f),
	tempPosition(0.f,0.f),
	isJump(false)
{
	// draw ���� �ذ� �뵵
	resources.push_back(std::make_tuple(ResourceTypes::Font, "fonts/DS-DIGI.ttf"));
}

void SceneJump::Init()
{
	Release();

	// draw ���� �ذ� �뵵
	AddGo(new TextGo("Title", "fonts/DS-DIGI.ttf"));

	for (int i = 0; i < BLOCKCOUNT; i++)
	{
		std::string num = std::to_string(i);
		AddGo(new Blocks("Block"+num)); // Block0~3���� gameObjects�� �߰�
	}

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneJump::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneJump::Enter()
{
	Scene::Enter();
	
	// draw ���� �ذ�뵵
	TextGo* titleGo = (TextGo*)FindGo("Title");
	titleGo->text.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));

	// blockGo ����
	for (int i = 0; i < BLOCKCOUNT; i++)
	{
		std::string num = std::to_string(i);
		Blocks* blockGo = (Blocks*)FindGo("Block" + num);
		blockGo->SetBlock(i); // ��� ����,ũ��,��ġ ����
	}

	// playerGo ����
	Blocks* playerGo = (Blocks*)FindGo("Block4");
	playerGo->SetPlayer();
}

void SceneJump::Exit()
{
	Scene::Exit();
}

void SceneJump::Update(float dt)
{
	Scene::Update(dt);

	Blocks* player = (Blocks*)FindGo("Block4");

	if (player->bottomSideCollide)
	{
		isJump = false;
	}
	else if (!player->bottomSideCollide)
	{
		isJump = true;
	}
	if (!isJump)
	{
		player->direction = { 0.f,0.f };
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		player->direction = { -1.f,0.f };
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			sf::Vector2f v = { -1000.f,-1000.f };
			player->SetVelocity(v);
		}
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		player->direction = { 1.f,0.f };
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			sf::Vector2f v = { 1000.f,-1000.f };
			player->SetVelocity(v);
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		player->direction = { 0.f,0.f };
		sf::Vector2f v = { 0.f,-1000.f };
		player->SetVelocity(v);
		player->MovePlayer(dt);
	}

	for (int i = 0; i < BLOCKCOUNT - 1; i++)
	{
		std::string num = std::to_string(i);
		Blocks* blockGo = (Blocks*)FindGo("Block" + num);

		player->CheckSideCollide();
		player->CheckBlockCollide(blockGo);
	}

	player->MovePlayer(dt);
}

void SceneJump::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

//COLLIDE SceneJump::CheckCollide()
//{
//	// �÷��̾� ��ü, �ٿ�� ��ȯ
//	Blocks* playerGo = (Blocks*)FindGo("Block4");
//	sf::FloatRect playerBound = playerGo->block.getGlobalBounds();
//
//	// ��� ��ü(3 ����), �ٿ�� ��ȯ => �ٿ��� �浹 üũ
//	for (int i = 0; i < BLOCKCOUNT-1; i++)
//	{
//		std::string num = std::to_string(i);
//		Blocks* blockGo = (Blocks*)FindGo("Block"+num);
//
//		if (playerBound.intersects(blockBound, tempRect))
//		{
//			if (tempRect.width > tempRect.height)
//			{
//				if (playerBound.top == tempRect.top)
//				{
//					playerGo->block.setPosition(playerGo->block.getPosition().x, tempRect.top + tempRect.height + 50.f);
//					playerGo->velocity = { playerGo->velocity.x, 500.f };
//
//					playerGo->gravity.y + 100.f;
//					playerGo->SetPosition(playerGo->GetPosition().x, tempRect.top + tempRect.height);
//					return COLLIDE::Bottom; // �浹 ������ ���
//				}
//				else if (playerBound.top > tempRect.top)
//				{
//					playerGo->SetPosition(playerGo->GetPosition().x, tempRect.top);
//					return COLLIDE::Top;
//				}
//			}
//			else if (tempRect.width < tempRect.height)
//			{
//				if (playerBound.left == tempRect.left)
//				{
//					playerGo->SetPosition(tempRect.left + tempRect.width + 25.f, playerGo->GetPosition().y);
//					return COLLIDE::Right;
//				}
//				else if (playerBound.left < tempRect.left)
//				{
//					playerGo->SetPosition(tempRect.left - 25.f, playerGo->GetPosition().y);
//					return COLLIDE::Left;
//				}
//			}
//		}
//	}
//	return COLLIDE::None;
//}