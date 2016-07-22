#ifndef INCLUDE_WHEELEDVEHICLE
#define INCLUDE_WHEELEDVEHICLE

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CWheeledVehicle : public CEntity
{
 public:
  CWheeledVehicle(IrrlichtDevice *device, irrBulletWorld *world, IMesh *mesh);
  ~CWheeledVehicle(void);


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
