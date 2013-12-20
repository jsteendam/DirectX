#include "HealthBar.h"

HealthBar::HealthBar(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game)
	: gfx(gfx)
	, game(game)
	, currentHealt(80)
	, maxHealth(100)
	, healRate(1.0)
{
	waitForRelease = false;
	fullHp = false;
}

HealthBar::~HealthBar(void)
{
}

void HealthBar::Tick()
{
	if(currentHealt < (maxHealth - healRate)) {
		currentHealt+=healRate;
	}
	else if(currentHealt > (maxHealth - healRate) && currentHealt < maxHealth) {
		currentHealt = maxHealth;
	}
	else if(!fullHp) {
		fullHp = true;
		std::cout << "Full HP" << std::endl;
	}
	if(game->keyboard->isPressed('G') && !waitForRelease) {
		std::cout << "Ouch" << std::endl;
		fullHp = false;
		waitForRelease = true;
		currentHealt-=30;
	}
	else if(!game->keyboard->isPressed('G') && waitForRelease) {
		waitForRelease = false;
	}
}

void HealthBar::Draw()
{
	gfx->DrawRect(gfx->GetWidth()-200, gfx->GetHeight()-20, (200.0/maxHealth)*currentHealt, 10, 0xFF1111);
}