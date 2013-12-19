#include "MainMenu.h"

MainMenu::MainMenu(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game) : gfx(gfx), game(game)
{
	std::cout << "MainMenu Constructor" << std::endl;
	animation = 0.0;
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
	if(animation < gfx->GetHeight()) {
		animation+=25;
	}
	if(game->mouse->MouseInWindow()) {
		//std::cout << "(" << game->mouse->getMouseX() << ", " << game->mouse->getMouseY() << ")" << std::endl;
	}
	if(game->keyboard->isPressed('d')) {
		game->PopState();
	}
}

void MainMenu::Draw()
{
	if(animation < gfx->GetHeight())
		gfx->DrawRect(200, 0, 400, (int)(animation), 0xFFFFFF);
	else
		gfx->DrawRect(200, 0, 400, gfx->GetHeight(), 0xFFFFFF);
}
