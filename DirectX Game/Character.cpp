#include "Character.h"
#include "D3DGraphics.h"

Character::Character(const std::shared_ptr<D3DGraphics>& gfx, const std::shared_ptr<GameEngine>& game)
	: gfx(gfx)
	, game(game)
	, width(30)
	, height(30)
	, x(50)
	, y(15)
	, isJumpingUp(false)
	, isFallingDown(false)
	, gravity(5.0)
	, jumpPower(15.0)
{
	inventoryBar = std::unique_ptr<InventoryBar>(new InventoryBar(gfx, game));
	staminaBar = std::unique_ptr<StaminaBar>(new StaminaBar(gfx, game));;
	healthBar = std::unique_ptr<HealthBar>(new HealthBar(gfx, game));
}

Character::~Character(void)
{
}

void Character::MoveRight()
{
	x+=5;
}

void Character::MoveLeft()
{
	x-=5;
}

void Character::SprintRight()
{
	x+=10;
}

void Character::SprintLeft()
{
	x-=10;
}

void Character::Tick()
{
	/** INVENTORY **/
	inventoryBar->Tick();

	/** STAMINA **/
	staminaBar->Tick();

	/** HEALTH **/
	healthBar->Tick();

	/** MOVEMENT **/
	if(game->keyboard->isPressed(VK_LSHIFT)) {
		if(game->keyboard->isPressed(VK_LEFT) | game->keyboard->isPressed('A'))
			SprintLeft();
		else if(game->keyboard->isPressed(VK_RIGHT) | game->keyboard->isPressed('D'))
			SprintRight();
	}
	else {
		if(game->keyboard->isPressed(VK_LEFT) | game->keyboard->isPressed('A'))
			MoveLeft();
		else if(game->keyboard->isPressed(VK_RIGHT) | game->keyboard->isPressed('D'))
			MoveRight();
	}

	/** JUMPING **/
	if(game->keyboard->isPressed(VK_SPACE) && !isJumpingUp && !isFallingDown) {
		isJumpingUp = true;
		jumpGoal = y+140;
	}

	/** GG PHYSICS **/
	if(isJumpingUp) {
		if(y < (jumpGoal - jumpPower)) {
			y += jumpPower;
		}
		else if(y < jumpGoal && y >= (jumpGoal - jumpPower)) {
			y = jumpGoal;
		}
		else if(y == jumpGoal) {
			isJumpingUp = false;
			isFallingDown = true;
		}
	}
	if(isFallingDown) {
		std::cout << y << ": ";
		if(y >= (height/2 + gravity)) {
			y -= gravity;
		}
		else if(y > height/2 && y < (height/2 + gravity)) {
			y = height/2;
		}
		else if(y == height/2) {
			isFallingDown = false;
		}
	}
}

void Character::Draw()
{
	/** INVENTORY **/
	inventoryBar->Draw();

	/** STAMINA **/
	staminaBar->Draw();

	/** HEALTH **/
	healthBar->Draw();

	/** DRAW SELF **/
	gfx->DrawRect(x-(width/2), 600-(y+(height/2)), width, height, 0x6464FF);
}