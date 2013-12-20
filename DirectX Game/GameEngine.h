#pragma once

#include <vector>
#include <memory>

#include "Keyboard.h"
#include "Mouse.h"
#include "D3DGraphics.h"
#include "Timer.h"
#include "Console.h"

#define TICKS_PER_SECOND 120
#define FRAMES_PER_SECOND 60

class GameState;

class GameEngine
{
private:
	const double FRAME_TIME;
	const double TICK_TIME;

	std::shared_ptr<D3DGraphics> gfx;
	std::shared_ptr<Console> console;

	// FPS Timers
	int frames;
	int ticks;

	double frameDelay;
	double tickDelay;

	std::vector<std::shared_ptr<GameState>> states;
	bool m_running;
	bool tmp;
	
	Timer performanceTimer;
	Timer frameTimer;
	Timer tickTimer;
public:
	std::shared_ptr<Keyboard> keyboard;
	std::shared_ptr<Mouse> mouse;

	GameEngine(const std::shared_ptr<KeyboardServer>& kServer, const std::shared_ptr<MouseServer>& mServer, const std::shared_ptr<D3DGraphics>& gfx);
	~GameEngine(void);

	void ChangeState(std::shared_ptr<GameState> state);
	void PushState(const std::shared_ptr<GameState>& state);
	void PopState();

	void Go();

	void Tick();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }
};