#include "gui.h"

///// -- Adam
//#include "OGLWindow.h"
//#include "ogro.h"
//#include "sod.h"
//#include "player.h"
///// -- Adam

#include <math.h>

CGUI::CGUI()
{
	///// -- Adam
	width = height = 0;
	sodIndex = ogroIndex = 0;
	gameOver = false;
	///// -- Adam

	minutesLeft = secondsLeft = enemiesLeft = 0;
	font = new CFont("Arial", 16);
	crosshair = new CFont("Courier New", 28);
	endText = new CFont("Arial", 40);
}

CGUI::~CGUI()
{
	font->ClearFont();
	crosshair->ClearFont();
	endText->ClearFont();
	delete font;
	delete crosshair;
	delete endText;
}

void CGUI::SetCurrentTime(float timeLeft)
{
	// timeLeft is in seconds

	minutesLeft = (int)(timeLeft / 60.0);	// 60 seconds in 1 minute
	secondsLeft = (int)floor(timeLeft) % 60;
	millisecondsLeft = static_cast<int>((timeLeft - (float)floor(timeLeft)) * 1000);
}

void CGUI::SetEnemiesLeft(int eLeft)
{
	enemiesLeft = eLeft;
}

void CGUI::DrawWinner()
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	endText->SetPos3D(-0.25f, 0.15f, -0.1f);
	endText->SetRGBA(0.3f, 1.0f, 0.3f, 0.8f);
	endText->Print("YOU WIN!");

	endText->SetPos3D(-0.5f, -0.2f, -0.1f);
	endText->SetRGBA(1.0f, 1.0f, 1.0f, 0.8f);
	endText->Print("Press the ESC key to exit");
	
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	///// -- Adam
	gameOver = true;
	///// -- Adam
}

void CGUI::DrawLoser()
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	endText->SetPos3D(-0.25f, 0.15f, -0.1f);
	endText->SetRGBA(1.0f, 0.3f, 0.3f, 0.8f);
	endText->Print("YOU LOSE!");

	endText->SetPos3D(-0.5f, -0.2f, -0.1f);
	endText->SetRGBA(1.0f, 1.0f, 1.0f, 0.8f);
	endText->Print("Press the ESC key to exit");
	
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	
	///// -- Adam
	gameOver = true;
	///// -- Adam
}

void CGUI::Draw()
{
	///// -- Adam
	if(!gameOver) // don't draw the HUD when the player wins or loses
	{
	///// -- Adam
		glDisable(GL_TEXTURE_2D);
		font->SetPos3D(2.5f, 2.7f, -5.0f);
		font->SetRGB(0.2f, 0.0f, 1.0f);
	
		if (secondsLeft < 10)
		{
			if (millisecondsLeft < 10)
				font->Print("Time: %d:0%d.0%d", minutesLeft, secondsLeft, millisecondsLeft);
			else
				font->Print("Time: %d:0%d.%d", minutesLeft, secondsLeft, millisecondsLeft);
		}
		else
		{
			if (millisecondsLeft < 10)
				font->Print("Time: %d:%d.0%d", minutesLeft, secondsLeft, millisecondsLeft);
			else
				font->Print("Time: %d:%d.%d", minutesLeft, secondsLeft, millisecondsLeft);
		}

		font->SetPos3D(2.5f, 2.5f, -5.0f);
		font->Print("Enemies: %d", enemiesLeft);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		crosshair->SetRGBA(1.0f, 0.1f, 0.1f, 0.7f);
		crosshair->SetPos3D(-0.03f, -0.03f, -5.0f);
		crosshair->Print("+");

		//glDisable(GL_BLEND); ///// -- Adam commented these out and moved them down to the bottom
		//glEnable(GL_TEXTURE_2D); ///// -- Adam commented these out

		/////////// -- Adam
		//We have to do something to change the way it is projected and then draw and then change it back.

		//Set up for 2D HUD drawing
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, (GLfloat)width, 0.0, (GLfloat)height);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		// Ready - Put HUD drawing here

		drawStamina(); // Draw the stamina bar on the HUD
		
		drawHealth(); // Draw the health bar on the HUD

		drawRadar(); // Draw the radar screen on the HUD

		//End HUD Drawing
	
		// -- Close up the HUD Drawing and go back to 3D mode
		glDisable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
	
		//gluPerspective(52.0f,(GLfloat)g_glRender->getWidth()/(GLfloat)g_glRender->getHeight(),1.0f,1000.0f);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);
			//the other place this gluPerspective method is called is in OGLWindow.cpp
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		////////// -- Adam
	
		glDisable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
	///// -- Adam
	}
	///// -- Adam
}

