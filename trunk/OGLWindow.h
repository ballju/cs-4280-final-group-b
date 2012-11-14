#ifndef __GL_COMPONENT
#define __GL_COMPONENT

//#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

// Begin - Phase 5
#include "camera.h"
// remove above definition of PI - already defined in vector.h
// End - Phase 5

// Begin - Phase 11
#include "world.h"
// remove above definition of PI - already defined in vector.h
// End - Phase 11

class OGLWindow
{
private:
	int m_windowWidth;
	int m_windowHeight;
	



	float m_angle;

	// Begin - Phase 5
	CCamera *gameCamera;

	CCamera *OnGetCamera() { return gameCamera; }
	// End - Phase 5
	// Begin - Phase 11
	CWorld *gameWorld;
	CWorld *OnGetWorld() { return gameWorld; }
	// End - Phase 11

public:
	OGLWindow();
	virtual ~OGLWindow();

	bool Init();
	bool Shutdown();

	void SetupProjection(int width, int height);
	// Begin - Phase 17 Change parameter lists
	void Prepare();
	void Render(float deltaTime);
	// End - Phase 17
	// Begin - Phase 6
	int mouseX;
	int mouseY;
	float mouseSensitivity;

	int GetMouseX(LPARAM lParam);		// get true mouse coordinates
	int GetMouseY(LPARAM lParam);
	void OnMouseMove(int x, int y);
	// End - Phase 6
	// Begin - Phase 9
	void OnKeyDown(int nVirtKey); 
	// End - Phase 9
	// Begin - Phase 16
	void OnMouseDownL(int x, int y);
	// End - Phase 16
};

#endif