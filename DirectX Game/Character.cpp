#include "Character.h"
#include "D3DGraphics.h"

Character::Character(std::shared_ptr<D3DGraphics> gfx) : gfx(gfx), x(5), y(5), width(5)
{

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

void Character::Jump()
{

}

void Character::Tick()
{

}

void Character::Draw()
{
	gfx->DrawDisc(x, 600-y, width, 100, 100, 255);
}