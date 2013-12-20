#include "Keyboard.h"

Keyboard::Keyboard(const std::shared_ptr<KeyboardServer>& kServ) :kServ(kServ)
{
}

Keyboard::~Keyboard(void)
{
}

bool Keyboard::isPressed(char character)
{
	return kServ->key_states[(int)(character)];
}