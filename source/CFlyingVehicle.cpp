#include <CFlyingVehicle.h>

CFylingVehicle::CFylingVehicle(IrrlichtDevice *device, irrBulletWorld *world, IMesh *mesh)
{
    Device = device;
    World = world;
    Smgr = Device->getSceneManager();
    Video = Device->getVideoDriver();

    Node = Device->getSceneManager()->addAnimatedMeshSceneNode(mesh);
    Node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    Shape = new IGImpactMeshShape(Node, mesh, 30.0f);
    Body = world->addRigidBody(shape);
	Body->includeNodeOnRemoval(false);

    Body->getAttributes()->addBool("isVehicle", true);
    Body->getAttributes()->addBool("isDestroyable", true);
    Body->getAttributes()->addBool("isDestroyed", false);
    Body->setActivationState(EAS_DISABLE_DEACTIVATION);

    Vehicle = World->addRaycastVehicle(Tank);
    Tank->setVehicleReference(Vehicle);
}

CFylingVehicle::~CFylingVehicle(void)
{
    Node->remove();
}

void CFylingVehicle::think()
{

}

IAnimatedMeshSceneNode *CFylingVehicle::getNode()
{
    return Node;
}

void CFylingVehicle::addWheel(vector3df offset)
{
    SWheelInfoConstructionInfo wheel;
    wheel.chassisConnectionPointCS = irr::core::vector3df(0.0,-0.88,4.0);
    wheel.wheelDirectionCS = irr::core::vector3df(0.0,-1,0.0);
    wheel.wheelAxleCS = irr::core::vector3df(-2,0.0,0.0);
    wheel.suspensionRestLength = 0.6;
    wheel.wheelRadius = 8.0;
    wheel.isFrontWheel = false;

    wheel.chassisConnectionPointCS = offset;
    Vehicle->addWheel(wheel);
}
