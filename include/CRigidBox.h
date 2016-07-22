#ifndef INCLUDE_RIGIDBOX
#define INCLUDE_RIGIDBOX

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CRigidBox : public CEntity
{
 public:
  CRigidBox(IrrlichtDevice *device, irrBulletWorld *world);
  ~CRigidBox(void);

void think(void);
void setPosition(vector3df position);
void setRotation(vector3df rotation);
void setScale(vector3df scale);
void setGravity(vector3df gravity);
void setMaterialFlag(E_MATERIAL_FLAG flag, bool newvalue);

vector3df getPosition();
vector3df getRotation();
vector3df getScale();
vector3df getGravity();
core::aabbox3d<f32>& getBoundingBox();

void setMaterialTexture(f32 layer, ITexture *texture);

ISceneNode *getNode();


 private:
 IrrlichtDevice *Device;
 irrBulletWorld *World;
 IMeshSceneNode *Node;
 IBoxShape *Shape;
 IRigidBody *Body;
};
#endif
