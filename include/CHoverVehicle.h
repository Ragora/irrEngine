#ifndef INCLUDE_HOVERVEHICLE
#define INCLUDE_HOVERVEHICLE

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CHoverVehicle : public CEntity
{
 public:
  CHoverVehicle(IrrlichtDevice *device, irrBulletWorld *world, IMesh *mesh);
  ~CHoverVehicle(void);


 IAnimatedMeshSceneNode *getNode();
 void think();

 private:
 IrrlichtDevice *Device;
 irrBulletWorld *World;
 ISceneManager *Smgr;
 IVideoDriver *Video;

 IAnimatedMeshSceneNode *Node;
 ISoftBody *Body;
 bool isAeroEnabled;
 bool isSoftVersusSoftEnabled;
};
#endif
