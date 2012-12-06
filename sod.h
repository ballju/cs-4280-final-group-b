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

#ifndef __SOD_H
#define __SOD_H

/*
	SOD.H

	The CSodEnemy class

	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: 3/30/2001
	Description: The CSodEnemy represents the Sod model
			   enemy. This enemy is considered smarter,
			   but has weaker armor than the Ogre.

*/

#include "enemy.h"
#include "ogro.h"
#include <time.h>

class CSodEnemy : public CEnemy
{
protected:
	void OnProcessAI();
	void OnCollision(CObject *collisionObject);
	void OnPrepare();

	///// -- Adam
	void OnDraw(CCamera *camera);
	///// -- Adam

public:
	/*******************Faith Satterthwaite 11/27/2012**************************/
	CSodEnemy()
	{
		Load();
		hitTarget = false;
		attackPlayer = false;	//11/30/2012
	}
	/***************************************************************************/
	CSodEnemy(float x, float z) { position.x = x; position.z = z; Load(); }
	~CSodEnemy() {}

	void Load();
	
	/*******************Faith Satterthwaite 11/27/2012**************************/
	bool hitTarget;
	bool attackPlayer; //11/29/2012
	/***************************************************************************/
};


#endif