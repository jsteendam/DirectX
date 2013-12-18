#include "Level1.h"
#include "Level2.h"

#include <iostream>

Level1::Level1(std::shared_ptr<D3DGraphics> gfx, std::shared_ptr<GameEngine> game) : gfx(gfx), game(game)
{
	std::cout << "Level1 Constructor" << std::endl;
}

Level1::~Level1(void)
{
	std::cout << "Level1 Destructor" << std::endl;
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
	if(game->keyboard->isPressed('a'))
	{
		game->PushState(std::make_shared<Level2>(gfx, game));
	}
}

void Level1::Draw()
{
	gfx->DrawRect(200, 200, 100, 100, 0x6464FF);
}
