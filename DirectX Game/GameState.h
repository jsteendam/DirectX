#pragma once

#include "GameEngine.h"

#include <memory>

class GameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Tick() = 0;
	virtual void Draw() = 0;

	void ChangeState(std::shared_ptr<GameEngine> game, std::shared_ptr<GameState> state);
};