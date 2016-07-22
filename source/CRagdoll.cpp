#include <CRagdoll.h>

CRagdoll::CRagdoll(IrrlichtDevice *device, irrBulletWorld *world, IAnimatedMesh *mesh)
{
    Device = device;
    Smgr = Device->getSceneManager();
    Video = Device->getVideoDriver();
    World = world;
    setType(E_ENTITY_RAGDOLL);

    Node = Smgr->addAnimatedMeshSceneNode(mesh);
    Node->setJointMode(irr::scene::EJUOR_CONTROL);
    //  Node->setRenderFromIdentity(true);

    //  IBoneSceneNode *test = Node->getJointNode(8);

////   if (test)
//   {
//       test->setSkinningSpace(irr::scene::EBSS_GLOBAL);
    //      test->setPosition(vector3df(1000,4000,800));
    //      IBoxShape *fun = new IBoxShape(test, 30.0f, true);
    //      World->addRigidBody(fun);
//   }

    unsigned int jointCount = Node->getJointCount();
    unsigned int index = 0;
    IBoneSceneNode *joint;
    for (index = 1; index < jointCount; index++)
    {
        joint = Node->getJointNode(index);
        printf("Test %a \n", joint->getBoneIndex());

        if (joint)
        {
            joint->setSkinningSpace(irr::scene::EBSS_GLOBAL);

            IBoxShape *fun = new IBoxShape(joint, 30.0f, true);
            World->addRigidBody(fun);
            Bodies[index] = World->addRigidBody(Shape);
        }
    }
}
