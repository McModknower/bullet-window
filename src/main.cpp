// Making a window using https://www.lighthouse3d.com/tutorials/glut-tutorial/ and https://en.wikibooks.org/wiki/OpenGL_Programming

#include <iostream>
#include <iomanip>

#include "settings.h"

#include "glut.h"

#include "snowman.h"

#include "camera.h"

GLfloat red = 1;
GLfloat green = 1;
GLfloat blue = 1;

GLfloat aspectRatio;

CameraMouseData *cam;

void renderScene() {

  glMatrixMode(GL_PROJECTION);
  // Reset transformations
  glLoadIdentity();
  gluPerspective(50, aspectRatio, 0.1, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotated(90, 1, 0, 0);
  glRotated(-90, 0, 0, 1);
  glRotated(180, 1, 0, 0);
  {
    GLdouble camMatrix[16];
    cam->m_camera_transform.inverse().getOpenGLMatrix(camMatrix);
    glMultMatrixd(camMatrix);
    // std::cout << "Cam Matrix is" << std::endl;
    // std::cout << std::fixed << std::setprecision(2);
    // std::cout << std::setw(6) << camMatrix[0] << std::setw(6) << camMatrix[4] << std::setw(6) << camMatrix[8] << std::setw(6) << camMatrix[12] << std::endl;
    // std::cout << std::setw(6) << camMatrix[1] << std::setw(6) << camMatrix[5] << std::setw(6) << camMatrix[9] << std::setw(6) << camMatrix[13] << std::endl;
    // std::cout << std::setw(6) << camMatrix[2] << std::setw(6) << camMatrix[6] << std::setw(6) << camMatrix[10] << std::setw(6) << camMatrix[14] << std::endl;
    // std::cout << std::setw(6) << camMatrix[3] << std::setw(6) << camMatrix[7] << std::setw(6) << camMatrix[11] << std::setw(6) << camMatrix[15] << std::endl;
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
  glColor3f(1-red,1-green,1-blue);
  glBegin(GL_QUADS);
  glVertex3f(-100.0f, -100.0f, 0.0f);
  glVertex3f(-100.0f,  100.0f, 0.0f);
  glVertex3f( 100.0f,  100.0f, 0.0f);
  glVertex3f( 100.0f, -100.0f, 0.0f);
  glEnd();

  drawSnowMan();

  glutSwapBuffers();
}

void changeSize(int w, int h) {

  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if(h == 0)
    h = 1;
  aspectRatio = 1.0* w / h;
}

int window_id;

void processNormalKeys(unsigned char key, int x, int y) {
  // 0x1B is escape
  switch(key) {
  case 0x1B:
    glutDestroyWindow(window_id); break;
  }
}

void processSpecialKeys(int key, int x, int y) {

  switch(key) {
  case GLUT_KEY_F1 :
    red = red < 0.5 ? 1.0 : 0.0;
    break;
  case GLUT_KEY_F2 :
    green = green < 0.5 ? 1.0 : 0.0;
    break;
  case GLUT_KEY_F3 :
    blue = blue < 0.5 ? 1.0 : 0.0;
    break;
  }
  glutPostRedisplay();
}

void mouseCallback(int button, int state, int x, int y) {
  cam->startMouseMove(button, state, x, y);
}

void moveCallback(int x, int y) {
  cam->updateMouseMove(x, y);
}

int main(int argc, char **argv) {
  // init GLUT and create Window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(320,320);
  aspectRatio = 1.0;
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  Window window("Lighthouse3D- GLUT Tutorial");
  window_id = window.m_window_id;//glutCreateWindow("Lighthouse3D- GLUT Tutorial");
  CameraMouseData local_cam(30.0, window);
  cam = &local_cam;
  // register callbacks
  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);

  glutMouseFunc(mouseCallback);
  glutMotionFunc(moveCallback);
 
  glEnable(GL_DEPTH_TEST);
  
  // enter GLUT event processing cycle
  glutMainLoop();

  std::cout << "Goodbye" << std::endl;

  return EXIT_SUCCESS;
}
