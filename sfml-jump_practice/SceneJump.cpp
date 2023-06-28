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

	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		player->direction = { -1.f,0.f };
		player->MovePlayer(dt);
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		player->direction = { 1.f,0.f };
		player->MovePlayer(dt);
	}
}

void SceneJump::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneJump::CheckCollide()
{
}

void SceneJump::MovePlayer(float dt)
{
}