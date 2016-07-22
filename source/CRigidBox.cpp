#include <CRigidBox.h>

CRigidBox::CRigidBox(IrrlichtDevice *device, irrBulletWorld *world)
{
    Device = device;
    World = world;
    setType(E_ENTITY_RIGIDBOX);

    Node = Device->getSceneManager()->addCubeSceneNode();
    Shape = new IBoxShape(Node, 30.0f, true);
    Body = World->addRigidBody(Shape);
}

CRigidBox::~CRigidBox()
{
// delete Shape;
// delete Body;
    Node->drop();
}

void CRigidBox::think()
{
//Pretty much just an empty function so someone can define a think() on any child classes
}

void CRigidBox::setPosition(vector3df position)
{
    vector3df gravity = Body->getGravity();
    World->removeCollisionObject(Body, false);
    Node->setPosition(position);
    Body = World->addRigidBody(Shape);
    Body->setGravity(gravity);
}

void CRigidBox::setRotation(vector3df rotation)
{
    vector3df gravity = Body->getGravity();
    World->removeCollisionObject(Body, false);
    Node->setRotation(rotation);
    Body = World->addRigidBody(Shape);
    Body->setGravity(gravity);
}

ISceneNode *CRigidBox::getNode()
{
    return Node;
}

void CRigidBox::setScale(vector3df scale)
{
    vector3df gravity = Body->getGravity();
    World->removeCollisionObject(Body, false);
    Shape->setLocalScaling(scale, ESP_BOTH);
    Body = World->addRigidBody(Shape);
    Body->setGravity(gravity);
}

void CRigidBox::setMaterialTexture(f32 layer, ITexture *texture)
{
    Node->setMaterialTexture(layer, texture);
}

void CRigidBox::setMaterialFlag(E_MATERIAL_FLAG flag, bool newvalue)
{
    Node->setMaterialFlag(flag, newvalue);
}

void CRigidBox::setGravity(vector3df gravity)
{
    Body->setGravity(gravity);
}

vector3df CRigidBox::getPosition()
{
    return Node->getPosition();
}

vector3df CRigidBox::getRotation()
{
    return Node->getRotation();
}

vector3df CRigidBox::getScale()
{
    return Node->getScale();
}

vector3df CRigidBox::getGravity()
{
    return Body->getGravity();
}

//core::aabbox3d<f32>& CRigidBox::getBoundingBox()
//{
//    return Node->getBoundingBox();
//}
