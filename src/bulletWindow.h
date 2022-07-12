#ifndef BULLET_WINDOW_H__
#define BULLET_WINDOW_H__

#include "settings.h"
#include "glut.h"

#include "camera.h"

class BulletWindow : Window
{
 private:
  GLfloat aspectRatio;
  GLfloat red = 1;
  GLfloat green = 1;
  GLfloat blue = 1;

 public:
  CameraMouseData m_cam;
  
  BulletWindow(const char* title, btScalar distance);

  void displayCallback();
};

#endif
