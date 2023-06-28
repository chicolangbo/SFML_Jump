#include "stdafx.h"
#include "SceneJump.h"
#include "Framework.h"

SceneJump::SceneJump()
	: Scene(SceneId::Game), blockCount(4), halfWidth(FRAMEWORK.GetWindowSize().x / 2.f), halfHeight(FRAMEWORK.GetWindowSize().y / 2.f)
{
}

void SceneJump::Init()
{
	Release();

	for (int i = 0; i < blockCount; i++)
	{
		blockPool.push_back(new Blocks("Block"));
	}

	//AddGo

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

	for (auto block : blockPool)
	{
		delete block;
		block = nullptr;
	}
	blockPool.clear();
}

void SceneJump::Enter()
{
	Scene::Enter();
	MakeBlock();
}

void SceneJump::Exit()
{
	Scene::Exit();
}

void SceneJump::Update(float dt)
{
	Scene::Update(dt);
}

void SceneJump::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	for (int i = 0; i < blockCount; i++)
	{
		window.draw(blockPool[i]->block);
	}
}

void SceneJump::CheckCollide()
{
}

void SceneJump::MovePlayer(float dt)
{
}

void SceneJump::MakeBlock()
{
	for (int i = 0; i < blockCount; i++)
	{
		blockPool[i]->SetActive(true);
		blockPool[i]->block.setFillColor(sf::Color::Cyan);
	}

	blockPool[0]->block.setSize(sf::Vector2f(182.f, halfHeight));
	blockPool[0]->SetOrigin(Origins::BL);
	blockPool[0]->SetPosition(0.f, FRAMEWORK.GetWindowSize().y);

	blockPool[1]->block.setSize(sf::Vector2f(182.f, 100.f));
	blockPool[1]->SetOrigin(Origins::TL);
	blockPool[1]->SetPosition(364.f, halfHeight - 100.f);

	blockPool[2]->block.setSize(sf::Vector2f(182.f, 100.f));
	blockPool[2]->SetOrigin(Origins::TL);
	blockPool[2]->SetPosition(728.f, halfHeight - 100.f);

	blockPool[3]->block.setSize(sf::Vector2f(182.f, halfHeight));
	blockPool[3]->SetOrigin(Origins::BL);
	blockPool[3]->SetPosition(1092.f, FRAMEWORK.GetWindowSize().y);
}
