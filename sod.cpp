#include "sod.h"
// Phase 15 - Comment out the following
// Phase 16 - Uncomment
#include "rocket.h"
// Use the following temporarily
#include "player.h"

/*
	SOD.CPP

	The CSodEnemy class implementation

	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: 3/30/2001
	Description:

*/

void CSodEnemy::OnCollision(CObject *collisionObject)
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
			///// -- Adam

			if (!static_cast<CRocket*>(collisionObject)->hitTarget)
			{//If the rocket hits the enemy, make it so it only takes damage once
				if(hitPoints > 0)
				{
					if(static_cast<CRocket*>(collisionObject)->isRocket == true)
					{
						hitPoints -= 50;//minus 10 health
					}
					else
					{
						hitPoints -= 1;
					}
				}

				if (hitPoints <= 0)
				{
					///// -- Adam
					
					// kill the ogre
					aiState = AI_DEAD;
					velocity = CVector(0.0, 0.0, 0.0);

					///// -- Adam
				}
				static_cast<CRocket*>(collisionObject)->hitTarget = true;
			}
				///// -- Adam
		}
	}
}

void CSodEnemy::OnPrepare() 
{
	///// -- Adam
	//float dirToPlayer;	// the angle of the enemy-player vector
	///// -- Adam

	CVector diff;		// the vector from the enemy to the player
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
	// if AI_SCARED, then MODEL_RUN
	switch (aiState)
	{
	case AI_SCARED:
		direction = (dirToPlayer - 90) + ((rand()%30)-15);		// set the direction of the enemy

			modelState = MODEL_RUN;
			velocity = CVector(0.0, 0.0, 15.0);
		break;
	case AI_UNCARING:
		direction = float(rand() % 360);
		if ((rand() % 3) != 0)
		{
			modelState = MODEL_IDLE;
			velocity = CVector(0.0, 0.0, 0.0);
		}
		else
		{
			modelState = MODEL_RUN;
			velocity = CVector(0.0, 0.0, 15.0);
		}
		break;
	case AI_DEAD:
		modelState = MODEL_DIE;
		velocity = CVector(0.0, 0.0, 0.0);
		if (nextFrame == stateStart)
			// time to kill the monster
		{
			isDead = true;
		}
		break;
	default:
		break;
	}

	// do prep for MD2 Model states
	CEntity::OnPrepare();
}

void CSodEnemy::Load()
{
	// load model
	CMD2Model::Load("models\\sodf8\\tris.md2", "models\\sodf8\\abarlith.pcx");
}

void CSodEnemy::OnProcessAI()
{
	// calculate distance from player
	CVector diff = player->position - position;

	if (aiState != AI_DEAD)
	{
		distFromPlayer = sqrt(diff.x*diff.x + diff.y*diff.y + diff.z*diff.z);
		if (distFromPlayer < 125.0)
			aiState = AI_SCARED;
		else
			aiState = AI_UNCARING;
	}
}
///// -- Adam
void CSodEnemy::OnDraw(CCamera *camera)
{
	CEntity::OnDraw(camera);

	glPushMatrix();
	//x is front and back on the model
	//y is left to right on the model
	//z is up and down on the model
	glTranslatef(0.0, 0.0, 25.0);//move it over their head
	glRotatef(direction - dirToPlayer, 0.0, 0.0, 1.0);	// the angle of the enemy-player vector
	glColor4f(0.0, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex3f(-15.0, 0, 0);
		glVertex3f(15.0, 0, 0);
		glVertex3f(15.0, 0, 5);
		glVertex3f(-15.0, 0, 5);
	glEnd();

	if (hitPoints >= 50)
		glColor4f(0.0, 1.0, 0.0, 1.0); // color -- green
	else if (hitPoints >= 25)
		glColor4f(1.0, 1.0, 0.0, 1.0); // color -- yellow
	else
		glColor4f(1.0, 0.0, 0.0, 1.0); // color -- red
	glBegin(GL_QUADS);
		glVertex3f(-14, -1, 1);
		glVertex3f((GLfloat)hitPoints / (GLfloat)maxHP * 28 - 14, -1, 1);
		glVertex3f((GLfloat)hitPoints / (GLfloat)maxHP * 28 - 14, -1, 4);
		glVertex3f(-14, -1, 4);
	glEnd();

	glPopMatrix();
}
///// -- Adam