#include "GameEngine.h"
#include "GameState.h"

#include <iostream>
#include <memory>
#include <cmath>

GameEngine::GameEngine(const KeyboardServer& kServer, const MouseServer& mServer, const std::shared_ptr<D3DGraphics>& gfx) : m_running(false), gfx(gfx) , TICK_TIME(1000.0/TICKS), FRAME_TIME(1000.0/FRAMES)
{
	keyboard = std::make_shared<Keyboard>(kServer);
	mouse = std::make_shared<Mouse>(mServer);

	console = std::make_shared<Console>();
	console->Init();
		
	fpsTimer.Start();
	tpsTimer.Start();
	frameTimer.Start();
	tickTimer.Start();
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
	Timer tim;
	tim.Start();
	Sleep(100);
	double b = tim.GetTimePassed();

	// Time FPS
	if(fpsTimer.GetTimePassed() >= 1000.0) {
		std::cout << frames << " fps" << std::endl;
		frames = 0;
		fpsTimer.Restart();
	}

	// Time TPS
	if(tpsTimer.GetTimePassed() >= 1000.0) {
		std::cout << ticks << " tps" << std::endl;
		ticks = 0;
		tpsTimer.Restart();
	}
	
	// Tick
	if(tickTimer.GetTimePassed() >= TICK_TIME) {
		tickTimer.Restart();
		ticks++;
		Tick();
	}

	// Draw
	if(frameTimer.GetTimePassed() >= FRAME_TIME) {
		frameTimer.Restart();
		gfx->BeginFrame();
		frames++;
		Draw();
		gfx->EndFrame();
	}

	float tickDifference = TICK_TIME - tickTimer.GetTimePassed();
	float frameDifference = FRAME_TIME - frameTimer.GetTimePassed();
	auto aksld = frameTimer.GetTimePassed();
	auto aksasdfld = tickTimer.GetTimePassed();
	auto min = min(tickDifference, frameDifference);
	if(min > 0)
		Sleep(min);
	else
		std::cout << "Halp!" << std::endl;
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