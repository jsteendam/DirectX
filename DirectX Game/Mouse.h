#pragma once

#include <memory>

class Mouse;

class MouseServer
{
private:
	friend Mouse;
	int mouseX;
	int mouseY;
	bool mouseLeftPressed;
	bool mouseRightPressed;
	bool isInWindow;

	bool wheelUp;
	bool wheelDown;
public:
	MouseServer() {
		int mouseX = 0;
		int mouseY = 0;
		bool mouseLeftPressed = false;
		bool mouseRightPressed = false;
		bool isInWindow = false;
	}
	
	void UpdateMousePosition(int x, int y) { mouseX = x; mouseY = y; }
	void LeftMouseButtonPressed() { mouseLeftPressed = true; }
	void LeftMouseButtonReleased() { mouseLeftPressed = false; }
	void RightMouseButtonPressed() { mouseRightPressed = true; }
	void RightMouseButtonReleased() { mouseRightPressed = false; }

	void WheelUp() { wheelUp = true; wheelDown = false; }
	void WheelDown() { wheelDown = true; wheelUp = false; }
	void WheelIdle() { wheelUp = wheelDown = false; }

	bool IsInWindow() { return isInWindow; }
	void OnEnter() { isInWindow = true; } 
	void OnExit() { isInWindow = false; }
};

class Mouse
{
private:
	std::shared_ptr<MouseServer> mServ;
public:
	Mouse(const std::shared_ptr<MouseServer>& mServ);
	~Mouse(void);
	
	int getMouseX() { return mServ->mouseX; }
	int getMouseY() { return mServ->mouseY; }
	bool mouseLeftPressed() { return mServ->mouseLeftPressed; }
	bool mouseRightPressed() { return mServ->mouseRightPressed; }
	bool MouseInWindow() { return mServ->isInWindow; }
	
	bool WheelUp() {
		bool tmp = mServ->wheelUp;
		if(tmp) {
			mServ->WheelIdle();
			return true;
		}
		else
			return false;
	}
	bool WheelDown() {
		bool tmp = mServ->wheelDown;
		if(tmp) {
			mServ->WheelIdle();
			return true;
		}
		else
			return false;
	}
};

