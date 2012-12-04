#ifndef __WORLD_H
#define __WORLD_H

/*
	WORLD.H

  	The CWorld class

	Description: The CWorld class represents the game world
			   of the engine. All objects, the terrain,
			   audio system, ambient world music and sound,
			   and the camera are held here.


*/
// Begin - Phase 15
#include <typeinfo.h>
// End - Phase 15
// Begin - Phase 18
#include "gui.h"
// End - Phase 18
// Begin - Phase 14
#include "player.h"
// End - Phase 14
// Begin - Phase 15
#include "sod.h"
#include "ogro.h"
#include "entity.h"
#include "md2.h"
// End - Phase 15
#include "object.h"
#include "camera.h"
// Begin - Phase 12
#include "terrain.h"
// End - Phase 12
// Begin - Phase 19
#include "DirectXAudio.h"
// End - Phase 19
#include "tree.h"


// Begin - Phase 15
#define MAX_ENEMIES 10
// End - Phase 15

class CWorld
{
private:
	// Begin - Phase 15
	int numOgros, numSods;
	// End - Phase 15
	int screenWidth, screenHeight;
	bool gameDone;

protected:
	void OnAnimate(float deltaTime);
	void OnDraw(CCamera *camera);
	void OnPrepare();

public:
	///// -- Adam
	bool shift, w, s, a, d;
	bool sprint;
	///// -- Adam
	
	HWND hwnd;

	// Begin - Phase 12
	CTerrain *terrain;
	// End - Phase 12
	CCamera *camera;			// the camera
    // Begin - Phase 14
	CPlayer *player;
	// End - Phase 14
	// Begin - Phase 19
	CDirectXAudio *audioSystem;
	// End - Phase 19
	// Begin - Phase 18
	CGUI *gui;
	// End - Phase 18
	// Begin - Phase 15
	COgroEnemy *ogroEnemy;
	CSodEnemy *sodEnemy;
	// End - Phase 15
	float timeStart;
	float timeElapsed;

	CWorld();
	CWorld(CCamera *c);
	~CWorld();

	// initialize terrain, load objects and put in container
	void LoadWorld();
	void UnloadWorld();

	// Begin - Phase 15
	int CountObjectTypes(const type_info &classID);
	// End - Phase 15

	// do physics calculations for all objects in the world
	// including collisions
	void Animate(float deltaTime);

	// render all objects in the world
	void Draw(CCamera *camera);
	void Prepare() { OnPrepare(); }

	void FadeScreen();
	void SetScreen(int width, int height);

	bool IsGameDone() { return gameDone; }
	void QuitGame() { gameDone = true; }
	// Begin - Phase 15
	int GetOgros() { return numOgros; }
	int GetSods() { return numSods; }
	// End - Phase 15

};


#endif