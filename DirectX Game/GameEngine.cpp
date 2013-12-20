#include "GameEngine.h"
#include "GameState.h"

#include <iostream>
#include <iomanip>
#include <memory>
#include <cmath>

GameEngine::GameEngine(const std::shared_ptr<KeyboardServer>& kServer, const std::shared_ptr<MouseServer>& mServer, const std::shared_ptr<D3DGraphics>& gfx) : m_running(false), gfx(gfx) , TICK_TIME(1000.0/TICKS_PER_SECOND), FRAME_TIME(1000.0/FRAMES_PER_SECOND)
{
	keyboard = std::make_shared<Keyboard>(kServer);
	mouse = std::make_shared<Mouse>(mServer);

	console = std::make_shared<Console>();
	console->Init();
		
	performanceTimer.Start();
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


void GameEngine::PushState(const std::shared_ptr<GameState>& state)
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
	// Time FPS and TPS
	if(performanceTimer.GetTimePassed() >= 1000.0) {
		//std::cout << "FPS: " << std::setw(3) << frames << ", TPS: " << std::setw(3) << ticks << '\n';
		frames = 0;
		ticks = 0;
		performanceTimer.Restart();
	}
	
	// Tick
	if(tickTimer.GetTimePassed() >= TICK_TIME) {
		tickDelay = tickTimer.GetTimePassed() - TICK_TIME;
		tickTimer.Restart();
		ticks++;
		Tick();
	}

	// Draw
	if(frameTimer.GetTimePassed() >= FRAME_TIME) {
		frameDelay = frameTimer.GetTimePassed() - FRAME_TIME;
		frameTimer.Restart();
		gfx->BeginFrame();
		frames++;
		Draw();
		gfx->EndFrame();
	}

	double tickDifference = (TICK_TIME - tickDelay) - tickTimer.GetTimePassed();
	double frameDifference = (FRAME_TIME - frameDelay) - frameTimer.GetTimePassed();
	auto min = min(tickDifference, frameDifference);
	if(min > 0)
		Sleep(min);
	//else
		//std::cout << "Halp!" << std::endl;
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