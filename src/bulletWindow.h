#ifndef BULLET_WINDOW_H__
#define BULLET_WINDOW_H__

#include "settings.h"
#include "glut.h"

#include "camera.h"

class BulletWindow : public Window
{
 private:
  GLfloat m_aspectRatio;
  GLfloat m_red = 1;
  GLfloat m_green = 1;
  GLfloat m_blue = 1;

  BulletWindow(const char* title, btScalar distance);

 public:
  CameraMouseData m_cam;

  static BulletWindow create(const char* title);
  
  void displayCallback() override;
  void reshapeCallback(int width, int height) override;
  void keyboardCallback(unsigned char key, int x, int y) override;
  void specialKeyCallback(int key, int x, int y) override;
  void mouseCallback(int button, int state, int x, int y) override;
  void motionCallback(int x, int y) override;
};

#endif
