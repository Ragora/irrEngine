#include <CStaticProp.h>

CStaticProp::CStaticProp(IrrlichtDevice *device, irrBulletWorld *world, IMesh *mesh)
{
    Device = device;
    World = world;
    setType(E_ENTITY_STATICPROP);

    Node = Device->getSceneManager()->addMeshSceneNode( mesh );

	Shape = new IBvhTriangleMeshShape(Node, mesh, 0.0);
    Body = World->addRigidBody(Shape);
    Body->setCollisionFlags(ECF_STATIC_OBJECT);
}

CStaticProp::~CStaticProp()
{
    Node->drop();
}

void CStaticProp::think()
{
//Pretty much just an empty function so someone can define a think() on any child classes
}

void CStaticProp::setPosition(vector3df position)
{
    vector3df gravity = Body->getGravity();
    World->removeCollisionObject(Body, false);
    Node->setPosition(position);
    Body = World->addRigidBody(Shape);
    Body->setGravity(gravity);
}

void CStaticProp::setRotation(vector3df rotation)
{
    vector3df gravity = Body->getGravity();
    World->removeCollisionObject(Body, false);
    Node->setRotation(rotation);
    Body = World->addRigidBody(Shape);
    Body->setGravity(gravity);
}

void CStaticProp::setScale(vector3df scale)
{
    vector3df gravity = Body->getGravity();
    World->removeCollisionObject(Body, false);
    Shape->setLocalScaling(scale, ESP_BOTH);
    Body = World->addRigidBody(Shape);
    Body->setGravity(gravity);
}

IMeshSceneNode *CStaticProp::getNode()
{
    return Node;
}

vector3df CStaticProp::getPosition()
{
    return Node->getPosition();
}

vector3df CStaticProp::getRotation()
{
    return Node->getRotation();
}

vector3df CStaticProp::getScale()
{
    return Node->getScale();
}

void CStaticProp::setMaterialFlag(E_MATERIAL_FLAG flag, bool newvalue)
{
    Node->setMaterialFlag(flag, newvalue);
}

void CStaticProp::setMaterialTexture(f32 layer, ITexture *texture)
{
    Node->setMaterialTexture(layer, texture);
}
