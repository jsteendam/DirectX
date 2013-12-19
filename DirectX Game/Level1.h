#pragma once

#include "D3DGraphics.h"
#include "GameState.h"
#include "GameEngine.h"

#include <memory>

class Level1 : public GameState
{
private:
	std::shared_ptr<D3DGraphics> gfx;
	std::shared_ptr<GameEngine> game;
public:
	Level1(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game);
	~Level1(void);

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void Tick();
	void Draw();
};
