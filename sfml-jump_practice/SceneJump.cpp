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
	// draw 오류 해결 용도
	resources.push_back(std::make_tuple(ResourceTypes::Font, "fonts/DS-DIGI.ttf"));
}

void SceneJump::Init()
{
	Release();

	// draw 오류 해결 용도
	AddGo(new TextGo("Title", "fonts/DS-DIGI.ttf"));

	for (int i = 0; i < BLOCKCOUNT; i++)
	{
		std::string num = std::to_string(i);
		AddGo(new Blocks("Block"+num)); // Block0~3까지 gameObjects에 추가
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
	
	// blockGo 세팅
	for (int i = 0; i < BLOCKCOUNT; i++)
	{
		std::string num = std::to_string(i);
		Blocks* blockGo = (Blocks*)FindGo("Block" + num);
		blockGo->SetBlock(i); // 블록 색상,크기,위치 세팅
	}

	// playerGo 세팅
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

	// 점프중인지 체크
	if (player->bottomSideCollide || player->topBlockCollide)
	{
		isJump = false;
	}
	else if (!player->bottomSideCollide && !player->topBlockCollide)
	{
 		isJump = true;
	}
	if (!isJump)
	{
		player->direction = { 0.f,0.f };
	}

	// 입력
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

	// 충돌 체크
	for (int i = 0; i < BLOCKCOUNT - 1; i++)
	{
		std::string num = std::to_string(i);
		Blocks* blockGo = (Blocks*)FindGo("Block" + num);

		if (i == 2)
		{
			player->SCheckBlockCollide(blockGo);
			if (player->topBlockCollide)
			{
				break;
			}
		}

		// else 처리하면, "Block2"가 블록 바닥 충돌 안 했을 때 다른 면 체크 불가
		player->CheckSideCollide();
		player->CheckBlockCollide(blockGo);
		if (player->topBlockCollide)
		{
			break;
		}
	}

	player->MovePlayer(dt);
}

void SceneJump::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}