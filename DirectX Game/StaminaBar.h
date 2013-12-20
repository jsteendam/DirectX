#pragma once

#include "D3DGraphics.h"
#include "GameEngine.h"

#include <memory>

class StaminaBar
{
private:
	std::shared_ptr<D3DGraphics> gfx;
	std::shared_ptr<GameEngine> game;

	double currentStamina;
	double maxStamina;
	double regenRate;
public:
	StaminaBar(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game);
	~StaminaBar(void);

	void Tick();
	void Draw();
};

