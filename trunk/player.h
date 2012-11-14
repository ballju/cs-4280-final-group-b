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
void OnCollision(CObject *collisionObject)
	{
		if (typeid(*collisionObject) == typeid(CTerrain))
		{
			position.y = ((CTerrain*)collisionObject)->GetHeight(position.x, position.z) + size;
		}
		else if (typeid(*collisionObject) == typeid(COgroEnemy))
		{
			if (camera)
			{
				if (camera->velocity.z > 0.0)
					camera->velocity = CVector(0.0, 0.0, 0.0);
			}
		}
		else if (typeid(*collisionObject) == typeid(CSodEnemy))
		{
			if (camera)
			{
				if (camera->velocity.z > 0.0)
					camera->velocity = CVector(0.0, 0.0, 0.0);
			}
		}
		else if (typeid(*collisionObject) == typeid(CPlayer))
		{
		}
	}

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

	CPlayer() { size = 7.0f; camera = NULL; terrain = NULL; 
	// Phase 14 - Take these out for now
	// Phase 19 - Uncomment the following
	audioSys = NULL; }
	~CPlayer() {}

	void SetCamera(CCamera *c) { camera = c; }
	void DetachCamera() { camera = NULL; }

	void SetTerrain(CTerrain *t) { terrain = t; }
// Phase 14 - Take out until Rocket is introduced
// Phase 16 - Uncomment
	void FireWeapon();
// Phase 14 - Take out until AudioSystem in introduced
// Phase 19 - Uncomment the following	
	void SetAudioSystem(CDirectXAudio *aSys) { audioSys = aSys; }
};

#endif