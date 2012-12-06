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

#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/Gl.h>
#include <gl/Glu.h>
#include <math.h>
#include "OGLWindow.h"

// disable implicit float-double casting
#pragma warning(disable:4305)

OGLWindow::OGLWindow()
{
}

OGLWindow::~OGLWindow()
{
}

bool OGLWindow::Init()
{   
	//sprint=false;//TOM
    // clear to black background
    glClearColor(0.0, 0.0, 0.0, 0.0);
	// Begin - Phase 6
	mouseSensitivity = 3.0f;
	// End - Phase 6
    m_angle = 0.0f;
	// Begin - Phase 5
	gameCamera = new CCamera;
	// End - Phase 5
	// Begin - Phase 11
	gameWorld = new CWorld(gameCamera);
	// End - Phase 11

	///// -- Adam
	gameWorld->SetScreen(m_windowWidth, m_windowHeight);
	///// - Adam

    return true;
}

bool OGLWindow::Shutdown()
{
	// Begin - Phase 11
	delete gameWorld;
	// Begin - Phase 5
	delete gameCamera;
	gameWorld = NULL;
	gameCamera = NULL;
	// End - Phase 5
	// End - Phase 11

    return true;
}

void OGLWindow::SetupProjection(int width, int height)
{
    if (height == 0)                    // don't want a divide by zero
    {
        height = 1;                 
    }

    glViewport(0, 0, width, height);        // reset the viewport to new dimensions
    glMatrixMode(GL_PROJECTION);            // set projection matrix current matrix
    glLoadIdentity();                       // reset projection matrix

    // calculate aspect ratio of window
    gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

    glMatrixMode(GL_MODELVIEW);             // set modelview matrix
    glLoadIdentity();                       // reset modelview matrix

    m_windowWidth = width;
    m_windowHeight = height;

	///// -- Adam
	//CWorld *world = OnGetWorld();
	//world->SetScreen(width, height);
	//gameWorld->SetScreen(width, height);
	//OnGetWorld()->SetScreen(width, height); // send the width and height to the world (used for the gui) Called from winmain class
	///// -- Adam
}
// Begin - Phase 17 Remove parameter
void OGLWindow::Prepare()
// End - Phase 17
{
	// Phase 11 - Move following two statements from Render
	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     
//	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
    m_angle += 0.1f;
}
// BEGIN - Phase 6
// GetMouseX()
// desc: get mouse cursor position in window
int OGLWindow::GetMouseX(LPARAM lParam)
{
	return LOWORD(lParam);
}

// GetMouseY()
// desc: get mouse cursor position in window
int OGLWindow::GetMouseY(LPARAM lParam)
{
	return HIWORD(lParam);
}

void OGLWindow::OnMouseMove(int x, int y)
{
	// Phase 8 - Update to azimuth and pitch control
	static float oldX;
	static float oldY;
	float mX, mY;
	float dx, dy;  // changes in mouse position

	int sizeX = this->m_windowWidth; // Used when controls are pegged
	int sizeY = this->m_windowHeight;

	mX = (float)x;
	mY = (float)y;

	dx = mX - oldX;
	dy = mY - oldY;

	// Phase 18 - Add gameDone logic
	if (!gameWorld->IsGameDone())
	{
	// Areas on screen where directional movement is pegged
	if( mX < 200)
	{
		//gameCamera->yaw -= 1.0f*mouseSensitivity;
		SetCursorPos(sizeX/2,sizeY/2);
	}
	if( mX > sizeX - 200)
	{
		//gameCamera->yaw += 1.0f*mouseSensitivity;
		SetCursorPos(sizeX/2,sizeY/2);
	}
	if( mY < 200)
	{
		//gameCamera->pitch += 1.0f*mouseSensitivity;
		SetCursorPos(sizeX/2,sizeY/2);
	}
	if( mY > sizeY - 200)
	{
		//gameCamera->pitch -= 1.0f*mouseSensitivity;
		SetCursorPos(sizeX/2,sizeY/2);
	}


	if (dx < 0)
		gameCamera->yaw -= 0.5f*mouseSensitivity;
	if (dx > 0)
		gameCamera->yaw += 0.5f*mouseSensitivity;
// The following four lines commented out for Phase 6
	// Uncommented for Phase 7
	if (dy < 0)
		gameCamera->pitch +=0.5f*mouseSensitivity;
	if (dy > 0)
		gameCamera->pitch -= 0.5f*mouseSensitivity;
	
	
	oldX=mX;
	oldY=mY;
	
	}
}

// End - Phase 6

// Begin - Phase 9
//TOM
void OGLWindow::OnKeyDown(int nVirtKey)
{
	// Phase 18 - Add gameDone logic
	if (!gameWorld->IsGameDone())
	{
		switch (nVirtKey)
		{
			//Begin - Phase 10
		case VK_SHIFT:
			if (gameWorld->shift == false)
			{
				gameWorld->shift = true;
				gameWorld->sprint = true;
			}
			break;
		case 0x57:
			gameWorld->w = true;
			break;
		case 0x53:
			gameWorld->s = true;
			break;
		case 0x44:
			gameWorld->d = true;
			break;
		case 0x41:
			gameWorld->a = true;
			break;
//		case VK_ESCAPE:
//			PostQuitMessage(0);
//			break;
			// End - Phase 10
		default:
			break;
		}
	}
}//TOM
// End - Phase 9

