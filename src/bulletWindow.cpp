#include "bulletWindow.h"
#include "snowman.h"

BulletWindow::BulletWindow(const char* title, btScalar distance) :
  Window(title),
  m_cam(distance,*this)
{
}

void BulletWindow::displayCallback() {
  glMatrixMode(GL_PROJECTION);
  // Reset transformations
  glLoadIdentity();
  gluPerspective(50, aspectRatio, 0.1, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // Rotate to use ROS standard Frame of Reference of Z UP
  glRotated(90, 1, 0, 0);
  glRotated(-90, 0, 0, 1);
  glRotated(180, 1, 0, 0);

  { // Rotate to the perspective defined by the camera
    GLdouble camMatrix[16];
    m_cam.m_camera_transform.inverse().getOpenGLMatrix(camMatrix);
    glMultMatrixd(camMatrix);
  }

  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glColor3f(red,green,blue);
  glBegin(GL_TRIANGLES);
  glVertex3f(-2.0f,-2.0f, 0.0f);
  glVertex3f( 2.0f, 0.0f, 0.0f);
  glVertex3f( 0.0f, 2.0f, 0.0f);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f,-1.0f);
  glEnd();

  
  glBegin(GL_LINE_LOOP);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 2.0f,-1.0f);
  glEnd();

  glColor3f(1-red,1-green,blue);

  glBegin(GL_POINTS);
  glVertex3f(0.0f,0.1f,0.0f);
  glEnd();

  // Draw ground
  glColor3f(0.9f, 0.9f, 0.9f);
  glBegin(GL_QUADS);
  glVertex3f(-100.0f, -100.0f, 0.0f);
  glVertex3f(-100.0f,  100.0f, 0.0f);
  glVertex3f( 100.0f,  100.0f, 0.0f);
  glVertex3f( 100.0f, -100.0f, 0.0f);
  glEnd();

  drawSnowMan();

  glutSwapBuffers();
}
