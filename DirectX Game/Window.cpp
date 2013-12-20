#include <Windows.h>

#include "Keyboard.h"
#include "Mouse.h"
#include "Game.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

std::shared_ptr<KeyboardServer> keyboardServer = std::make_shared<KeyboardServer>();
std::shared_ptr<MouseServer> mouseServer = std::make_shared<MouseServer>();

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) {
	case WM_KEYDOWN:
		keyboardServer->KeyDown(wParam);
		break;
	case WM_KEYUP:
		keyboardServer->KeyUp(wParam);
		break;
	case WM_MOUSEMOVE: {
		int x = (short)LOWORD(lParam);
		int y = (short)HIWORD(lParam);
		if (x > 0 && x < 1100 && y > 0 && y < 800) {
			mouseServer->UpdateMousePosition(x, y);
			if (!mouseServer->IsInWindow()) {
				SetCapture(hwnd);
				mouseServer->OnEnter();
			}
		}
		else {
			if ( wParam & (MK_LBUTTON | MK_RBUTTON) ) {
				x = max( 0,x );
				x = min( SCREEN_WIDTH-1,x );
				y = max( 0,y );
				y = min( SCREEN_HEIGHT-1,y );
				mouseServer->UpdateMousePosition(x, y);
			}
			else {
				ReleaseCapture();
				mouseServer->OnExit();
				mouseServer->LeftMouseButtonReleased();
				mouseServer->RightMouseButtonReleased();
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
		SetFocus(hwnd);
		mouseServer->LeftMouseButtonPressed();
		break;
	case WM_RBUTTONDOWN:
		mouseServer->RightMouseButtonPressed();
		break;
	case WM_LBUTTONUP:
		mouseServer->LeftMouseButtonReleased();
		break;
	case WM_RBUTTONUP:
		mouseServer->RightMouseButtonReleased();
		break;
	case WM_MOUSEWHEEL:
		if((HIWORD(wParam) == 0x78))
			mouseServer->WheelUp();
		else if(HIWORD(wParam) == 0xff88)
			mouseServer->WheelDown();
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
	Game theGame(hWnd, keyboardServer, mouseServer, SCREEN_WIDTH, SCREEN_HEIGHT);

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