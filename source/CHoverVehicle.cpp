#include <CHoverVehicle.h>

CHoverVehicle::CHoverVehicle(IrrlichtDevice *device, irrBulletWorld *world, IMesh *mesh)
{
    Device = device;
    World = world;
    Smgr = Device->getSceneManager();
    Video = Device->getVideoDriver();

    Node = Device->getSceneManager()->addAnimatedMeshSceneNode(mesh);
    Node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

CHoverVehicle::~CHoverVehicle(void)
{
    Node->remove();
}

IAnimatedMeshSceneNode *CHoverVehicle::getNode()
{
    return Node;
}

void CHoverVehicle::think()
{

}
