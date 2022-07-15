#include "window.h"

#include "glut.h"

#include <map>

std::map<int,Window*> activeWindows;



Window::Window(const char* title)
  : m_window_id(0)
{
  m_window_id = glutCreateWindow("Lighthouse3D- GLUT Tutorial");
  m_height = glutGet(GLUT_WINDOW_HEIGHT);
  m_width = glutGet(GLUT_WINDOW_WIDTH);
  activeWindows[m_window_id] = this;

  
  glutDisplayFunc(&Window::staticDisplayCallback);
  glutReshapeFunc(&Window::staticReshapeCallback);
  
  glutKeyboardFunc(&Window::staticKeyboardCallback);
  glutSpecialFunc(&Window::staticSpecialKeyCallback);

  glutMouseFunc(&Window::staticMouseCallback);
  glutMotionFunc(&Window::staticMotionCallback);
  
}

Window::~Window(){
  activeWindows.erase(m_window_id);
}

// static callbacks, since c++ doesn't like to use instance methods as callbacks for c functions.
void Window::postRedisplay() {
  glutPostWindowRedisplay(m_window_id);
}

void Window::close() {
  glutDestroyWindow(m_window_id);
}

void Window::staticDisplayCallback() {
  activeWindows[glutGetWindow()]->displayCallback();
}

void Window::staticReshapeCallback(int width, int height) {
  Window *w = activeWindows[glutGetWindow()];
  w->m_width = width;
  w->m_height = height;
  activeWindows[glutGetWindow()]->reshapeCallback(width, height);
}

void Window::staticKeyboardCallback(unsigned char key, int x, int y) {
  activeWindows[glutGetWindow()]->keyboardCallback(key, x, y);
}

void Window::staticSpecialKeyCallback(int key, int x, int y) {
  activeWindows[glutGetWindow()]->specialKeyCallback(key, x, y);
}

void Window::staticMouseCallback(int button, int state, int x, int y) {
  activeWindows[glutGetWindow()]->mouseCallback(button, state, x, y);
}

void Window::staticMotionCallback(int x, int y) {
  activeWindows[glutGetWindow()]->motionCallback(x, y);
}
