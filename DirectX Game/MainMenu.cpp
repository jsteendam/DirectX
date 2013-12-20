#include "MainMenu.h"
#include "Level2.h"

#include <Windows.h>

MainMenu::MainMenu(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game) : gfx(gfx), game(game)
{
	std::cout << "MainMenu Constructor" << std::endl;
	animation = 0.0;
	if(game->keyboard->isPressed(VK_ESCAPE)) {
		waitForRelease = true;
	}
	else {
		waitForRelease = false;
	}
}

MainMenu::~MainMenu(void)
{
	std::cout << "MainMenu Destructor" << std::endl;
}

void MainMenu::Init()
{
}

void MainMenu::Cleanup()
{
}

void MainMenu::Pause()
{
}

void MainMenu::Resume()
{
}

void MainMenu::Tick()
{
	if(animation < gfx->GetHeight() - 100) {
		animation+=50;
	}
	if(!game->keyboard->isPressed(VK_ESCAPE)) {
		waitForRelease = false;
	}
	if(!waitForRelease && game->keyboard->isPressed(VK_ESCAPE)) {
		game->PopState();
	}
}

void MainMenu::Draw()
{
	if(animation < gfx->GetHeight() - 100)
		gfx->DrawRect(150, 0, 400, (int)(animation), 0xFFFFFF);
	else
		gfx->DrawRect(150, 0, 400, gfx->GetHeight() - 100, 0xFFFFFF);
}
