#ifndef INCLUDE_RAGDOLL
#define INCLUDE_RAGDOLL

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CRagdoll : public CEntity
{
public:
    CRagdoll(IrrlichtDevice *device, irrBulletWorld *world, IAnimatedMesh *mesh);
    ~CRagdoll(void);
private:

IrrlichtDevice *Device;
irrBulletWorld *World;
ISceneManager *Smgr;
IVideoDriver *Video;
IAnimatedMeshSceneNode *Node;

IBoxShape *Shape;
IRigidBody *Bodies[];

};
#endif
