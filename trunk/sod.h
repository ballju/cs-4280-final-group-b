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

public:
	CSodEnemy() { Load(); }
	CSodEnemy(float x, float z) { position.x = x; position.z = z; Load(); }
	~CSodEnemy() {}

	void Load();
};


#endif