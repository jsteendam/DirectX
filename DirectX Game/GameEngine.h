#pragma once

#include <vector>
#include <memory>

#include "Keyboard.h"
#include "Mouse.h"
#include "D3DGraphics.h"
#include "Timer.h"
#include "Console.h"

#define TICKS 120
#define FRAMES 60

class GameState;

class GameEngine
{
private:
	const float FRAME_TIME;
	const float TICK_TIME;

	std::shared_ptr<D3DGraphics> gfx;
	std::shared_ptr<Console> console;

	// FPS Timers
	unsigned int frames;
	unsigned int ticks;

	std::vector<std::shared_ptr<GameState>> states;
	bool m_running;
	bool tmp;
	
	Timer fpsTimer;
	Timer tpsTimer;
	Timer frameTimer;
	Timer tickTimer;
public:
	std::shared_ptr<Keyboard> keyboard;
	std::shared_ptr<Mouse> mouse;

	GameEngine(const KeyboardServer& kServer, const MouseServer& mServer, const std::shared_ptr<D3DGraphics>& gfx);
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