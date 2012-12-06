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

	///// -- Adam
	bool hitTarget;
	bool isRocket;
	///// -- Adam

	CTexture *explosionTex;
	CExplosion *explosion;

	CRocket();
	~CRocket();

	///// -- Adam
	CRocket(float s);
	///// -- Adam

	void Load();
	void Unload();

};

#endif