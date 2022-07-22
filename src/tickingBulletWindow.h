#ifndef TICKING_BULLET_WINDOW_H__
#define TICKING_BULLET_WINDOW_H__
/**
 * A TickingBulletWindow is a BulletWindow that additionally allows the user to start/stop ticking of the world via the 'P' key.
 * In the future this might be updated to include controls for setting the speed.
 */

#include "bulletWindow.h"

class TickingBulletWindow : public BulletWindow
{
 private:
  bool m_paused;
  // Stores the tick delay while playback is paused. 
  int m_tick_delay;
 public:
  TickingBulletWindow(const char* title, btDynamicsWorld *world);

  void keyboardCallback(unsigned char key, int x, int y) override;
  void tick() override;

  void start();
  void stop();
};

#endif
