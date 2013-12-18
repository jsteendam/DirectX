#include "GameEngine.h"
#include "GameState.h"

#include <iostream>
#include <memory>

GameEngine::GameEngine(const KeyboardServer& kServer, const MouseServer& mServer, std::shared_ptr<D3DGraphics> gfx) : m_running(false), gfx(gfx)
{
	keyboard = std::make_shared<Keyboard>(kServer);
	mouse = std::make_shared<Mouse>(mServer);

	console = std::make_shared<Console>();
	console->Init();
		
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