#include "settings.h"

#include "glut.h"

#include "bulletWindow.h"
#include "snowman.h"
#include <iostream>

BulletWindow BulletWindow::create(const char* title) {
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  BulletWindow window(title, 3.0);
  glEnable(GL_DEPTH_TEST);
  return window;
}

BulletWindow::BulletWindow(const char* title, btScalar distance) :
  Window(title),
  m_cam(distance,*this)
{
  m_aspectRatio = m_width / (GLfloat) m_height;
}

void BulletWindow::reshapeCallback(int w, int h) {
  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if(h == 0)
    h = 1;
  m_aspectRatio = 1.0* w / h;
  glViewport(0,0,w,h);
}

void BulletWindow::mouseCallback(int button, int state, int x, int y) {
  m_cam.startMouseMove(button, state, x, y);
}

void BulletWindow::motionCallback(int x, int y) {
  m_cam.updateMouseMove(x, y);
}

void BulletWindow::keyboardCallback(unsigned char key, int x, int y) {
  // 0x1B is escape
  switch(key) {
  case 0x1B:
    close(); break;
  }
}

void BulletWindow::specialKeyCallback(int key, int x, int y) {

  switch(key) {
  case GLUT_KEY_F1 :
    m_red = m_red < 0.5 ? 1.0 : 0.0;
    break;
  case GLUT_KEY_F2 :
    m_green = m_green < 0.5 ? 1.0 : 0.0;
    break;
  case GLUT_KEY_F3 :
    m_blue = m_blue < 0.5 ? 1.0 : 0.0;
    break;
  }
  postRedisplay();
}


void BulletWindow::displayCallback() {
  glMatrixMode(GL_PROJECTION);
  // Reset transformations
  glLoadIdentity();
  gluPerspective(50, m_aspectRatio, 0.1, 1000);
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
  
  glColor3f(m_red,m_green,m_blue);
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

  glColor3f(1-m_red,1-m_green,m_blue);

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

  // When we are moving around, draw a little yellow disk similar to
  // that one RVIZ draws.
  glPushMatrix();
  {
    btVector3 disk_pos(m_cam.m_camera_center_distance, 0, 0);
    disk_pos = m_cam.m_camera_transform(disk_pos);
    glTranslated(disk_pos.getX() ,disk_pos.getY() , disk_pos.getZ());
    glColor3f(0.8f, 0.8f, 0.0f);
    glScalef(1.0f, 1.0f, 0.1f);
    glutSolidSphere(0.1, 50, 50);
  }
  glPopMatrix();

  glFlush();
  
  glutSwapBuffers();
}
