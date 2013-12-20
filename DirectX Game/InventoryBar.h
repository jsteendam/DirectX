#pragma once

#include "D3DGraphics.h"
#include "GameEngine.h"

#include <memory>

class InventoryBar
{
private:
	std::shared_ptr<D3DGraphics> gfx;
	std::shared_ptr<GameEngine> game;
	
	static const int nSlots = 8;
	int selectedSlot;
public:
	InventoryBar(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game);
	~InventoryBar(void);

	void Tick();
	void Draw();
};

