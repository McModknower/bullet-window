// Making a window using https://www.lighthouse3d.com/tutorials/glut-tutorial/ and https://en.wikibooks.org/wiki/OpenGL_Programming

#include <iostream>
#include <iomanip>

#include "settings.h"

#include "glut.h"

#include "bulletWindow.h"

int main(int argc, char **argv) {
  // init GLUT and create Window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(320,320);
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  BulletWindow window("Lighthouse3D- GLUT Tutorial", 3.0);
  // register callbacks
 
  glEnable(GL_DEPTH_TEST);
  
  // enter GLUT event processing cycle
  glutMainLoop();

  std::cout << "Goodbye" << std::endl;

  return EXIT_SUCCESS;
}
