#include "ogro.h"
// Phase 15 - Comment out the following
// Phase 16 - Uncomment
#include "rocket.h"
// Use the following temporarily
#include "player.h"

/*
	OGRO.CPP

	The COgroEnemy class implementation

	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: 3/30/2001
	Description:

*/

void COgroEnemy::OnCollision(CObject *collisionObject)
{
	// as long as the model is not dying, it can collide with other objects
	if (modelState != MODEL_DIE)
	{
		// if this enemy collides with another enemy
		if ((typeid(*collisionObject) == typeid(CSodEnemy)) ||
			(typeid(*collisionObject) == typeid(COgroEnemy)))
		{
			aiState = AI_UNCARING;
		}

		// if this enemy collides with the terrain (always)
		else	if (typeid(*collisionObject) == typeid(CTerrain))
		{
			position.y = ((CTerrain*)collisionObject)->GetHeight(position.x, position.z) + size;
	
			if (position.x <= ((CTerrain*)collisionObject)->GetScanDepth())
				position.x = ((CTerrain*)collisionObject)->GetScanDepth();
			if (position.x >= ((CTerrain*)collisionObject)->GetWidth()*((CTerrain*)collisionObject)->GetMul() - ((CTerrain*)collisionObject)->GetScanDepth())
				position.x = ((CTerrain*)collisionObject)->GetWidth()*((CTerrain*)collisionObject)->GetMul() - ((CTerrain*)collisionObject)->GetScanDepth();
			if (position.z <= ((CTerrain*)collisionObject)->GetScanDepth())
				position.z = ((CTerrain*)collisionObject)->GetScanDepth();
			if (position.z >= ((CTerrain*)collisionObject)->GetWidth()*((CTerrain*)collisionObject)->GetMul() - ((CTerrain*)collisionObject)->GetScanDepth())
				position.z = ((CTerrain*)collisionObject)->GetWidth()*((CTerrain*)collisionObject)->GetMul() - ((CTerrain*)collisionObject)->GetScanDepth();
		}
		// Phase 15 - Comment out the following
		// Phase 16 - Uncomment
		else if (typeid(*collisionObject) == typeid(CRocket))
		{
			// kill the ogre
			aiState = AI_DEAD;
			velocity = CVector(0.0, 0.0, 0.0);
		}
	}
}

void COgroEnemy::OnPrepare() 
{
     float dirToPlayer;  // the angle of the enemy-player vector

     CVector diff;       // the vector from the enemy to the player
     diff.x = position.x - player->position.x;
     diff.z = position.z - player->position.z;
     diff.Normalize();

     // find the angle in the world of the vector from the enemy to the player
     // in relation the negative z-axis
     dirToPlayer = RAD2DEG(diff.Angle(CVector(0,0,-1)));

     // seed random generator
     srand((unsigned int)time(NULL));

     ProcessAI();
     // now do Ogro prep
     // set modelState based on AIstate
     switch (aiState)
     {
     case AI_SCARED:
          direction = (dirToPlayer - 90) + ((rand()%90)-45);          // set the direction of the enemy
		  // -90 to 90 degrees
			modelState = MODEL_RUN;
			velocity = CVector(0.0, 0.0, 15.0);
          break;
     case AI_UNCARING:
          direction = float(rand() % 360);
          if ((rand() % 4) != 0)
          {
               modelState = MODEL_IDLE;
               velocity = CVector(0.0, 0.0, 0.0);
          }
          else
          {
              velocity = CVector(0.0, 0.0, 15.0);
              modelState = MODEL_RUN;
          }
          break;
     case AI_DEAD:
          modelState = MODEL_DIE;
          velocity = CVector(0.0, 0.0, 0.0);
          if (nextFrame == stateStart)
          {
               // time to kill the monster
               isDead = true;
          }
          break;
     default:
          break;
     }

     // do prep for MD2 Model states
     CEntity::OnPrepare();
}

void COgroEnemy::Load()
{
	// load model
	CMD2Model::Load("models\\ogro\\tris.md2", "models\\ogro\\ogrobase.pcx");
}

void COgroEnemy::OnProcessAI()
{
     // calculate distance from player
     CVector diff = player->position - position;

     if (aiState != AI_DEAD)
     {
          // if the player is close enough, the enemy should become scared
          distFromPlayer = sqrt(diff.x*diff.x + diff.y*diff.y + diff.z*diff.z);
          if (distFromPlayer < 100.0)
               aiState = AI_SCARED;
          else
               aiState = AI_UNCARING;
     }
}
