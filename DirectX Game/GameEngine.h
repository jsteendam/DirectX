#pragma once

#include <vector>
#include <memory>

#include "Keyboard.h"
#include "Mouse.h"
#include "D3DGraphics.h"
#include "Timer.h"
#include "Console.h"

const float FRAME_TIME = 33.3333f;
const float TICK_TIME = 33.3333f;

class GameState;

class GameEngine
{
private:

	std::shared_ptr<D3DGraphics> gfx;
	std::shared_ptr<Console> console;

	// FPS Timers
	unsigned int frames;

	std::vector<std::shared_ptr<GameState>> states;
	bool m_running;
	
	Timer fpsTimer;
	Timer frameTimer;
public:
	std::shared_ptr<Keyboard> keyboard;
	std::shared_ptr<Mouse> mouse;

	GameEngine(const KeyboardServer& kServer, const MouseServer& mServer, std::shared_ptr<D3DGraphics> gfx);
	~GameEngine(void);

	void ChangeState(std::shared_ptr<GameState> state);
	void PushState(std::shared_ptr<GameState> state);
	void PopState();

	void Go();

	void Tick();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }
};