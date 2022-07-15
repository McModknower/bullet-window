// Making a window using https://www.lighthouse3d.com/tutorials/glut-tutorial/ and https://en.wikibooks.org/wiki/OpenGL_Programming

#include <iostream>
#include <iomanip>

#include "settings.h"

#include "glut.h"

#include "bulletWindow.h"

int main(int argc, char **argv) {
  // init GLUT and create Window
  glutInit(&argc, argv);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(320,320);
  BulletWindow window = BulletWindow::create("Lighthouse3D- GLUT Tutorial");
  
  // enter GLUT event processing cycle
  glutMainLoop();

  std::cout << "Goodbye" << std::endl;

  return EXIT_SUCCESS;
}
