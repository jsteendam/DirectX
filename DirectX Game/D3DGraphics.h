#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class D3DGraphics
{
public:
	D3DGraphics( HWND hWnd,  int width, int height );
	~D3DGraphics();
	void PutPixel( unsigned int x, unsigned int y,int r,int g,int b );
	void PutPixel( unsigned int x, unsigned int y,int color );
	void DrawLine( int x1,int y1,int x2,int y2,int r,int g,int b );
	void DrawCircle( int cx,int cy,int radius,int r,int g,int b );
	void DrawDisc( int cx,int cy,int r,int rd,int g,int b );
	void DrawRect(int x, int y, int width, int height, D3DCOLOR color);
	void Clear(D3DCOLOR color);
	void BeginFrame();
	void EndFrame();
	
	int GetWidth() { return width; }
	int GetHeight() { return height; }
private:
	IDirect3D9*			pDirect3D;
	IDirect3DDevice9*	pDevice;
	IDirect3DSurface9*	pBackBuffer;
	D3DLOCKED_RECT		backRect;

	int width;
	int height;
};