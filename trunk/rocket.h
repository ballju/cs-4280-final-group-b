#ifndef __ROCKET_H
#define __ROCKET_H

/*
	
	FILENAME
	What is in this file?
	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: XX/XX/XXXX
	Description:

*/

#include "explosion.h"
#include "terrain.h"
#include "player.h"
#include "camera.h"
#include "object.h"
#include "vector.h"
//#include "sod.h"
//#include "ogro.h"

class CRocket : public CEntity
{
private:
	void SetupExplosionTexture();

protected:
	void OnAnimate(scalar_t deltaTime);
	void OnCollision(CObject *collisionObject);
	void OnDraw(CCamera *camera);
	void OnPrepare();

public:
	// direction rocket points
	float pitch;
	float distanceTravel;	// distance rocket has travelled
	CVector forward;		// forward vector of rocket (for pitch/dir)
	bool isExplosion;

	CTexture *explosionTex;
	CExplosion *explosion;

	CRocket();
	~CRocket();

	void Load();
	void Unload();

};

#endif