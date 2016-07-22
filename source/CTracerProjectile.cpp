#include <CTracerProjectile.h>

CTracerProjectile::CTracerProjectile(IrrlichtDevice *device, irrBulletWorld *world)
{
        Device = device;
        World = world;

	//Shape = new IBvhTriangleMeshShape(Node, Node->getMesh(), 0.0);
//	shape->setMargin(0.07);
  //      Body = world->addRigidBody(Shape);
    //    Body->setCollisionFlags(ECF_STATIC_OBJECT);
}

CTracerProjectile::~CTracerProjectile()
{
// delete Shape;
// delete Body;
 Node->drop();
}

void CTracerProjectile::think()
{
 //Pretty much just an empty function so someone can define a think() on any child classes
}
