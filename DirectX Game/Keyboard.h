#pragma once

#include <iostream>

class Keyboard;

class KeyboardServer
{
	friend Keyboard;
	bool a_pressed;
	bool s_pressed;
	bool w_pressed;
	bool d_pressed;
public:
	KeyboardServer() {}

	void KeyDown(char character) {
		if(character == 'A')
			a_pressed = true;
		else if(character == 'S')
			s_pressed = true;
		else if(character == 'W')
			w_pressed = true;
		else if(character == 'D')
			d_pressed = true;
	}

	void KeyUp(char character) {
		if(character == 'A')
			a_pressed = false;
		else if(character == 'S')
			s_pressed = false;
		else if(character == 'W')
			w_pressed = false;
		else if(character == 'D')
			d_pressed = false;
	}
};

class Keyboard
{
private:
	const KeyboardServer& kServ;
public:
	Keyboard(const KeyboardServer& kServ);
	~Keyboard(void);
	
	bool isPressed(char character);
};

