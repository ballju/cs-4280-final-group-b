/*
	CAMERA.CPP

	What is in this file?

*/

#include "camera.h"
#include "object.h"

CCamera::CCamera()
{
	position = CVector(0.0, 0.0, 0.0);
	//Begin - Phase 5
	// Change initial lookAt vector to look down
	// the negative z axis
	lookAt = CVector(0.0, 0.0, -1.0);
	//End - Phase 5

	forward = lookAt;
	up = CVector(0.0, 1.0, 0.0);
	right = CVector(1.0, 0.0, 0.0);

	velocity = CVector(0.0, 0.0, 0.0);
	acceleration = CVector(0.0, 0.0, 0.0);
	// Begin - Phase 5
	// Begin - Phase 13 Change the following yaw vector
	yaw = 45.0;
	// End - Phase 5
	pitch = 0.0;
}

CCamera::CCamera(CVector *look)
{
	position = CVector(0.0, 0.0, 0.0);
	lookAt = look->UnitVector();

	forward = lookAt;
	up = CVector(0.0, 1.0, 0.0);
	right = forward.CrossProduct(up); //CVector(1.0, 0.0, 0.0);

	velocity = CVector(0.0, 0.0, 0.0);
	acceleration = CVector(0.0, 0.0, 0.0);	

	yaw = 0.0;
	pitch = 0.0;
}

CCamera::CCamera(CVector *pos, CVector *look)
{
	position = *pos;
	lookAt = look->UnitVector();

	forward = lookAt;
	up = CVector(0.0, 1.0, 0.0);
	right = CVector(1.0, 0.0, 0.0);

	velocity = CVector(0.0, 0.0, 0.0);
	acceleration = CVector(0.0, 0.0, 0.0);

	yaw = 0.0;
	pitch = 0.0;
}

CCamera::~CCamera()
{
}

void CCamera::UpdateLookAt()
{
	CVector look = CVector(finalLookAt.x - lookAt.x,
					   finalLookAt.y - lookAt.y,
					   finalLookAt.z - lookAt.z);

	lookAtVel = look * 0.5;
}

void CCamera::UpdateMoveTo()
{
	CVector pos = CVector(finalPosition.x - position.x,
					  finalPosition.y - position.y,
					  finalPosition.z - position.z);

	velocity = pos * 0.5;
}

void CCamera::RotatePitch(scalar_t radians)
{
	float sine = sinf(radians);
	float cosine = cosf(radians);

	up.y = cosine * up.Length();
	up.z = sine * up.Length();

	forward.y = -sine * forward.Length();
	forward.z = cosine * forward.Length();
	/*     x   y      z       p
         |  1  0       0       0 |
     M = |  0  cos(A) -sin(A)  0 |
         |  0  sin(A)  cos(A)  0 |
         |  0  0       0       1 |
	*/
}

void CCamera::RotateYaw(scalar_t radians)
{
	float sine = sinf(radians);
	float cosine = cosf(radians);
	
	right.x = cosine * right.Length();
	right.z = sine * right.Length();

	forward.x = -sine * forward.Length();
	forward.z = cosine * forward.Length();
	
	/*	   x      y    z      p
         |  cos(A)  0  -sin(A)  0 |
     M = |  0       1   0       0 |
         |  sin(A)  0   cos(A)  0 |
         |  0       0   0       1 |
	*/

}

void CCamera::RotateRoll(scalar_t radians)
{
	float sine = sinf(radians);
	float cosine = cosf(radians);
	
	right.x = cosine * right.Length();
	right.y = sine * right.Length();

	up.x = -sine * forward.Length();
	up.y = cosine * forward.Length();
	/*
         |  cos(A)  -sin(A)   0   0 |
     M = |  sin(A)   cos(A)   0   0 |
         |  0        0        1   0 |
         |  0        0        0   1 |
	*/
}


void CCamera::LookAtNow(CObject *object)
{
	lookAt = object->position;
}

void CCamera::MoveToNow(scalar_t x, scalar_t y, scalar_t z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}


void CCamera::MoveToNow(CObject *object)
{
	position = object->position;
}

// look at an object over time
void CCamera::LookAt(CObject *object)
{
	CVector v = CVector(object->position - lookAt);

	initLookAt = lookAt;
	finalLookAt = object->position;

	lookAtAccel = -lookAt * 0.25f;

	UpdateLookAt();
}

// move to an object over time
void CCamera::MoveTo(CObject *object)
{
	CVector v = CVector(object->position - position);

	initPosition = position;
	finalPosition = object->position;

	acceleration = -position * 0.25f;

	UpdateMoveTo();
}


void CCamera::Animate(scalar_t deltaTime)
{
     if ((yaw >= 360.0f) || (yaw <= -360.0f))
          yaw = 0.0f;

     if (pitch > 60.0f)
          pitch = 60.0f;
     if (pitch < -60.0f)
          pitch = -60.0f;
     
	// calculate trig functions
     float cosYaw = (scalar_t)cos(DEG2RAD(yaw));
     float sinYaw = (scalar_t)sin(DEG2RAD(yaw));
     float sinPitch = (scalar_t)sin(DEG2RAD(pitch));

	// speed is velocity z-component
     float speed = velocity.z * deltaTime;

	// strafe speed is velocity x-component
     float strafeSpeed = velocity.x * deltaTime;

	// speed limit
     if (speed > 15.0)
          speed = 15.0;
     if (strafeSpeed > 15.0)
          strafeSpeed = 15.0;
     if (speed < -15.0)
          speed = -15.0;
     if (strafeSpeed < -15.0)
          strafeSpeed = -15.0;

	// friction slows down movements
     if (velocity.Length() > 0.0)
          acceleration = -velocity * 1.5f;

     velocity += acceleration*deltaTime;

	// calculate new position of camera
     position.x += float(cos(DEG2RAD(yaw + 90.0)))*strafeSpeed;
     position.z += float(sin(DEG2RAD(yaw + 90.0)))*strafeSpeed;
     position.x += float(cosYaw)*speed;
     position.z += float(sinYaw)*speed;

	// calculate lookAt based on new position
     lookAt.x = float(position.x + cosYaw);
     lookAt.y = float(position.y + sinPitch);
     lookAt.z = float(position.z + sinYaw);

	// set the camera
	gluLookAt(position.x, position.y, position.z,
               lookAt.x, lookAt.y, lookAt.z,
               0.0, 1.0, 0.0);
}