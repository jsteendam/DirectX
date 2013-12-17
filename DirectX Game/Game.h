#pragma once

#include <Windows.h>

#include "Keyboard.h"
#include "Mouse.h"
#include "D3DGraphics.h"
#include "Character.h"
#include "Level.h"
#include "Timer.h"

#define FRAME_TIME 33.3333
#define TICK_TIME 33.3333

class Game
{
private:
	Keyboard* keyboard;
	Mouse* mouse;

	std::shared_ptr<D3DGraphics> gfx;

	Character* character;

	Level* level1;

	// FPS Timers
	unsigned int frames;

	Timer fpsTimer;
	Timer frameTimer;
	Timer tickTimer;
public:
	Game(const KeyboardServer& kServer, const MouseServer& mServer, std::shared_ptr<D3DGraphics> gfx);
	~Game(void);

	void Go(void);

	void Tick();
	void Draw();
};

