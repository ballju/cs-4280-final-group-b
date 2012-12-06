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

#ifndef __GUI_H
#define __GUI_H

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

/*
	
	GUI.H
	The GUI class interface
	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: 4/2/2001
	Description:

*/

#include <windows.h>
#include "font.h"
#include "texture.h"

///// -- Adam
#include "enemy.h"
#include "player.h"

#define MAX_ENEMIES 10
///// -- Adam

class CGUI
{
private:
	int minutesLeft, secondsLeft, millisecondsLeft;
	int enemiesLeft;

	CFont *font;
	CFont *crosshair;
	CFont *endText;

	///// -- Adam
	int height, width; // used to calculate aspect ratio in order to draw gui and then switch back to 3d
	CPlayer *player;
	//CEnemy *sod[MAX_ENEMIES], *ogro[MAX_ENEMIES];
	//int sodIndex, ogroIndex; // I moved this into the player class

	//CFont *ammo;
	///// -- Adam

public:
	CGUI();
	~CGUI();

	void SetCurrentTime(float timeLeft);
	void SetEnemiesLeft(int eLeft);
	void Draw();
	void Animate(float deltaTime);

	void DrawWinner();
	void DrawLoser();

	///// -- Adam
	void drawHealth(); // draws the player's health bar
	void drawStamina(); // draws the player's stamina bar
	void drawRadar(); // draw the radar screen on the HUD

	void setScreen(int w, int h); // set the screen whenever the screen changes (called from world class)

	void setPlayer(CPlayer* p);
	//void setSod(CEnemy* s);
	//void setOgro(CEnemy* o);
	bool gameOver;
	///// -- Adam
};


#endif