#include "stdafx.h"
#include "SceneJump.h"
#include "Framework.h"
#include "TextGo.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include <string>

#define BLOCKCOUNT	5

SceneJump::SceneJump()
	: Scene(SceneId::Game), halfWidth(FRAMEWORK.GetWindowSize().x / 2.f), halfHeight(FRAMEWORK.GetWindowSize().y / 2.f)
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
	
	// draw 오류 해결용도
	TextGo* titleGo = (TextGo*)FindGo("Title");
	titleGo->text.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));

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

	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		player->direction = { -1.f,0.f };
		player->HorizontalMovePlayer(dt);
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			sf::Vector2f v = { -1000.f,-1000.f };
			player->SetVelocity(v);
		}
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		player->direction = { 1.f,0.f };
		player->HorizontalMovePlayer(dt);
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			sf::Vector2f v = { 1000.f,-1000.f };
			player->SetVelocity(v);
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		sf::Vector2f v = { 0.f,-1000.f };
		player->SetVelocity(v);
	}

	player->VerticalMovePlayer(dt);

	CheckCollide();
}

void SceneJump::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneJump::CheckCollide()
{
	// 플레이어 객체, 바운드 반환
	Blocks* playerGo = (Blocks*)FindGo("Block4");
	sf::FloatRect playerBound = playerGo->block.getGlobalBounds();

	// 볼록 객체(3 빼고), 바운드 반환 => 충돌 시 플레이어 위치 세팅
	for (int i = 0; i < BLOCKCOUNT-1; i++)
	{
		std::string num = std::to_string(i);
		Blocks* blockGo = (Blocks*)FindGo("Block"+num);
		sf::FloatRect blockBound = blockGo->block.getGlobalBounds();

		if (playerBound.intersects(blockBound))
		{
			std::cout << "123" << std::endl;
			playerGo->speed = 0;
		}
	}

	//Blocks* blockGo1c = (Blocks*)FindGo("Block0");
	//sf::FloatRect blockBound1 = blockGo1c->block.getGlobalBounds();
	//Blocks* blockGo2c = (Blocks*)FindGo("Block1");
	//sf::FloatRect blockBound1 = blockGo2c->block.getGlobalBounds();
	//Blocks* blockGo3c = (Blocks*)FindGo("Block2");
	//sf::FloatRect blockBound1 = blockGo3c->block.getGlobalBounds();
	//Blocks* blockGo4c = (Blocks*)FindGo("Block3");
	//sf::FloatRect blockBound1 = blockGo4c->block.getGlobalBounds();
	//Blocks* playerGoc = (Blocks*)FindGo("Block4");
	//sf::FloatRect playerBound = playerGoc->block.getGlobalBounds();

	//sf::Vector2f leftMax = { blockBound1.left + blockBound1.width, halfHeight*2.f };
	//sf::Vector2f RightMax = { blockBound1.left + blockBound1.width, halfHeight*2.f };

	//if (blockBound1.left + blockBound1.width >= playerBound.left)
	//{
	//	sf::Vector2f tempPosition = playerGoc->GetPosition();
	//	playerGoc->SetPosition(blockBound1.,tempPosition.y)
	//}
}