// -----------------------------------------------------------------
//                      Learning Team B
//                      Members:
//                            Adam LeMmon
//                            Faith Satterthwaite
//                            Tom Fletcher
//                            Justin Ball
//                      CS 4280 – 11:30 am
//                      Final Project
//                      Dr. Rague
//                      Due: 12/06/12
//                      Version: 2.4
// -----------------------------------------------------------------
// We made five major improvements to this game
// 1) New controls
// 2) Enemy attack
// 3) HUD (heads up display)
// 4) Enemy health bars
// 5) New Weapon
// -----------------------------------------------------------------

#define WIN32_MEAN_AND_LEAN
#define WIN32_EXTRA_LEAN

#include "font.h"

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <gl/gl.h>

CFont::CFont()
{
	screenX = 0;
	screenY = 0;
	xpos = 0.0;
	ypos = 0.0;
	zpos = 0.0;
}

CFont::CFont(char *name, int size)
{
	screenX = 0;
	screenY = 0;
	xpos = 0.0;
	ypos = 0.0;
	zpos = 0.0;
	Build(name, size);
}

CFont::~CFont()
{
	glDeleteLists(callList, 96);
}

void CFont::Build(char *name, int size)
{
	HFONT hFont;	// font ID
	HDC hDC;		// device context

	hDC = wglGetCurrentDC();
	callList = glGenLists(96);

	if (_stricmp(name, "symbol") == 0)
	{
		hFont = CreateFont(-size, 0,0,0,FW_BOLD, FALSE, FALSE, FALSE, SYMBOL_CHARSET,
						OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
						FF_DONTCARE | DEFAULT_PITCH, name);
	}
	else
	{
		hFont = CreateFont(-size, 0,0,0,FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
					OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 
					FF_DONTCARE | DEFAULT_PITCH, name);
	}

	SelectObject(hDC, hFont);
	wglUseFontBitmaps(hDC, 32, 96, callList);
}

void CFont::Print(const char *str, ...)
{
	char text[256];
	va_list args;

	if (str == NULL)
		return;

	va_start(args, str);
		vsprintf(text, str, args);
	va_end(args);

	glPushMatrix();
	glColor4f(r, g, b, a);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1.0f);	// translate one unit into the screen
	if (xpos == 0.0 && ypos == 0.0 && zpos == 0.0)
		glRasterPos2i(screenX, screenY);
	else
		glRasterPos3f(xpos, ypos, zpos);

	glPushAttrib(GL_LIST_BIT);
		glListBase(callList - 32);
		glCallLists(static_cast<GLsizei>(strlen(text)), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
	glPopMatrix();
}

void CFont::ClearFont()
{
	glDeleteLists(callList, 96);
}
