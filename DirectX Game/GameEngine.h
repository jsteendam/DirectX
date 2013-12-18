#pragma once

#include <vector>
#include <memory>

#include "Keyboard.h"
#include "Mouse.h"
#include "D3DGraphics.h"
#include "Timer.h"

const float FRAME_TIME = 33.3333f;
const float TICK_TIME = 33.3333f;

class GameState;

class GameEngine
{
private:
private:
	//Mouse* mouse;

	std::shared_ptr<D3DGraphics> gfx;

	// FPS Timers
	unsigned int frames;

	std::vector<std::shared_ptr<GameState>> states;
	bool m_running;
	
	Timer fpsTimer;
	Timer frameTimer;
public:
	Keyboard* keyboard;

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