#include "player.h"

// Phase 14 - Take out until Rocket is introduced
// Phase 16 - Uncomment
void CPlayer::FireWeapon()
{
	///// -- Adam
	if(ammo > 0)
	{
	///// -- Adam
		// use camera->lookAt vector and multiply
		// this lookAt vector by the ammo's speed
		// to get the ammo velocity vector.
		// create the new ammo and attach it to
		// the world. fire the ammo

		CRocket *newRocket = new CRocket;

		newRocket->pitch = camera->pitch;
		newRocket->direction = direction;
		newRocket->position = position;
		newRocket->forward = camera->lookAt.UnitVector();
	// Phase 19 - Uncomment the following
		newRocket->SetAudioSystem(audioSys);
		newRocket->LoadAudio(audioSys->iExplode);
		newRocket->AttachTo(terrain);

		//// -- Adam
		ammo -= 1;
	}
	///// -- Adam
}

///// -- Adam
void CPlayer::FireWeapon2()
{
	// use camera->lookAt vector and multiply
	// this lookAt vector by the ammo's speed
	// to get the ammo velocity vector.
	// create the new ammo and attach it to
	// the world. fire the ammo

	CRocket *newRocket = new CRocket(1000.0); //It can't be faster than this or it goes through the enemies

	newRocket->pitch = camera->pitch;
	newRocket->direction = direction;
	newRocket->position = position;
	newRocket->forward = camera->lookAt.UnitVector();
// Phase 19 - Uncomment the following
	newRocket->SetAudioSystem(audioSys);
	newRocket->LoadAudio(audioSys->iExplode);
	newRocket->AttachTo(terrain);
}

//get a pointer to the sod // The array is used to keep track of all sods on the map in the radar screen
void CPlayer::setSod(CEnemy* s)
{
	sod[sodIndex] = s;
	sodIndex++;

	//ammo -- we want half as many rockets as total enemeies
	ammo++;
}

//get a pointer to the ogro // The array is used to keep track of all ogros on the map in the radar screen
void CPlayer::setOgro(CEnemy* o)
{
	ogro[ogroIndex] = o;
	ogroIndex++;
}

void CPlayer::killSod(CEnemy* s)
{
	for(int i = 0; i < MAX_ENEMIES; i++)
	{
		if (sod[i] == s)
		{
			sod[i] = 0;
			break;
		}
	}
}
void CPlayer::killOgro(CEnemy* o)
{
	for(int i = 0; i < MAX_ENEMIES; i++)
	{
		if (ogro[i] == o)
		{
			ogro[i] = 0;
			break;
		}
	}
}
///// -- Adam

/*********************************Faith Satterthwaite 11/27/2012*********************************/
void CPlayer::OnCollision(CObject *collisionObject)
{		
	// if Sod enemy collides with the player
	if (typeid(*collisionObject) == typeid(CSodEnemy))
	{
		///// -- Adam
		if (recoveryTime == 0) // make the player invicible for a moment after being hit
		{
			recoveryTime = .4;
		///// - Adam
			if(hp > 0)
				hp -= 10;	//minus 10 health
		///// - Adam
		}
		velocity = CVector(0.0, 0.0, 0.0);//stop when you hit an enemy
		acceleration = CVector(0.0, 0.0, 0.0);
		camera->acceleration = CVector(0.0, 0.0, 0.0);
		camera->velocity = CVector(0.0, 0.0, 0.0);
		///// - Adam
	}

	// if Ogro enemy collides with the player
	if (typeid(*collisionObject) == typeid(COgroEnemy))
	{
		///// -- Adam
		if (recoveryTime == 0) // make the player invicible for a moment after being hit
		{
			recoveryTime = .4;
		///// - Adam
			if(hp > 0)
				hp -= 20;	//minus 20 health
		///// - Adam
		}
		velocity = CVector(0.0, 0.0, 0.0);//stop when you hit an enemy
		acceleration = CVector(0.0, 0.0, 0.0);
		camera->acceleration = CVector(0.0, 0.0, 0.0);
		camera->velocity = CVector(0.0, 0.0, 0.0);
		///// - Adam
	}
}
/***********************************************************************************************/