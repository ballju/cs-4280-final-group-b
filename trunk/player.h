#ifndef __PLAYER_H
#define __PLAYER_H

/*

	PLAYER.H

	The CPlayer class

	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: 3/30/2001
	Description:

*/

#include <typeinfo.h>
// Phase 19 - Uncomment the following
#include "DirectXAudio.h"
// Phase 15 - Begin
// Uncomment following
#include "sod.h"
#include "ogro.h"
// Phase 15 - End
// Phase 16 - Uncomment
#include "rocket.h"
#include "camera.h"
#include "object.h"
#include "terrain.h"

///// -- Adam
#define MAX_ENEMIES 10
///// -- Adam

class CPlayer : public CObject
{
private:
	CCamera *camera;
	CTerrain *terrain;
	// Phase 19 - Uncomment the following
	CDirectXAudio *audioSys;
	
protected:
	// Phase 14 - Take out until enemies are introduced
	// Phase 15 - Uncomment because enemies exist now

	void OnPrepare()
	{
		if (camera)
		{
			position = camera->position;		// the player stays with the camera
			direction = camera->yaw;
			pitch = camera->pitch;
		}
	}

public:
	float direction;	// direction player is facing (same as camera)
	float pitch;		// pitch of player's lookAt vector
	
	///// -- Adam
	int hp;
	float timer; // used for the rate of fire for the secondary weapon
	bool fireWeapon;// used for the rate of fire for the secondary weapon
	CEnemy *sod[MAX_ENEMIES], *ogro[MAX_ENEMIES];
	int sodIndex, ogroIndex, ammo;
	float recoveryTime;
	///// -- Adam
	float stamina;//TOM
	int maxStam;//TOM
	
	/*****************************Faith Satterthwaite 11/27/2012***************************/
	void OnCollision(CObject *collisionObject);
	/**************************************************************************************/

	CPlayer() 
	{ 
		size = 7.0f; camera = NULL; terrain = NULL; 
		// Phase 14 - Take these out for now
		// Phase 19 - Uncomment the following
		audioSys = NULL;
		///// -- Adam
		hp = 100;
		timer = 0;
		fireWeapon = false;//start off not shooting
		sodIndex = ogroIndex = ammo = 0;
		 recoveryTime = 0.0;
		///// -- Adam
	stamina=100;//TOM
	maxStam=100;//TOM
	}
	~CPlayer() {}

	void SetCamera(CCamera *c) { camera = c; }
	void DetachCamera() { camera = NULL; }

	void SetTerrain(CTerrain *t) { terrain = t; }
// Phase 14 - Take out until Rocket is introduced
// Phase 16 - Uncomment
	void FireWeapon();

	///// -- Adam
	void FireWeapon2();
	void setSod(CEnemy* s);
	void setOgro(CEnemy* o);
	void killSod(CEnemy* s);
	void killOgro(CEnemy* o);
	///// -- Adam

// Phase 14 - Take out until AudioSystem in introduced
// Phase 19 - Uncomment the following	
	void SetAudioSystem(CDirectXAudio *aSys) { audioSys = aSys; }
};

#endif