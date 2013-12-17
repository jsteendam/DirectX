#include "Level.h"

Level::Level(std::shared_ptr<D3DGraphics> gfx) : gfx(gfx)
{
}

Level::~Level(void)
{
}

void Level::Draw()
{
	gfx->Clear(0xFF00FF);
}