#include "bulletRenderer.h"
#include <bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.h>  //for the shape types

//getCollisionObjectArray()

// all the individual shapes
#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>

#include "glut.h"

//for debugging
#include <iostream>

void render(const btCollisionObjectArray &objects) {
  //objects is actually a btAlignedObjectArray<class btCollisionObject*>
  for(int i = 0; i<objects.size(); i++) {
    render(objects[i]);
  }
}

void render(const btCollisionObject *object) {
  btScalar glMatrix[16];
  object->getWorldTransform().getOpenGLMatrix(glMatrix);
  glPushMatrix();
  glMultMatrixf(glMatrix);
  render(object->getCollisionShape());
  glPopMatrix();
}

void renderBox(const btBoxShape &shape) {
  const btVector3 &dimensions = shape.getHalfExtentsWithoutMargin();
  glPushMatrix();
  glScalef(dimensions.getX(), dimensions.getY(), dimensions.getZ());
  glutSolidCube(2);
  glPopMatrix();
}

void render(const btCollisionShape *shape) {
  switch(shape->getShapeType()) {
  case BOX_SHAPE_PROXYTYPE:
    renderBox(dynamic_cast<const btBoxShape&>(*shape));
    break;
  default:
    break;
  }
}