///// -- Adam
void CGUI::drawHealth()// draws the player's health bar
{
	//Draw Health Bar //TODO: make it shrink as HP decreases
	//int hp = 100; // temporary hp until we actually get hp implemented
	int hpMax = 100; 
	if (player->hp >= 50)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if (player->hp >= 25)
		glColor3f(1.0f, 1.0f, 0.0f);
	else
		glColor3f(1.0f, 0.0f, 0.0f); // color -- red
	glBegin(GL_QUADS);
		glVertex2i(200, 570);
		glVertex2i((GLfloat)player->hp / (GLfloat)hpMax * 400 + 200, 570);
		glVertex2i((GLfloat)player->hp / (GLfloat)hpMax * 400 + 200, 580);
		glVertex2i(200, 580);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(199, 569);
		glVertex2i(601, 569);
		glVertex2i(601, 581);
		glVertex2i(199, 581);
	glEnd();

	/**************************Faith Satterthwaite 12/1/2012******************************/
	if(player->hp <= 0)
		DrawLoser();
	/*************************************************************************************/
	
	//End Draw Health Bar
}
void CGUI::drawStamina()// draws the player's stamina bar
{
	//Draw Stamina Bar // TODO: make it increase and become more solid as players get more tired.
	int stamina = 100;
	int staminaMax = 100;
	glColor4f(0.8f, 0.8f, 0.3f, (GLfloat)stamina / staminaMax);//color -- yellow/tan
	glBegin(GL_QUADS);
		glVertex2i(20, 300);
		glVertex2i(30, 300);
		glVertex2i(30, (GLfloat)stamina / (GLfloat)staminaMax * 200 + 300);
		glVertex2i(20, (GLfloat)stamina / (GLfloat)staminaMax * 200 + 300);
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, (GLfloat)stamina / staminaMax);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(19, 299);
		glVertex2i(31, 299);
		glVertex2i(31, 501);
		glVertex2i(19, 501);
	glEnd();
	//End Draw Stamina Bar
}
void CGUI::drawRadar()// draw the radar screen on the HUD
{
	//Draw Radar Screen
	//This draws a rectangular radar screen and fills it with dots for each enemy and for your player.
	//The enemies show as black dots when idle and turn to red when you are in sight.
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glBegin(GL_LINE_LOOP);//Draw the outline of the radar screen
		glVertex2i(20, 20);
		glVertex2i(20, 200);
		glVertex2i(200, 200);
		glVertex2i(200, 20);
	glEnd();

	//Draw the player on the map
	glPushMatrix(); // save the state
	
	glTranslatef(player->position.z * 180.0 / 1600.0 + 20, player->position.x * 180.0 / 1600.0 + 20, 0);//Translate out to the correct location
	glRotatef(-player->direction + 90, 0, 0, 1); //rotate about the z axis
		//it's negative because we're drawing the radar in the opposite direction that the player->direction attribute works
		//plus ninety to get it to line up right.

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		glVertex2i(10, 0);//Draw our triangle's nose
		glVertex2i(-5, 5); //draw the back of the triangle
		glVertex2i(-5, -5);
	glEnd();
	glPopMatrix(); // reload the saved state
		
	//Then loop through and check to make sure it's not dead before showing it on the radar
	//rndInt = (rand() % (MAX_ENEMIES-4)) + 4;	// random # from 4 to MAX -- this is how many enemies world.cpp creates -- 10
	glPointSize(3.0);
	glBegin(GL_POINTS);
		//Draw the Sods on the map
		for (int i = 0; i < sodIndex; i++)
		{
			if (sod[i] != 0)
			{
				if (sod[i]->getAIState() == AI_UNCARING) // This changes the color based on idle verses attacking enemies
					glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
				else
					glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				if (sod[i]->getAIState() == AI_DEAD)
				{
					sod[i] = 0;//stop trying dead ones
				}
				else
				{//convert the sod's location into radar coordinates and draw it on the screen
					glVertex2i(sod[i]->position.z * 180.0 / 1600.0 + 20, sod[i]->position.x * 180.0 / 1600.0 + 20);
				}
			}
		}

		//Draw the Ogros on the map
		for (int i = 0; i < ogroIndex; i++)
		{
			if (ogro[i] != 0)
			{
				if (ogro[i]->getAIState() == AI_UNCARING) // This changes the color based on idle verses attacking enemies
					glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
				else
					glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				if (ogro[i]->getAIState() == AI_DEAD)
				{
					ogro[i] = 0;//stop trying dead ones
				}
				else
				{//convert the ogro's location into radar coordinates and draw it on the screen
					glVertex2i(ogro[i]->position.z * 180.0 / 1600.0 + 20, ogro[i]->position.x * 180.0 / 1600.0 + 20);
				}
			}
		}
	glEnd();
	//End Draw Radar Screen
} 

//This function is used to give the GUI the width and height values of the screen. It is called from the world.cpp file
//The GUI uses these to determine how to set the perspective back to 3D and to know the HUD dimensions.
void CGUI::setScreen(int w, int h) 
{
	width = w;
	height = h;
}

//get a pointer to the player
void CGUI::setPlayer(CPlayer* p)
{
	player = p;
}

//get a pointer to the sod // The array is used to keep track of all sods on the map in the radar screen
void CGUI::setSod(CEnemy* s)
{
	sod[sodIndex] = s;
	sodIndex++;
}

//get a pointer to the ogro // The array is used to keep track of all ogros on the map in the radar screen
void CGUI::setOgro(CEnemy* o)
{
	ogro[ogroIndex] = o;
	ogroIndex++;
}
///// -- Adam