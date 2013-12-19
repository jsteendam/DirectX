#pragma once

#include "D3DGraphics.h"
#include "GameState.h"
#include "GameEngine.h"

#include <memory>

class MainMenu : public GameState
{
private:
	std::shared_ptr<D3DGraphics> gfx;
	std::shared_ptr<GameEngine> game;

	double animation;
public:
	MainMenu(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game);
	~MainMenu(void);

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void Tick();
	void Draw();
};

