#include "Level2.h"

#include <iostream>

Level2::Level2(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game) : gfx(gfx), game(game)
{
	std::cout << "Level2 Constructor" << std::endl;
}

Level2::~Level2(void)
{
	std::cout << "Level2 Destructor" << std::endl;
}

void Level2::Init()
{
}

void Level2::Cleanup()
{
}

void Level2::Pause()
{
}

void Level2::Resume()
{
}

void Level2::Tick()
{
	if(game->keyboard->isPressed('d'))
	{
		game->PopState();
	}
}

void Level2::Draw()
{
	gfx->Clear(0xFF6464);
}
