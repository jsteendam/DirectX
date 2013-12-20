#include "Level1.h"
#include "Level2.h"
#include "MainMenu.h"

#include <iostream>

Level1::Level1(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game)
	: gfx(gfx)
	, game(game)
{
	character = std::unique_ptr<Character>(new Character(gfx, game));

	if(game->keyboard->isPressed(VK_ESCAPE)) {
		waitForRelease = true;
	}
	else {
		waitForRelease = false;
	}
}

Level1::~Level1(void)
{
}

void Level1::Init()
{
}

void Level1::Cleanup()
{
}

void Level1::Pause()
{
}

void Level1::Resume()
{
}

void Level1::Tick()
{
	character->Tick();

	if(!game->keyboard->isPressed(VK_ESCAPE)) {
		waitForRelease = false;
	}
	if(!waitForRelease && game->keyboard->isPressed(VK_ESCAPE))	{
		game->PushState(std::make_shared<MainMenu>(gfx, game));
		waitForRelease = true;
	}
}

void Level1::Draw()
{
	character->Draw();
}
