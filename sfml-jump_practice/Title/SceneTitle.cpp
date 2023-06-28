#include "stdafx.h"
#include "SceneTitle.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SpriteGo.h"
#include "Framework.h"
#include "TextGo.h"

SceneTitle::SceneTitle() : Scene(SceneId::Title)
{
	// 이 클래스 안에서 생성, 소멸되기 때문에 매번 만들어줘야 함
	resources.push_back(std::make_tuple(ResourceTypes::Font, "fonts/DS-DIGI.ttf"));
}

void SceneTitle::Init()
{
	Release();

	AddGo(new TextGo("Title", "fonts/DS-DIGI.ttf"));

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneTitle::Enter()
{
	Scene::Enter();

	sf::Vector2f centerPos = FRAMEWORK.GetWindowSize(); // centerPos = 1280,720 이라서 아직 중앙X

	TextGo* titleGo = (TextGo*)FindGo("Title");
	titleGo->text.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));
	titleGo->text.setString("START TO PRESS ENTER");
	titleGo->text.setFillColor(sf::Color::White);
	titleGo->text.setCharacterSize(100);
	titleGo->SetOrigin(Origins::MC);
	titleGo->SetPosition(centerPos / 2.f);
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}