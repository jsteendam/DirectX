#pragma once

#include "D3DGraphics.h"
#include "GameEngine.h"

#include <memory>

class HealthBar
{
private:
	std::shared_ptr<D3DGraphics> gfx;
	std::shared_ptr<GameEngine> game;

	double currentHealt;
	double maxHealth;
	double healRate;

	bool waitForRelease;
	bool fullHp;
public:
	HealthBar(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game);
	~HealthBar(void);

	void Tick();
	void Draw();
};

