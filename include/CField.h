#ifndef INCLUDE_FIELD
#define INCLUDE_FIELD

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace video;

class CField
{
 public:
  CField(IrrlichtDevice *device, irrBulletWorld *world);
  ~CField(void);

  void think();

 private:
 IrrlichtDevice *Device;
 irrBulletWorld *World;
 ISceneNode *Node;
};
#endif
