#ifndef INCLUDE_RIGIDBODY
#define INCLUDE_RIGIDBODY

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CRigidBody : public CEntity
{
 public:
  CRigidBody(IrrlichtDevice *device, irrBulletWorld *world, IMesh *mesh);
  ~CRigidBody(void);

  void setPosition(vector3df position);
  void setRotation(vector3df rotation);
  void setScale(vector3df scale);
  void setGravity(vector3df gravity);

  vector3df getPosition();
  vector3df getRotation();
  vector3df getScale();

 IMeshSceneNode *getNode();

 void think();

 private:
 IrrlichtDevice *Device;
 irrBulletWorld *World;
 IMeshSceneNode *Node;
 IGImpactMeshShape *Shape;
 IRigidBody *Body;
};
#endif
