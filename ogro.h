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

#ifndef __OGRO_H
#define __OGRO_H

/*
	OGRO.H

	The COgroEnemy class

	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: 3/30/2001
	Description: The COgroEnemy represents the Ogro model
			   enemy. This enemy is considered "dumb",
			   but has a thicker coat of armor.

*/

#include "enemy.h"
#include "sod.h"
#include <time.h>

class COgroEnemy : public CEnemy
{
protected:
	void OnProcessAI();
	void OnCollision(CObject *collisionObject);
	void OnPrepare();

	///// -- Adam
	void OnDraw(CCamera *camera);
	///// -- Adam

public:
	/*******************Faith Satterthwaite 12/1/2012**************************/
	COgroEnemy()
	{
		Load();
		bool hitTarget = false;
		bool attackPlayer = false;
	}
	/***************************************************************************/
	COgroEnemy(float x, float z) { position.x = x; position.z = z; Load(); }
	~COgroEnemy() {}

	void Load();
	
	/*******************Faith Satterthwaite 12/1/2012**************************/
	bool hitTarget;
	bool attackPlayer;
	/***************************************************************************/
};


#endif
