#ifndef __ENEMY_H
#define __ENEMY_H

/*
	ENEMY.H

	The CEnemy class

	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: 3/30/2001
	Description: The CEnemy class

*/

#include "entity.h"
// Phase 15 - Comment out the following
// Phase 19 - Uncomment the following
#include "DirectXAudio.h"
#include "vector.h"

class CPlayer;
class CTerrain;

enum AIState_t
{
	AI_UNCARING,	// enemy is not scared and does not care
	AI_SCARED,	// enemy is scared and running away
	AI_DEAD,

	/**************************Faith Satterthwaite 11/27/2012************************/
	AI_ATTACK,	// enemy attacks player
	AI_BACKUP
	/*******************************************************************************/
};

class CEnemy : public CEntity
{
private:

protected:
     int hitPoints;           // hit points the enemy has left

	 ///// -- Adam
	 int maxHP;
	 float dirToPlayer;	// the angle of the enemy-player vector
	 bool beenShot;
	 ///// -- Adam
     
	 float distFromPlayer;    // distance this enemy is from player
     float runSpeed;          // speed of enemy when running
     AIState_t aiState;       // state of enemy thought

     virtual void OnProcessAI() {}

     void OnCollision(CObject *collisionObject)
     {
          // if this enemy collides with another enemy
          if (typeid(*collisionObject) == typeid(CEnemy))
          {
               modelState = MODEL_IDLE;
               velocity = CVector(0.0, 0.0, 0.0);
          }
          // if this enemy collides with the terrain (always)
          else if (typeid(*collisionObject) == typeid(CTerrain))
          {
               position.y = ((CTerrain*)collisionObject)->GetHeight(position.x, position.z) + size;
          }
          else
          {
          }
     }

	///// -- Adam
	void OnDraw(CCamera *camera) { CEntity::OnDraw(camera); }
	///// -- Adam

public:
     CPlayer *player;

     CEnemy() 
     {
          hitPoints = 100;    // start with 100 hit points
		  
		  ///// -- Adam
		  maxHP = 100;
		  dirToPlayer = 0;	// the angle of the enemy-player vector
		  beenShot = false; //not been shot yet
		  ///// -- Adam
          
		  isDead = false;     // enemy starts off alive
          velocity = CVector(0.0, 0.0, 0.0); // speed of enemy
          runSpeed = velocity.z;
          SetState(MODEL_IDLE);    // idle state
          direction = 0.0f;        // point north
          player = NULL;
     }

     ~CEnemy() {}

     void ProcessAI() { OnProcessAI(); }
     void SetPlayer(CPlayer *p) { player = p; }

	 ///// -- Adam
	 //This is needed for figuring out if the enemy is dead before putting them on the radar in gui.cpp
	 int getAIState() { return aiState; }
	 ///// -- Adam
};

#endif