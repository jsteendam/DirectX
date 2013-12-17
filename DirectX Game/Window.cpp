#include <Windows.h>

#include "Keyboard.h"
#include "Mouse.h"
#include "Game.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

static KeyboardServer keyboardServer;
static MouseServer mouseServer;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) {
	case WM_KEYDOWN:
		keyboardServer.KeyDown(wParam);
		break;
	case WM_KEYUP:
		keyboardServer.KeyUp(wParam);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"Game";
	
    RegisterClassEx(&wc);

	RECT wr;
	wr.left = 950;
	wr.right = SCREEN_WIDTH + wr.left;
	wr.top = 150;
	wr.bottom = SCREEN_HEIGHT + wr.top;
	AdjustWindowRect( &wr,WS_OVERLAPPEDWINDOW,FALSE );

	HWND hWnd = CreateWindowEx(NULL, wc.lpszClassName, L"Game", WS_OVERLAPPEDWINDOW, wr.left,wr.top,wr.right-wr.left,wr.bottom-wr.top, NULL, NULL, hInstance, NULL);
	
	ShowWindow(hWnd, nCmdShow);
	
	// Init game
	std::shared_ptr<D3DGraphics> gfx = std::make_shared<D3DGraphics>(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	Game theGame(keyboardServer, mouseServer, gfx);

	// Start message pump
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Let the game class figure out what to do
			theGame.Go();
		}
	}

	UnregisterClass(L"Game", wc.hInstance);
	return 0;
}