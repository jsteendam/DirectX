#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <memory>

#include "Game.h"
#include "D3DGraphics.h"
#include "Timer.h"

Game::Game(const KeyboardServer& kServer, const MouseServer& mServer, std::shared_ptr<D3DGraphics> gfx) : gfx(gfx)
{
	keyboard = new Keyboard(kServer);
	character = new Character(gfx);
	level1 =  new Level(gfx);

	AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;
		
	fpsTimer.StartWatch();
	tickTimer.StartWatch();
	frameTimer.StartWatch();
}


Game::~Game(void)
{
}

void Game::Go(void)
{
	// Time FPS
	if(fpsTimer.GetTimeMilli() >= 1000.0) {
		std::cout << frames << " fps" << std::endl;
		frames = 0;
		fpsTimer.Restart();
	}

	// Tick
	//if(tickTimer.GetTimeMilli() >= TICK_TIME) {
		Tick();
		//tickTimer.Restart();
	//}

	// Draw
	//if(frameTimer.GetTimeMilli() >= FRAME_TIME) {
		frameTimer.Restart();
		gfx->BeginFrame();
		Draw();
		gfx->EndFrame();
		float diffrence = FRAME_TIME - frameTimer.GetTimeMilli();
		if(diffrence > 0)
			Sleep(diffrence);
	//}
}

void Game::Tick(void)
{
	if(keyboard->isPressed('a') && (character->GetX() - character->GetWidth()) >= character->GetWidth())
		character->MoveLeft();
	if(keyboard->isPressed('d') && (character->GetX() + character->GetWidth()) < (gfx->GetWidth() - character->GetWidth()))
		character->MoveRight();
}

void Game::Draw(void)
{
	frames++;
	level1->Draw();
	character->Draw();
}