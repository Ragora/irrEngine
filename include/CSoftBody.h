#ifndef INCLUDE_SOFTBODY
#define INCLUDE_SOFTBODY

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CSoftBody : public CEntity
{
 public:
  CSoftBody(IrrlichtDevice *device, irrBulletWorld *world, IMesh *mesh);
  ~CSoftBody(void);

 void setPosition(vector3df position);
 void setAeroEnabled(bool enabled);
 void setSoftCollisionEnabled(bool enabled);

 void setLiftCoefficient(f32 lift);
 void setDragCoefficient(f32 drag);
 void setDampingCoefficient(f32 damping);
 void setTotalMass(f32 mass, bool fromfaces);

 IMeshSceneNode *getNode();

 private:
 IrrlichtDevice *Device;
 irrBulletWorld *World;
 IMeshSceneNode *Node;
 ISoftBody *Body;
 bool isAeroEnabled;
 bool isSoftVersusSoftEnabled;
};
#endif
