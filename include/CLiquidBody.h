#ifndef INCLUDE_LIQUIDBODY
#define INCLUDE_LIQUIDBODY

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CLiquidBody : public CEntity
{
  public:
   CLiquidBody(IrrlichtDevice *device, irrBulletWorld *world);
   ~CLiquidBody(void);

   void think();
  private:
  IrrlichtDevice *Device;
  irrBulletWorld *World;
  ILiquidBody *Body;
  ISceneNode *Node;
};
#endif
