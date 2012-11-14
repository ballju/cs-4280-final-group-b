#ifndef __OBJECT_H
#define __OBJECT_H

#include "tree.h"
#include "vector.h"
#include "camera.h"

/*
	OBJECT.H

  	The CObject class

	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: 3/29/2001
	Description: The CObject class is derived from CNode and
			   represents an object in the game world.

*/

class CObject : public CNode
{
protected:

     // perform basic physics on the object
     virtual void OnAnimate(scalar_t deltaTime) 
     {
          position += velocity * deltaTime;
          velocity += acceleration * deltaTime;
     }

     // draw the object given the camera position
     virtual void OnDraw(CCamera *camera) {} 

     // collide with other objects
     virtual void OnCollision(CObject *collisionObject) {}

     // perform collision and other preparations for this object
     virtual void OnPrepare() 
     {
          ProcessCollisions(FindRoot());     // perform collisions starting with
                                             // root world object
     }

public:
     CVector position;        // object position
     CVector velocity;        // velocity of object
     CVector acceleration;    // acceleration
     scalar_t size;           // size of bounding sphere (radius)

     bool isDead;

     CObject() { isDead = false; }
     ~CObject() {}

     virtual void Load() {}
     virtual void Unload() {}

     // draw object
     void Draw(CCamera *camera) 
     {
          // push modelview matrix on stack
          glPushMatrix();
               OnDraw(camera);          // draw this object
               if (HasChild())          // draw children
                    ((CObject*)childNode)->Draw(camera);
          glPopMatrix();

          // draw siblings
          if (HasParent() && !IsLastChild())
               ((CObject*)nextNode)->Draw(camera);
     }

     // animate object
     void Animate(scalar_t deltaTime) 
     {
          OnAnimate(deltaTime);         // animate this object
     
          // animate children
          if (HasChild())
               ((CObject*)childNode)->Animate(deltaTime);

          // animate siblings
          if (HasParent() && !IsLastChild())
               ((CObject*)nextNode)->Animate(deltaTime);

          if (isDead)
               delete this;
     }

     // perform collision detection
     void ProcessCollisions(CObject *obj) 
     {
          // if this object's bounding sphere collides with obj's sphere
          // and obj is not this object
          if (((obj->position - position).Length() <= (obj->size + size)) &&
               (obj != ((CObject*)this)))
          {
               OnCollision(obj);        // perform this object's collision with obj

               // test child collisions with obj
               if (HasChild())
                    ((CObject*)childNode)->ProcessCollisions(obj);

               // test sibling collisions with obj
               if (HasParent() && !IsLastChild())
                    ((CObject*)nextNode)->ProcessCollisions(obj);
          }

          // if obj has children, check collisions with these children
          if (obj->HasChild())
               ProcessCollisions((CObject*)(obj->childNode));

          // if obj has siblings, check collisions with these siblings
          if (obj->HasParent() && !obj->IsLastChild())
               ProcessCollisions((CObject*)(obj->nextNode));
     }

     // prepare object
     void Prepare()
     {
          OnPrepare();                            // prepare this object

          if (HasChild())                         // prepare children
               ((CObject*)childNode)->Prepare();

          if (HasParent() && !IsLastChild())      // prepare siblings
               ((CObject*)nextNode)->Prepare();
     }

     // find root object of cyclic linked list tree
     CObject *FindRoot()
     {
          // if this object has a parent node, return the root of the parent node
          if (parentNode)
               return ((CObject*)parentNode)->FindRoot();

          return this;
     }
};


#endif