#ifndef INCLUDE_TRACERPROJECTILE
#define INCLUDE_TRACERPROJECTILE

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace video;

class CTracerProjectile
{
 public:
  CTracerProjectile(IrrlichtDevice *device, irrBulletWorld *world);
  ~CTracerProjectile(void);

  void think();

 private:
 IrrlichtDevice *Device;
 irrBulletWorld *World;
 ISceneNode *Node;
};
#endif
