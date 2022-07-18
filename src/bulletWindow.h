#ifndef BULLET_WINDOW_H__
#define BULLET_WINDOW_H__

#include "settings.h"
#include "glut.h"

#include "camera.h"

#include <bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h>

class BulletWindow : public Window
{
 private:
  GLfloat m_aspectRatio;

  btVector3 m_light_position;

  GLfloat m_red = 1;
  GLfloat m_green = 1;
  GLfloat m_blue = 1;

  int ticks = 0;
  
  const btCollisionWorld *m_world;

  BulletWindow(const char* title, btScalar distance, const btCollisionWorld *world);

 public:
  CameraMouseData m_cam;

  static BulletWindow create(const char* title, const btCollisionWorld *world);
  
  void displayCallback() override;
  void reshapeCallback(int width, int height) override;
  void keyboardCallback(unsigned char key, int x, int y) override;
  void specialKeyCallback(int key, int x, int y) override;
  void mouseCallback(int button, int state, int x, int y) override;
  void motionCallback(int x, int y) override;
  void tick() override;
};

#endif
