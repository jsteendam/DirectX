#include "InventoryBar.h"

InventoryBar::InventoryBar(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game)
	: gfx(gfx)
	, game(game)
	, selectedSlot(1)
{
}

InventoryBar::~InventoryBar(void)
{
}

void InventoryBar::Tick()
{
	//std::cout << selectedSlot << std::endl;
	for(int i = 0; i < nSlots; i++) {
		if(game->keyboard->isPressed(i + '1')) {
			selectedSlot = i;
			std::cout << i << std::endl;
		}
	}	
	if(game->mouse->WheelUp()) {
		if(selectedSlot > 0)
			selectedSlot--;
		else
			selectedSlot = nSlots - 1;
	}
	else if(game->mouse->WheelDown()) {
		if(selectedSlot < (nSlots - 1))
			selectedSlot++;
		else
			selectedSlot = 0;
	}
}

void InventoryBar::Draw()
{
	for(int i = 0; i < nSlots; i++) {
		gfx->DrawRect((i * 60 + 20), 20, 50, 50, 0xA4A4A4);
		if(selectedSlot == i) {
			gfx->DrawRect((i * 60 + 20) - 5, 15, 5, 60, 0x555555);
			gfx->DrawRect((i * 60 + 20) + 50, 15, 5, 60, 0x555555);
			gfx->DrawRect((i * 60 + 20), 15, 50, 5, 0x555555);
			gfx->DrawRect((i * 60 + 20), 70, 50, 5, 0x555555);
			gfx->DrawRect((i * 60 + 20), 20, 50, 50, 0xA4A4A4A4);
		}
	}
}
