#include "world.h"

CWorld::CWorld()
{
// Begin - Phase 12
	terrain = new CTerrain(32, 0.5);
// End - Phase 12
}

CWorld::~CWorld()
{
	// Begin - Phase 18
	delete gui;
	// End - Phase 18
	// Begin - Phase 12
	delete terrain;
	terrain = NULL;
    // End - Phase 12
	// Begin - Phase 18
	gui = NULL;
	// End - Phase 18
	// Begin - Phase 19

	audioSystem = NULL;
}

CWorld::CWorld(CCamera *c)
{
	camera = c;
	// Begin - Phase 12
	terrain = new CTerrain(32, 1.0f);
	// End - Phase 12
	// Begin - Phase 14
	player = new CPlayer;
	// End - Phase 14
	// Begin - Phase 19
	audioSystem = new CDirectXAudio;
	// End - Phase 19
	// Begin - Phase 18
	gui = new CGUI;
	// End - Phase 18
	// Begin - Phase 16
	gameDone = false;
	// End - Phase 16
	// Begin - Phase 14
	player->AttachTo(terrain);
	player->SetCamera(camera);
	player->SetTerrain(terrain);
	// End - Phase 14
	// Begin - Phase 19
	audioSystem->PlaySoundDX(audioSystem->iAmbient);

	player->SetAudioSystem(audioSystem);
	// End - Phase 19
	LoadWorld();
	timeStart = 300.0;			// 300 seconds = 5 minutes
	timeElapsed = 0.0;
	// Begin - Phase 18
	gui->SetCurrentTime(timeStart);
	gui->SetEnemiesLeft(numOgros + numSods);
	// End - Phase 18
}

void CWorld::Animate(float deltaTime)
{
	// Phase 12 - Begin
	// Phase 13 - Add hardwired 7.0f for player size
	// Phase 14 - Add player-> size back to camera position
	// set camera height based on player position on terrain
	camera->position.y = terrain->GetHeight(camera->position.x, camera->position.z) + player->size;	
	
	if (camera->position.x <= terrain->GetScanDepth())
		camera->position.x = terrain->GetScanDepth();
	if (camera->position.x >= terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth())
		camera->position.x = terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth();
	if (camera->position.z <= terrain->GetScanDepth())
		camera->position.z = terrain->GetScanDepth();
	if (camera->position.z >= terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth())
		camera->position.z = terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth();

	terrain->Animate(deltaTime);   // animate terrain
	// Phase 12 - End
	// Phase 15 - Begin
	const type_info &ogro = typeid(COgroEnemy);  // get ogro typeid
	const type_info &sod = typeid(CSodEnemy);    // get sod typeid

	numOgros = CountObjectTypes(ogro);           // count ogros
	numSods = CountObjectTypes(sod);             // count sods
	// Phase 15 - End

	// Begin - Phase 18
	gui->SetEnemiesLeft(numOgros + numSods);
	gui->SetCurrentTime(timeStart - timeElapsed);
	// End - Phase 18

	///// -- Adam
	player->recoveryTime -= deltaTime;
	if (player->recoveryTime < 0)
		player->recoveryTime = 0;
	//set the player's timer from here so that the weapon can shoot every so often
	player->timer += deltaTime;
	//do a firing loop here // decrease this decimal to make the rate of fire speed up
	if (player->timer > .1) //if it's been enough time since we last fired
	{
		if (player->fireWeapon == true) // if the mouse button is down
			player->FireWeapon2();
		player->timer = 0;
	}
	///// -- Adam

	// Phase 16 - Begin
	if (!gameDone)
		timeElapsed += deltaTime;
	else
		timeElapsed = timeStart;
    // Phase 16 - End


}

void CWorld::FadeScreen()
{
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-5, -5, -3.0);
	glVertex3f(5, -5, -3.0);
	glVertex3f(5, 5, -3.0);
	glVertex3f(-5, 5, -3.0);
	glEnd();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void CWorld::SetScreen(int width, int height)
{
	screenWidth = width;
	screenHeight = height;

	///// -- Adam
	gui->setScreen(screenWidth, screenHeight);
	///// -- Adam
}