void OGLWindow::OnKeyUp(int nVirtKey)
{
	// Phase 18 - Add gameDone logic
	if (!gameWorld->IsGameDone())
	{
		switch (nVirtKey)
		{
			//Begin - Phase 10
		case VK_SHIFT:
			gameWorld->shift = false;
			gameWorld->sprint = false;
			break;
		case 0x57:
			gameWorld->w = false;
			break;
		case 0x53:
			gameWorld->s = false;
			break;
		case 0x44:
			gameWorld->d = false;
			break;
		case 0x41:
			gameWorld->a = false;
			break;
		default:
			break;
		}
	}
}//TOM

// Begin - Phase 16
void OGLWindow::OnMouseDownL(int x, int y) 
{
	if (!gameWorld->IsGameDone())
		///// -- Adam
		//gameWorld->player->FireWeapon2(); ///// -- Adam -- I changed this to shoot weapon 2
		gameWorld->player->fireWeapon = true;
		///// -- Adam
//	else
//		OnMouseDownL(0,0);
}
// End - Phase 16

///// -- Adam
//This function is for when you let go of the mouse button.
//It sets a boolean to let the player know to shoot rockets until the mouse is released
void OGLWindow::OnMouseUpL(int x, int y) 
{
	if (!gameWorld->IsGameDone())
		///// -- Adam
		//gameWorld->player->FireWeapon2(); ///// -- Adam -- I changed this to shoot weapon 2
		gameWorld->player->fireWeapon = false;
		///// -- Adam
//	else
//		OnMouseDownL(0,0);
}

void OGLWindow::OnMouseDownR(int x, int y) 
{
	if (!gameWorld->IsGameDone())
		gameWorld->player->FireWeapon();
	//set a bool here
//	else
//		OnMouseDownL(0,0);
}
///// -- Adam

// Begin - Phase 17 Add float parameter
void OGLWindow::Render(float deltaTime)
// End - Phase 17
{
	CCamera *camera = OnGetCamera();
	// Begin - Phase 11
	CWorld *world = OnGetWorld();

	world->Prepare();
	// End - Phase 11
    
	// Begin - Phase 5
	// For phase 10, change to 0.05
	// Phase 17 - change parameter to deltaTime
	camera->Animate(deltaTime);
	// End - Phase 5

	// Begin - Phase 11
	// Phase 17 - change parameter to deltaTime
	world->Animate(deltaTime);
	world->Draw(camera);
	// End - Phase 11
	// Begin - Phase 6 (Use Push/Pop)
    
	// Remove all following code - Phase 12
/*    glPushMatrix();
	// move back 5 units and rotate about all 3 axes
	glTranslatef(0.0, 0.0, -5.0f);
    glRotatef(m_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(m_angle, 0.0f, 1.0f, 0.0f);
    glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

    // lime greenish color
    glColor3f(0.7f, 1.0f, 0.3f);

    // draw the triangle such that the rotation point is in the center
    glBegin(GL_TRIANGLES);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

	glPopMatrix();
	// draw sphere at (5, 0, 0)
	glPushMatrix();
	glTranslatef(5.0f, 0.0f, 0.0f);
	glRotatef(90.0, 1.0f, 0.0f, 0.0f);

	GLUquadricObj * mySphere = gluNewQuadric();
	gluQuadricDrawStyle(mySphere, GLU_LINE);
	gluSphere(mySphere, 1.0, 12, 12);
	glPopMatrix();
	// draw cylinder at (0, 0, +5)
	glPushMatrix();
	float height = 2.0;
	glTranslatef(0.0f, height/2.0f, 5.0f);
	glRotatef(90.0, 1.0f, 0.0f, 0.0f);

	GLUquadricObj * myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_LINE);
	gluCylinder(myCylinder, 1.0, 1.0, height, 12, 12);
	glPopMatrix();

	// draw disk at (-5, 0, 0)
	glPushMatrix();
	glTranslatef(-5.0f, 0.0f, 0.0f);
	glRotatef(90.0, 0.0f, 1.0f, 0.0f);

	GLUquadricObj * myDisk = gluNewQuadric();
	gluQuadricDrawStyle(myDisk, GLU_LINE);
	gluDisk(myDisk, 0.0, 1.0, 12, 6);
	glPopMatrix();
	// End - Phase 6

	// Begin - Phase 7
// draw cone rotated 60 degrees above (0,0, -5)
	glPushMatrix();
	
	glRotatef(60.0, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);
	glTranslatef(0.0f, -height/2.0f, 0.0f);
	glRotatef(-90.0, 1.0f, 0.0f, 0.0f); 
	
	//GLUquadricObj * myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_LINE);
	gluCylinder(myCylinder, 1.0, 0.0, height, 12, 12);
	glPopMatrix();
	// draw ring rotated 60 degrees below (0,0, -5)
	glPushMatrix();
	glRotatef(-60.0, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -5.0f);
	//GLUquadricObj * myDisk = gluNewQuadric();
	gluQuadricDrawStyle(myDisk, GLU_LINE);
	gluDisk(myDisk, .5 , 1.0, 12, 6);
	glPopMatrix();
	// End - Phase 7
*/
}

