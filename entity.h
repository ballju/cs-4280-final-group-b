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

#ifndef __ENTITY_H
#define __ENTITY_H

/*
	ENTITY.H

	The CEntity class

	Author: Kevin Hawkins
	Date: 3/29/2001
	Description: The CEntity class is derived from CMD2Model and
			   provides the functionality of an entity in the
			   game world. It holds the current MD2 animation
			   state, the entity angle heading, and the entity's
			   primary sound.

*/

#include <stdlib.h>
#include <time.h>
#include <typeinfo.h>

#include "md2.h"
#include "object.h"
#include "camera.h"
// Phase 15 - Comment out the following
// Phase 19 - Uncomment the following
#include "DirectXAudio.h"
#include "terrain.h"

class CEntity : public CMD2Model
{
protected:
	void OnAnimate(float deltaTime);
	void OnDraw(CCamera *camera);
	void OnCollision(CObject *collisionObject);
	void OnPrepare();
// Phase 15 - Comment out the following
// Phase 19 - Uncomment the following
	void PlaySound() 
	{ 
		audioSys->PlaySoundDX(index); //call the audioSys playSoundDX method with the index associated with this object
	}

public:
	float direction;		// angle the entity is facing (in degrees)

// Phase 15 - Comment out the following
// Phase 19 - Uncomment the following
	
	CDirectXAudio *audioSys;	// a pointer to the audio system

	XACTINDEX index;			// used to hold the index of the sound associated with this index

	CEntity();
	~CEntity();

	int stateStart, stateEnd;	// state keyframe start/end
	float deltaT;
	float animSpeed;

// Phase 15 - Comment out the following
// Phase 19 - Uncomment the following
   void LoadAudio(XACTINDEX index);
   void SetAudioSystem(CDirectXAudio *asys) { audioSys = asys; }
};

#endif