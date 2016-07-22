#include <CRigidBody.h>

CRigidBody::CRigidBody(IrrlichtDevice *device, irrBulletWorld *world, IMesh *mesh)
{
    Device = device;
    World = world;
    setType(E_ENTITY_RIGIDBODY);

    Node = Device->getSceneManager()->addMeshSceneNode( mesh );

    Shape = new IGImpactMeshShape(Node, mesh, 30);
    Body = World->addRigidBody(Shape);
}

CRigidBody::~CRigidBody()
{
}

IMeshSceneNode *CRigidBody::getNode()
{
    return Node;
}

void CRigidBody::think()
{

}

void CRigidBody::setPosition(vector3df position)
{
    vector3df gravity = Body->getGravity();
    World->removeCollisionObject(Body, false);
    Node->setPosition(position);
    Body = World->addRigidBody(Shape);
    Body->setGravity(gravity);
}

void CRigidBody::setRotation(vector3df rotation)
{
    vector3df gravity = Body->getGravity();
    World->removeCollisionObject(Body, false);
    Node->setRotation(rotation);
    Body = World->addRigidBody(Shape);
    Body->setGravity(gravity);
}

void CRigidBody::setScale(vector3df scale)
{
    vector3df gravity = Body->getGravity();
    World->removeCollisionObject(Body, false);
    Node->setScale(scale);
    Body = World->addRigidBody(Shape);
    Body->setGravity(gravity);
}

void CRigidBody::setGravity(vector3df gravity)
{
    Body->setGravity(gravity);
}

vector3df CRigidBody::getPosition()
{
    return Node->getPosition();
}

vector3df CRigidBody::getRotation()
{
    return Node->getRotation();
}

vector3df CRigidBody::getScale()
{
    return Node->getScale();
}
