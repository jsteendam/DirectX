#include "D3DGraphics.h"

#include <math.h>
#include <assert.h>
#include <iostream>

D3DGraphics::D3DGraphics( HWND hWnd, int width, int height ) : width(width), height(height)
{
	HRESULT result;

	backRect.pBits = NULL;
	
	pDirect3D = Direct3DCreate9( D3D_SDK_VERSION );
	assert( pDirect3D != NULL );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp,sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

    result = pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,&d3dpp,&pDevice );
	assert( !FAILED( result ) );

	result = pDevice->GetBackBuffer( 0,0,D3DBACKBUFFER_TYPE_MONO,&pBackBuffer );
	
	assert( !FAILED( result ) );

	pSysBuffer = new D3DCOLOR[ width * height ];
}

D3DGraphics::~D3DGraphics()
{
	if( pDevice ) {
		pDevice->Release();
		pDevice = NULL;
	}
	if( pDirect3D ) {
		pDirect3D->Release();
		pDirect3D = NULL;
	}
	if( pBackBuffer ) {
		pBackBuffer->Release();
		pBackBuffer = NULL;
	}
	if( pSysBuffer )
	{
		delete pSysBuffer;
		pSysBuffer = NULL;
	}
}

void D3DGraphics::PutPixel( unsigned int x, unsigned int y, int r, int g, int b )
{
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < width );
	assert( y < height );
	pSysBuffer[x + y * width] = D3DCOLOR_XRGB( r,g,b );
}

void D3DGraphics::PutPixel( unsigned int x, unsigned int y, int color )
{
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < width );
	assert( y < height );
	pSysBuffer[x + y * width] = color;
}

void D3DGraphics::BeginFrame()
{
	memset( pSysBuffer,0xE0,sizeof( D3DCOLOR ) * width * height);
}

void D3DGraphics::EndFrame()
{
	HRESULT result;
	
	result = pBackBuffer->LockRect( &backRect,NULL,NULL );
	assert( !FAILED( result ) );

	for( int y = 0; y < height; y++ )
	{
		memcpy( &((BYTE*)backRect.pBits)[ backRect.Pitch * y ],&pSysBuffer[ width * y ],sizeof( D3DCOLOR ) * width );
	}

	result = pBackBuffer->UnlockRect();
	assert( !FAILED( result ) );

	result = pDevice->Present( NULL,NULL,NULL,NULL );
	assert( !FAILED( result ) );
}

void D3DGraphics::DrawDisc( int cx,int cy,int r,int rd,int g,int b )
{
	for( int x = cx - r; x < cx + r; x++ )
	{
		for( int y = cy - r; y < cy + r; y++ )
		{
			if( sqrt( (float)( (x - cx)*(x - cx) + (y - cy)*(y - cy) ) ) < r )
			{
				PutPixel( x,y,rd,g,b );
			}
		}
	}
}

void D3DGraphics::DrawLine( int x1,int y1,int x2,int y2,int r,int g,int blu )
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	if( dy == 0 && dx == 0 )
	{
		PutPixel( x1,y1,r,g,blu );
	}
	else if( abs( dy ) > abs( dx ) )
	{
		if( dy < 0 )
		{
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		float m = (float)dx / (float)dy;
		float b = x1 - m*y1;
		for( int y = y1; y <= y2; y = y + 1 )
		{
			int x = (int)(m*y + b + 0.5f);
			PutPixel( x,y,r,g,blu );
		}
	}
	else
	{
		if( dx < 0 )
		{
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		float m = (float)dy / (float)dx;
		float b = y1 - m*x1;
		for( int x = x1; x <= x2; x = x + 1 )
		{
			int y = (int)(m*x + b + 0.5f);
			PutPixel( x,y,r,g,blu );
		}
	}
}

void D3DGraphics::DrawCircle( int centerX,int centerY,int radius,int r,int g,int b )
{
	int rSquared = radius*radius;
	int xPivot = (int)(radius * 0.707107f + 0.5f);
	for( int x = 0; x <= xPivot; x++ )
	{
		int y = (int)(sqrt( (float)( rSquared - x*x ) ) + 0.5f);
		PutPixel( centerX + x,centerY + y,r,g,b );
		PutPixel( centerX - x,centerY + y,r,g,b );
		PutPixel( centerX + x,centerY - y,r,g,b );
		PutPixel( centerX - x,centerY - y,r,g,b );
		PutPixel( centerX + y,centerY + x,r,g,b );
		PutPixel( centerX - y,centerY + x,r,g,b );
		PutPixel( centerX + y,centerY - x,r,g,b );
		PutPixel( centerX - y,centerY - x,r,g,b );
	}
}

void D3DGraphics::DrawRect(int x, int y, int width, int height, D3DCOLOR color)
{
	for(int xx = x; xx < (x+width); xx++)
	{
		for(int yy = y; yy < (y+height); yy++)
		{
			PutPixel(xx, yy, color);
		}
	}
}

void D3DGraphics::Clear(D3DCOLOR color)
{
	DrawRect(0, 0, width, height, color);
}