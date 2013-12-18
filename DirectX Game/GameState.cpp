#include "GameState.h"


void GameState::ChangeState(std::shared_ptr<GameEngine> game, std::shared_ptr<GameState> state)
{
	game->ChangeState(state);
}
