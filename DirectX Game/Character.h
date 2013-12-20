#pragma once

#include "D3DGraphics.h"
#include "GameEngine.h"
#include "InventoryBar.h"
#include "StaminaBar.h"
#include "HealthBar.h"

#include <memory>

class Character
{
private:
	int x;
	int y;
	int height;
	int width;
	
	std::shared_ptr<D3DGraphics> gfx;
	std::shared_ptr<GameEngine> game;

	/** CHARACTER ITEMS **/
	std::unique_ptr<InventoryBar> inventoryBar;
	
	/** CHARACTER STATES **/
	std::unique_ptr<StaminaBar> staminaBar;
	std::unique_ptr<HealthBar> healthBar;

	bool isJumpingUp;
	bool isFallingDown;

	/** CHARACTER PHYSICS **/
	double gravity;
	double jumpPower;
	int jumpGoal;
public:
	Character(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game);
	~Character(void);
	
	void MoveRight();
	void MoveLeft();
	void SprintRight();
	void SprintLeft();

	void Tick();
	void Draw();
	
	int GetX() { return x; }
	int GetY() { return y; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
};

