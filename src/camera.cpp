#include "camera.h"

#include <iostream>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <GLUT/freeglut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif

CameraMouseData::CameraMouseData(btScalar distance) :
  m_motion_mode(MOTION_MODE_NOTHING),
  m_camera_center_distance(distance),
  m_camera_transform(btQuaternion(0, 0, 0, 1))
{
}

void CameraMouseData::startMouseMove(int button, int state, int x, int y) {
  if(state == GLUT_UP) {
    m_motion_mode = MOTION_MODE_NOTHING;
  } else {
    btTransform other(btQuaternion(0, 0, 0, 1));
    btTransform result(btQuaternion(0, 0, 0, 1));
    switch(button) {
    case 3: // WHEEL_UP
      other.setOrigin(btVector3(0.10*m_camera_center_distance, 0.0, 0.0));
      result.mult(m_camera_transform, other);
      m_camera_transform = result;
      break;
    case 4: // WHEEL_DOWN
      other.setOrigin(btVector3((-0.10)*m_camera_center_distance, 0.0, 0.0));
      result.mult(m_camera_transform, other);
      m_camera_transform = result;
      break;
    }
    if(m_motion_mode == MOTION_MODE_NOTHING) {
      m_lx = x;
      m_ly = y;
      switch(button) {
      case GLUT_LEFT_BUTTON:
	m_motion_mode = MOTION_MODE_ROTATE; break;
      case GLUT_RIGHT_BUTTON:
	m_motion_mode = MOTION_MODE_TRANSLATE; break;
      }
    }
  }
  glutPostRedisplay();
}

void CameraMouseData::updateMouseMove(int x, int y)
{
  if(m_motion_mode == MOTION_MODE_NOTHING) {
    return;
  }
  // TODO use width and height instead of 100
  btScalar dx = (x - m_lx) / 100.0;
  btScalar dy = (y - m_ly) / 100.0;
  btVector3 camera_center(m_camera_center_distance, 0, 0);
  camera_center = m_camera_transform(camera_center);
  m_lx = x;
  m_ly = y;

  if(m_motion_mode == MOTION_MODE_ROTATE) {
    btVector3 y_axis(0, 1, 0);
    y_axis = m_camera_transform(y_axis);
    btVector3 camera_center(m_camera_center_distance, 0, 0);
    camera_center = m_camera_transform(camera_center);
    
    btTransform a(btQuaternion(0, 0, 0, 1), camera_center);

    m_camera_transform *= a.inverse();
    m_camera_transform *= btTransform(btQuaternion(y_axis, dx*M_PI));
    m_camera_transform *= btTransform(btQuaternion(btVector3(0, 0, 1), dx*M_PI));
    m_camera_transform *= a;
    
  } else if(m_motion_mode == MOTION_MODE_TRANSLATE) {
    
    btTransform other(btQuaternion(0, 0, 0, 1), btVector3(0, dx * 10, dy * 10));
    
    btTransform result(btQuaternion(0, 0, 0, 1));
    result.mult(m_camera_transform, other);
    m_camera_transform = result;
  }
  glutPostRedisplay();
}
