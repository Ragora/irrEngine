#ifndef INCLUDE_STATICPROP
#define INCLUDE_STATICPROP

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CStaticProp : public CEntity
{
 public:
  CStaticProp(IrrlichtDevice *device, irrBulletWorld *world, IMesh *mesh);
  ~CStaticProp(void);

void think(void);
void setPosition(vector3df position);
void setRotation(vector3df rotation);
void setScale(vector3df scale);

void setMaterialFlag(E_MATERIAL_FLAG flag, bool newvalue);
void setMaterialTexture(f32 layer, ITexture *texture);

vector3df getPosition();
vector3df getRotation();
vector3df getScale();

IMeshSceneNode *getNode();


 private:
 IrrlichtDevice *Device;
 irrBulletWorld *World;
 IMeshSceneNode *Node;
 IBvhTriangleMeshShape *Shape;
 IRigidBody *Body;
};
#endif
