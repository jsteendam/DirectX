#pragma once

#include <iostream>
#include <memory>

class Keyboard;

class KeyboardServer
{
	friend Keyboard;
	bool key_states[128];
public:
	KeyboardServer() {
		for(int i = 0; i < 128; i++)
			key_states[i] = false;
	}

	void KeyDown(char character) {
		//std::cout << "Down: " << character << "[" << ((int)(character)) << "]" << std::endl;
		key_states[(int)(character)] = true;
	}

	void KeyUp(char character) {
		key_states[(int)(character)] = false;
	}
};

class Keyboard
{
private:
	std::shared_ptr<KeyboardServer> kServ;
public:
	Keyboard(const std::shared_ptr<KeyboardServer>& kServ);
	~Keyboard(void);
	
	bool isPressed(char character);
};

