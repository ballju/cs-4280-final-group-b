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

public:
	COgroEnemy() { Load(); }
	COgroEnemy(float x, float z) { position.x = x; position.z = z; Load(); }
	~COgroEnemy() {}

	void Load();
};


#endif
