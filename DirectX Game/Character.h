#pragma once

#include <memory>

#include "D3DGraphics.h"
#include "Drawable.h"

class Character : Drawable
{
private:
	int x;
	int y;
	int height;
	int width;

	std::shared_ptr<D3DGraphics> gfx;
public:
	Character(std::shared_ptr<D3DGraphics> gfx);
	~Character(void);
	
	void MoveRight();
	void MoveLeft();
	void Jump();

	void Tick();
	void Draw();
	
	int GetX() { return x; }
	int GetY() { return y; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
};

