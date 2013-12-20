#include "StaminaBar.h"

StaminaBar::StaminaBar(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game)
	: gfx(gfx)
	, game(game)
	, currentStamina(200)
	, maxStamina(300)
	, regenRate(1.0)
{
}

StaminaBar::~StaminaBar(void)
{
}

void StaminaBar::Tick()
{
	// Tick
}

void StaminaBar::Draw()
{
	gfx->DrawRect(gfx->GetWidth()-200, gfx->GetHeight()-10, (200.0/maxStamina)*currentStamina, 10, 0x1111FF);
}
