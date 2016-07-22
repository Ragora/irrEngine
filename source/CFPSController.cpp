#include <CFPSController.h>

CFPSController::CFPSController(IrrlichtDevice *device, irrBulletWorld *world, IAnimatedMesh *mesh)
{
    setControlSchemeEnable(true);
    setType(E_ENTITY_FPSCONTROLLER);
    cameraOffset = vector3df(0,0,0);
    nodeOffset = vector3df(0,0,0);
    isMoving = false;
    isActive = false;

    Device = device;
    World = world;
    Smgr = Device->getSceneManager();
    Video = Device->getVideoDriver();

    Physics = Smgr->addCubeSceneNode();
    Physics->setScale(vector3df(5,7,5));
    // Physics->setPosition(vector3df(715,700,500));
    Physics->setMaterialFlag(EMF_LIGHTING, false);

    Node = Smgr->addAnimatedMeshSceneNode(mesh);
    Smgr->getActiveCamera()->setPosition(vector3df(715,2100,500));
    Node->setPosition(vector3df(715,5000,500));
    //  Node->setPosition(vector3df(715,700,500));
    Physics->setPosition(vector3df(715,5000,500));

    Node->setMaterialFlag(EMF_LIGHTING, false);
    Shape = new IBoxShape(Physics, 30.0f, false);

    Body = World->addRigidBody(Shape);
}

CFPSController::~CFPSController(void)
{

}

void CFPSController::think()
{
//   vector3df cameraRotation = Smgr->getActiveCamera()->getRotation();
//   Node->setRotation(vector3df(0,cameraRotation.Y * -1,0));
    if (!isActive)
        return;

    CInputHandle *input = getControlScheme();
    Device->setEventReceiver(input);


    vector3df velocity = Body->getLinearVelocity();
    vector3df localForward(0,0,0);
    vector3df vel(0,0,0);

    if (input->IsKeyDown(irr::KEY_KEY_W))
    {
        isMoving = true;
        localForward.Z = 0.025f * 2000;
        localForward.Y = 0.0f;

        const matrix4& mat = Smgr->getActiveCamera()->getAbsoluteTransformation();
        mat.rotateVect(vel, localForward);
        velocity.Y = velocity.Y;

        Body->setLinearVelocity(velocity);
    }
    else
    {
        isMoving = false;
        Body->setLinearVelocity(vector3df(0,velocity.Y,0));
    }


    vector3df cameraRot = Smgr->getActiveCamera()->getRotation();

    matrix4 mat = Physics->getAbsoluteTransformation();

    mat.setRotationDegrees( vector3df(0.0f, cameraRot.Y, 0.0f) );
    Body->setWorldTransform(mat);
    //Now detect if something is pressed

    Smgr->getActiveCamera()->setPosition(Physics->getPosition() + cameraOffset);

    Node->setPosition(Physics->getPosition() + nodeOffset);

    vector3df physicsRot = Physics->getRotation();
    Node->setRotation(vector3df(0, cameraRot.Y - 180, 0));

}

IAnimatedMeshSceneNode *CFPSController::getNode()
{
    return Node;
}

void CFPSController::setCameraOffset(vector3df offset)
{
    cameraOffset = offset;
}

void CFPSController::setNodeOffset(vector3df offset)
{
    nodeOffset = offset;
}

void CFPSController::setIsActive(bool active)
{
    isActive = active;
}
