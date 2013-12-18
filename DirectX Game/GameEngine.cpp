#include "GameEngine.h"
#include "GameState.h"

#include <iostream>
#include <memory>
#include <cmath>

GameEngine::GameEngine(const KeyboardServer& kServer, const MouseServer& mServer, std::shared_ptr<D3DGraphics> gfx) : m_running(false), gfx(gfx)
{
	keyboard = std::make_shared<Keyboard>(kServer);
	mouse = std::make_shared<Mouse>(mServer);

	console = std::make_shared<Console>();
	console->Init();
		
	fpsTimer.StartWatch();
	tpsTimer.StartWatch();
	frameTimer.StartWatch();
	tickTimer.StartWatch();
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

	// Time TPS
	if(tpsTimer.GetTimeMilli() >= 1000.0) {
		std::cout << ticks << " tps" << std::endl;
		ticks = 0;
		tpsTimer.Restart();
	}
	
	// Tick
	if(tickTimer.GetTimeMilli() >= TICK_TIME) {
		ticks++;
		Tick();
		tickTimer.Restart();
		tickTimer.GetTimeMilli();
	}

	// Draw
	if(frameTimer.GetTimeMilli() >= FRAME_TIME) {
		gfx->BeginFrame();
		frames++;
		Draw();
		gfx->EndFrame();
		frameTimer.Restart();
	}

	float tickDifference = TICK_TIME - tickTimer.GetTimeMilli();
	float frameDifference = FRAME_TIME - frameTimer.GetTimeMilli();
	auto min = min(tickDifference, frameDifference);
	////std::cout << tickDifference << ", " << frameDifference << std::endl;
	if(frameDifference > tickDifference) {
		if(tickDifference > 0)
			Sleep(tickDifference);
		else
			tickTimer.Restart();
	}
	else {
		if(frameDifference > 0)
			Sleep(frameDifference);
		else
			frameTimer.Restart();
	}
}


void GameEngine::Tick()
{
	if(states.size() > 0)
		states[states.size()-1]->Tick();
}


void GameEngine::Draw()
{
	auto s = states.size();
	if(states.size() > 0)
		states[states.size()-1]->Draw();
}