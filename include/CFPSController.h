#ifndef INCLUDE_FPSCONTROLLER
#define INCLUDE_FPSCONTROLLER

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CFPSController : public CEntity
{
 public:
  CFPSController(IrrlichtDevice *device, irrBulletWorld *world, IAnimatedMesh *mesh);
  ~CFPSController(void);

void think();
void setPosition(vector3df position);
void setRotation(vector3df rotation);
void setScale(vector3df scale);

void setMaterialFlag(E_MATERIAL_FLAG flag, bool newvalue);
void setMaterialTexture(f32 layer, ITexture *texture);
 void setIsActive(bool active);

IAnimatedMeshSceneNode *getNode();

vector3df getPosition();
vector3df getRotation();
vector3df getScale();
void setCameraOffset(vector3df offset);
void setNodeOffset(vector3df offset);

 private:
 IrrlichtDevice *Device;
 ISceneManager *Smgr;
 IVideoDriver *Video;
 IAnimatedMeshSceneNode *Node;
 IMeshSceneNode *Physics;

 bool isActive;
 bool isMoving;

 vector3df cameraOffset;
 vector3df nodeOffset;

 irrBulletWorld *World;
 IBoxShape *Shape;
 IRigidBody *Body;
};
#endif
