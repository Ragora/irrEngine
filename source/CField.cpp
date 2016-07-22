#include <CField.h>

CField::CField(IrrlichtDevice *device, irrBulletWorld *world)
{
        Device = device;
        World = world;
        Node = Device->getSceneManager()->addCubeSceneNode();

//	Shape = new IBvhTriangleMeshShape(Node, Node->getMesh(), 0.0);
	//Shape->setMargin(0.07);
     //   Body = world->addRigidBody(Shape);
      //  Body->setCollisionFlags(ECF_STATIC_OBJECT);
}

CField::~CField()
{
 //delete Shape;
 //delete Body;
 Node->drop();
}

void CField::think()
{
 //Pretty much just an empty function so someone can define a think() on any child classes
}
