#include <CSoftBody.h>

CSoftBody::CSoftBody(IrrlichtDevice *device, irrBulletWorld *world, IMesh *mesh)
{
    Device = device;
    World = world;
    setType(E_ENTITY_SOFTBODY);

    isAeroEnabled = false;
    isSoftVersusSoftEnabled = false;

    Node = device->getSceneManager()->addMeshSceneNode(mesh);
    Node->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
    // Node->setMaterialTexture(0, Device->getVideoDriver()->getTexture("newspaper.png"));
    Node->setAutomaticCulling(EAC_OFF);

    Body = World->addSoftBody(Node);
    Body->setActivationState(EAS_DISABLE_DEACTIVATION);
}

CSoftBody::~CSoftBody()
{
}

void CSoftBody::setPosition(vector3df position)
{
    World->removeCollisionObject(Body, false);
    Node->setPosition(position);
    Body = World->addSoftBody(Node);
}

void CSoftBody::setAeroEnabled(bool enabled)
{
    if (enabled)
    {
        Body->getConfiguration().aeroModel = ESBAM_VERTEX_TWO_SIDED;
        Body->updateConfiguration();
    }
    else
    {
        Body->getConfiguration().dampingCoefficient = 0.0;
        Body->updateConfiguration();
    }

    isAeroEnabled = enabled;
}

IMeshSceneNode *CSoftBody::getNode()
{
    return Node;
}

void CSoftBody::setSoftCollisionEnabled(bool enabled)
{
    if (enabled)
    {
        Body->generateClusters(60.0f);
        Body->addCollisionFlag(ESBCM_CLUSTER_SOFT_VERSUS_SOFT);
    }
    else
    {

    }

    isSoftVersusSoftEnabled = enabled;
}

void CSoftBody::setLiftCoefficient(f32 lift)
{
    Body->getConfiguration().liftCoefficient = lift;
    Body->updateConfiguration();
}

void CSoftBody::setDragCoefficient(f32 drag)
{
    Body->getConfiguration().dragCoefficient = drag;
    Body->updateConfiguration();
}

void CSoftBody::setDampingCoefficient(f32 damping)
{
    Body->getConfiguration().dampingCoefficient = damping;
    Body->updateConfiguration();
}

void CSoftBody::setTotalMass(f32 mass, bool fromface=true)
{
    Body->setTotalMass(mass, fromface);
}

