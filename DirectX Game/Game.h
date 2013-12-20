#pragma once

#include <memory>
#include <Windows.h>

#include "D3DGraphics.h"
#include "GameEngine.h"
#include "Keyboard.h"
#include "Mouse.h"

class Game
{
private:
	std::shared_ptr<D3DGraphics> gfx;
	std::shared_ptr<GameEngine> game;
public:
	Game(HWND hwnd, const std::shared_ptr<KeyboardServer>& kServ, const std::shared_ptr<MouseServer>& mServ, const int width, const int height);
	~Game(void);

	void Go();
};

