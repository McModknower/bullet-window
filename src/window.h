#ifndef WINDOW_H__
#define WINDOW_H__

class Window
{
private:
  static void staticDisplayCallback();
  static void staticReshapeCallback(int width, int height);
  static void staticKeyboardCallback(unsigned char key, int x, int y);
  static void staticSpecialKeyCallback(int key, int x, int y);
  static void staticMouseCallback(int button, int state, int x, int y);
  static void staticMotionCallback(int x, int y);
public:
  int m_window_id;
  int m_height;
  int m_width;

  Window(const char* title);
  
  virtual void displayCallback() {}
  virtual void reshapeCallback(int width, int height) {}
  virtual void keyboardCallback(unsigned char key, int x, int y) {}
  virtual void specialKeyCallback(int key, int x, int y) {}
  virtual void mouseCallback(int button, int state, int x, int y) {}
  virtual void motionCallback(int x, int y) {}

  void postRedisplay();
  void close();

  virtual ~Window();
};

#endif
