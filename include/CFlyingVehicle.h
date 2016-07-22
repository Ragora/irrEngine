#ifndef INCLUDE_FLYINGVEHICLE
#define INCLUDE_FLYINGVEHICLE

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CFylingVehicle : public CEntity
{
 public:
  CFylingVehicle(IrrlichtDevice *device, irrBulletWorld *world, IMesh *mesh);
  ~CFylingVehicle(void);


 IAnimatedMeshSceneNode *getNode();
 void think();
 void addWheel(vector3df offset);


 private:
 IrrlichtDevice *Device;
 irrBulletWorld *World;
 ISceneManager *Smgr;
 IVideoDriver *Video;

 IRigidBody *Body;
 IRaycastVehicle *Vehicle;
 IAnimatedMeshSceneNode *Node;
 IGImpactMeshShape *Shape;
};
#endif
