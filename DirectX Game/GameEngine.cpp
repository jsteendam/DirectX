#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <memory>

#include "GameEngine.h"
#include "GameState.h"


GameEngine::GameEngine(const KeyboardServer& kServer, const MouseServer& mServer, std::shared_ptr<D3DGraphics> gfx) : m_running(false), gfx(gfx)
{
	keyboard = new Keyboard(kServer);

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
	frameTimer.StartWatch();
}


GameEngine::~GameEngine(void)
{
}


void GameEngine::ChangeState(std::shared_ptr<GameState> state)
{
	if(states.size() > 0) {
		states.pop_back();
		states.push_back(state);
		state->Init();
	}
}


void GameEngine::PushState(std::shared_ptr<GameState> state)
{
	states.push_back(state);
	state->Init();
}


void GameEngine::PopState()
{
	if(states.size() > 0) {
		states.pop_back();
		if(states.size() == 0)
		{
			Quit();
		}
	}
}

void GameEngine::Go()
{
	// Time FPS
	if(fpsTimer.GetTimeMilli() >= 1000.0) {
		std::cout << frames << " fps" << std::endl;
		frames = 0;
		fpsTimer.Restart();
	}
	
	// Tick
	Tick();

	// Draw
	frameTimer.Restart();
	gfx->BeginFrame();
	frames++;
	Draw();
	gfx->EndFrame();

	float difference = FRAME_TIME - frameTimer.GetTimeMilli();
	if(difference > 0)
		Sleep(difference);
	else { /* Something went wrong, you should leave now */ }
}


void GameEngine::Tick()
{
	if(states.size() > 0)
		states[states.size()-1]->Tick();
}


void GameEngine::Draw()
{
	if(states.size() > 0)
		states[states.size()-1]->Draw();
}