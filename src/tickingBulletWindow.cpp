#include "tickingBulletWindow.h"

TickingBulletWindow::TickingBulletWindow(const char* title, btDynamicsWorld *world) :
  BulletWindow(title, world),
  m_paused(true),
  m_tick_delay(1000 / 60)
{
}

void TickingBulletWindow::display() {
  BulletWindow::display();
  if(!m_paused) {
    start();
  }
}

void TickingBulletWindow::keyboardCallback(unsigned char key, int x, int y) {
  switch(key) {
  case 'p':
    m_paused = !m_paused;
    if(m_paused) {
      stop();
    } else {
      start();
    }
    break;
  default:
    BulletWindow::keyboardCallback(key, x, y);
  }
}

void TickingBulletWindow::tick() {
  if(!m_paused) {
    m_world->stepSimulation(1. / 60.);
    postRedisplay();
  }
}

void TickingBulletWindow::start() {
  enableTick(m_tick_delay);
}

void TickingBulletWindow::stop() {
  disableTick();
}
