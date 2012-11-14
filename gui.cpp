#include "gui.h"
#include <math.h>

CGUI::CGUI()
{
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
}

void CGUI::Draw()
{
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
	
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
}