void CWorld::Draw(CCamera *camera)
{
	// Begin - Phase 12
	terrain->Draw(camera);
	// End - Phase 12
	// Begin - Phase 18
	gui->Draw();

	if (gameDone)
	{
		FadeScreen();
		if (numOgros + numSods <=0)
			gui->DrawWinner();
		else
			gui->DrawLoser();
	}
// End - Phase 18

}

void CWorld::OnPrepare()
{
	// Begin - Phase 12
	glClearColor(terrain->fogColor[0], terrain->fogColor[1], terrain->fogColor[2], terrain->fogColor[3]);
	terrain->Prepare();
	// End - Phase 12
	// Phase 15 - Begin
	//********************************Faith Satterthwaite 12/1/2012************************************/
	if ((numOgros + numSods <= 0) || (timeElapsed >= timeStart) || (player->hp <= 0))
	{
		gameDone = true;
		///// -- Adam
		player->fireWeapon = false; // stop firing your gun when the game is over
		///// -- Adam
	}
	/**************************************************************************************************/
	// Phase 15 - End
	
}


// LoadWorld()
// desc: initializes the world
void CWorld::LoadWorld()
{
	// Phase 15 - Begin
	int enemyIdx = 0;
	int rndInt = 0;

	numOgros = 0;
	numSods = 0;

	srand((unsigned int)time(NULL));
	
	rndInt = (rand() % (MAX_ENEMIES-4)) + 4;	// random # from 4 to MAX
	numOgros = numSods = rndInt;

	// generate ogros
	for (enemyIdx = 0; enemyIdx < numOgros; enemyIdx++)
	{
		ogroEnemy = new COgroEnemy();
		ogroEnemy->AttachTo(terrain);
		ogroEnemy->SetPlayer(player);
		// Phase 19 - Uncomment
		ogroEnemy->SetAudioSystem(audioSystem);
		ogroEnemy->position.x = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		ogroEnemy->position.y = 0.0f;
		//ogroEnemy->position.z = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		ogroEnemy->position.z = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul() - 220) + 220);
		///// -- Adam -- I changed this position x to make them appear 220 units off to the side so they won't generate on top of you
		
		///// -- Adam
		//gui->setOgro(ogroEnemy);
		player->setOgro(ogroEnemy);
		///// -- Adam
	}

	// generate sods
	for (enemyIdx = 0; enemyIdx < numSods; enemyIdx++)
	{
		sodEnemy = new CSodEnemy;
		sodEnemy->AttachTo(terrain);
		sodEnemy->SetPlayer(player);
		// Phase 19 - Uncomment
		sodEnemy->SetAudioSystem(audioSystem);
//		sodEnemy->LoadAudio(audioSystem, "chimes.wav", false);
		//sodEnemy->position.x = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		sodEnemy->position.x = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul() - 220) + 220);
		///// -- Adam -- I changed this position x to make them appear 220 units above so they won't generate on top of you
		sodEnemy->position.y = 0.0f;
		sodEnemy->position.z = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		
		///// -- Adam
		//gui->setSod(sodEnemy);
		player->setSod(sodEnemy);
		///// -- Adam
	}

		
  // Phase 15 - End

	///// -- Adam
	gui->setPlayer(player);
	///// -- Adam
}
// Phase 15 - Begin
// CountObjectTypes
// desc: counts the number of objects passed as classID in the hierarchy
int CWorld::CountObjectTypes(const type_info &classID)
{
	int count = 0;
	CObject *c1;
	CObject *c2;

	c1 = (CObject*)terrain->childNode;

	while (c1 != NULL)
	{
		c2 = c1;
		do
		{
			if (typeid(*c2) == classID)
				count++;
			c2 = (CObject*)c2->nextNode;
		} while (!c2->IsFirstChild());
//      Phase 19 - Remove the following
//		count--;

		c1 = (CObject*)c1->childNode;
	}

	return count;
}
// Phase 15 - End
