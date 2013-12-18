#include "MainMenu.h"

MainMenu::MainMenu(std::shared_ptr<D3DGraphics> gfx, std::shared_ptr<GameEngine> game) : gfx(gfx), game(game)
{
	std::cout << "Level1 Constructor" << std::endl;
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
	//if(game->mouse->MouseInWindow())
	{
		std::cout << "(" << game->mouse->getMouseX() << ", " << game->mouse->getMouseY() << ")" << std::endl;
	}
}

void MainMenu::Draw()
{
	gfx->DrawRect(250, 0, 300, gfx->GetHeight(), 0xFFFFFF);
	gfx->DrawRect(300, 200, 200, 75, 0x000000);
}
