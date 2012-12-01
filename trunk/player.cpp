#include "player.h"

// Phase 14 - Take out until Rocket is introduced
// Phase 16 - Uncomment
void CPlayer::FireWeapon()
{
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
}

///// -- Adam
void CPlayer::FireWeapon2()
{
	// use camera->lookAt vector and multiply
	// this lookAt vector by the ammo's speed
	// to get the ammo velocity vector.
	// create the new ammo and attach it to
	// the world. fire the ammo

	CRocket *newRocket = new CRocket(1240.0);

	newRocket->pitch = camera->pitch;
	newRocket->direction = direction;
	newRocket->position = position;
	newRocket->forward = camera->lookAt.UnitVector();
// Phase 19 - Uncomment the following
	newRocket->SetAudioSystem(audioSys);
	newRocket->LoadAudio(audioSys->iExplode);
	newRocket->AttachTo(terrain);
}
///// -- Adam

/*********************************Faith Satterthwaite 11/27/2012*********************************/
void CPlayer::OnCollision(CObject *collisionObject)
{		
	// if Sod enemy collides with the player
	if (typeid(*collisionObject) == typeid(CSodEnemy))
	{
		if(hp > 0)
			hp -= .10;	//minus 10 health
	}

	// if Ogro enemy collides with the player
	if (typeid(*collisionObject) == typeid(COgroEnemy))
	{
		if(hp > 0)
			hp -= .20;	//minus 20 health
	}
}
/***********************************************************************************************/