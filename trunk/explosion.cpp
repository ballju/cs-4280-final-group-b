/****************************************************************************
 Particles.h  Particle and particle system base classes.
 
 Author   :   Dave Astle
 Date     :   2/1/2001

 Written for OpenGL Game Programming
*****************************************************************************/


/********************************* Includes *********************************/
#include "explosion.h"
#include <time.h>


/*****************************************************************************
 CExplosion::Constructor

 Nothing to do
*****************************************************************************/
CExplosion::CExplosion(int numParticles, CVector origin, float spread, GLuint texture)
  : m_texture(texture), m_spread(spread), CParticleSystem(numParticles, origin)
{
  srand((unsigned)time(NULL));
  CParticleSystem::InitializeSystem();
  Emit(numParticles);
} // end CExplosion::Constructor


/*****************************************************************************
 CExplosion::InitializeParticle()

 Sets the initial particle properties for the explosion
*****************************************************************************/
void CExplosion::InitializeParticle(int index)
{
  // start the particle at the sky at a random location in the emission zone
  m_particleList[index].m_pos.x = m_origin.x + FRAND * m_spread;
  m_particleList[index].m_pos.y = m_origin.y + FRAND * m_spread;
  m_particleList[index].m_pos.z = m_origin.z + FRAND * m_spread;

  // set the size of the particle
  m_particleList[index].m_size = PARTICLE_SIZE + FRAND * SIZE_VARIATION;

  // give the particle a random velocity
  m_particleList[index].m_velocity.x = PARTICLE_VELOCITY.x + FRAND * VELOCITY_VARIATION.x;
  m_particleList[index].m_velocity.y = PARTICLE_VELOCITY.y + FRAND * VELOCITY_VARIATION.y;
  m_particleList[index].m_velocity.z = PARTICLE_VELOCITY.z + FRAND * VELOCITY_VARIATION.z;

  m_particleList[index].m_acceleration = PARTICLE_ACCELERATION;

  m_particleList[index].m_color[0] = 1.0;
  m_particleList[index].m_color[1] = 1.0;
  m_particleList[index].m_color[2] = 0.4f;
  m_particleList[index].m_color[3] = 1.0;

  m_particleList[index].m_energy = static_cast<float>(0.5 + FRAND/2.0);

  m_particleList[index].m_colorDelta[0] = 0.0;
  m_particleList[index].m_colorDelta[1] = 0.0;
  m_particleList[index].m_colorDelta[2] = 0.0;
  m_particleList[index].m_colorDelta[3] = static_cast<float>(-1.0/m_particleList[index].m_energy);

//  m_particleList[index].m_sizeDelta = -m_particleList[index].m_size/m_particleList[index].m_energy;
  m_particleList[index].m_sizeDelta = 8.0;

} // end CExplosion::InitializeParticle


/*****************************************************************************
 CExplosion::Update

 Update the existing particles, killing them and creating new ones as needed
*****************************************************************************/
void CExplosion::Update(float elapsedTime)
{
  for (int i = 0; i < m_numParticles; )
  {
    // update the particle's position based on the elapsed time and velocity
    m_particleList[i].m_pos = m_particleList[i].m_pos + m_particleList[i].m_velocity * elapsedTime;
    m_particleList[i].m_velocity = m_particleList[i].m_velocity + m_particleList[i].m_acceleration * elapsedTime;

    m_particleList[i].m_energy -= elapsedTime;
    m_particleList[i].m_size += m_particleList[i].m_sizeDelta * elapsedTime;

    m_particleList[i].m_color[3] += m_particleList[i].m_colorDelta[3] * elapsedTime;
    m_particleList[i].m_color[1] += m_particleList[i].m_colorDelta[1] * elapsedTime;

    // if the particle has hit the ground plane, kill it
    if (m_particleList[i].m_energy <= 0.0)
    {
      // move the last particle to the current positon, and decrease the count
      m_particleList[i] = m_particleList[--m_numParticles];
    }
    else
    {
      ++i;
    }
  }
} // end CExplosion::Update()


/*****************************************************************************
 CExplosion::Render()

 Draw the snowflake particles as textured quads
*****************************************************************************/
void CExplosion::Render()
{
  float viewMatrix[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);

  CVector right(viewMatrix[0], viewMatrix[4], viewMatrix[8]);
  CVector up(viewMatrix[1], viewMatrix[5], viewMatrix[9]);

//  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  GLfloat size;
  CVector pos;

  glBegin(GL_QUADS);
  for (int i = 0; i < m_numParticles; ++i)
  {
    size = m_particleList[i].m_size/2;
    pos = m_particleList[i].m_pos;
    glColor4fv(m_particleList[i].m_color);
    glTexCoord2f(0.0, 0.0); glVertex3fv((pos + (right + up) * - size).v);
    glTexCoord2f(1.0, 0.0); glVertex3fv((pos + (right - up) * size).v);
    glTexCoord2f(1.0, 1.0); glVertex3fv((pos + (right + up) * size).v);
    glTexCoord2f(0.0, 1.0); glVertex3fv((pos + (up - right) * size).v);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
//  glEnable(GL_DEPTH_TEST);
} // end CExplosion::Update
