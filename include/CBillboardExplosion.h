#ifndef INCLUDE_BILLBOARDEXPLOSION
#define INCLUDE_BILLBOARDEXPLOSION

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace video;

class CBillboardExplosion : public CEntity
{
 public:
  CBillboardExplosion(IrrlichtDevice *device, irrBulletWorld *world);
  ~CBillboardExplosion(void);

  //Defines how fast our animation is played
  void setSpeed(f32 speed);
  f32 getSpeed();
  void think();

 private:
 IrrlichtDevice *Device;
 irrBulletWorld *World;
 ISceneNode *Node;
};
#endif
