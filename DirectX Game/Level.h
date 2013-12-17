#pragma once

#include <memory>

#include "D3DGraphics.h"
#include "Drawable.h"

class Level : Drawable
{
private:
	
	std::shared_ptr<D3DGraphics> gfx;
public:
	Level(std::shared_ptr<D3DGraphics> gfx);
	~Level(void);

	void Draw();
};

