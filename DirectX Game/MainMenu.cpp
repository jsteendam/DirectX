#include "MainMenu.h"

MainMenu::MainMenu(std::shared_ptr<D3DGraphics> gfx, std::shared_ptr<GameEngine> game) : gfx(gfx), game(game)
{
	std::cout << "Level1 Constructor" << std::endl;
	animation = 0.0;
}

MainMenu::~MainMenu(void)
{
	std::cout << "Level1 Destructor" << std::endl;
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
	if(game->mouse->MouseInWindow())
	{
		std::cout << "(" << game->mouse->getMouseX() << ", " << game->mouse->getMouseY() << ")" << std::endl;
	}
	if(game->keyboard->isPressed('d'))
	{
		game->PopState();
	}
	if(animation < gfx->GetHeight())
		animation+=12.5;
}

void MainMenu::Draw()
{
	if(animation > 0)
		gfx->DrawRect(200, 0, 400, (int)(animation), 0xFFFFFF);
}
