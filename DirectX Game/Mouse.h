#pragma once
class Mouse;

class MouseServer
{
private:
	friend Mouse;
public:
	MouseServer() {}
};

class Mouse
{
public:
	Mouse(void);
	~Mouse(void);
};

