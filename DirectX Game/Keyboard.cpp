#include "Keyboard.h"

Keyboard::Keyboard(const KeyboardServer& kServ) :kServ(kServ)
{
}

Keyboard::~Keyboard(void)
{
}

bool Keyboard::isPressed(char character)
{
	if(character == 'a')
		return kServ.a_pressed;
	else if(character == 's')
		return kServ.s_pressed;
	else if(character == 'w')
		return kServ.w_pressed;
	else if(character == 'd')
		return kServ.d_pressed;
	return false;
}