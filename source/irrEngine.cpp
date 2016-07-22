#define _DEBUG

#include <irrlicht.h>
#include <irrBullet.h>
#include <irrEngineManager.cpp>

//When our engine is called up
int main(int argc, char* argv[])
{
    //This is all that's needed to initialize the engine ... blahaha
    irrEngineManager *Manager = new irrEngineManager();
    IrrlichtDevice *Device = Manager->getDevice();
    ISceneManager *Smgr = Device->getSceneManager();
    IVideoDriver *Video = Device->getVideoDriver();
    irrBulletWorld *World = Manager->getBulletWorld();
    ISoundEngine *Sound = Manager->getSoundEngine();
    IGUIEnvironment *Gui = Device->getGUIEnvironment();
    ICursorControl *cursor = Device->getCursorControl();

    World->setGravity(vector3df(0,-100,0));
    Manager->setWindowCaption(L"irrEngine");

    Device->getFileSystem()->addZipFileArchive("map-20kdm2.pk3");

    //Scene Begin
    CStaticProp *prop = new CStaticProp(Device, World, Smgr->getMesh("20kdm2.bsp")->getMesh(0));
   // CGUIButton *button = new CGUIButton(Device);
    //  button->setRelativePosition(vector2df(720, 450));
   // button->setPosition(vector2df(720, 450));
   // button->setScale(vector2df(2,2));
    // Manager->registerStaticProp(prop);
    CGUIImage *image = new CGUIImage(Device);
  //  image->setImage(Video->getTexture("draakan.png"));
  //  image->setRelativePosition(vector2df(720, 450));
 //   image->setRelativeScale(vector2df(1,1));

   CRigidBox *box = new CRigidBox(Device, World);
   box->setScale(vector3df(5,5,5));
   box->setPosition(vector3df(715,1200,500));
    box->setMaterialFlag(EMF_LIGHTING, false);
    box->setMaterialTexture(0, Video->getTexture("textures/crate.jpg"));
   Manager->registerRigidBox(box);

//   CRenderTarget *rt = new CRenderTarget(Device, box->getNode());
//   rt->getCamera()->setPosition(vector3df(0,500,0));

    ICameraSceneNode *Camera = Smgr->addCameraSceneNodeFPS(0, 100.f, 0.0f, -1, 0, 0, true, 0.0, false, true);
  // ICameraSceneNode*Camera = Smgr->addCameraSceneNodeFPS();
    Smgr->addAnimatedMeshSceneNode(Smgr->getMesh("dwarf.x"));

   CIrrKlangSceneNode *Nodes = new CIrrKlangSceneNode(Sound, Smgr->getRootSceneNode(), Smgr, 666);
    Nodes->setMinMaxSoundDistance();
    Nodes->setSoundFileName("Menu.mp3");

    CFPSController *controller = new CFPSController(Device, World, Smgr->getMesh("dwarf.x"));
    Manager->registerFPSController(controller);
    Manager->setActivePlayer(controller);
  //  controller->setCameraOffset(vector3df(0,50,0));
    controller->setNodeOffset(vector3df(0,-10,0));
//   rt->setFollowMode(true, Camera);
//   rt->setTrailMode(true, Camera, true, true);
//   box->setMaterialTexture(0, rt->getTexture());

    //  Manager->registerRenderTarget(rt);
//
    //  CRagdoll *doll = new CRagdoll(Device, World, Smgr->getMesh("dwarf.x"));

    //Continue using Irrlicht as normal

    u32 TimeStamp = Device->getTimer()->getTime();
    u32 DeltaTime = 0;
    while (Manager->run())
    {
        //The Manager handles everything inside of this drawAll call
        DeltaTime = Device->getTimer()->getTime() - TimeStamp;
        TimeStamp = Device->getTimer()->getTime();
        World->stepSimulation(DeltaTime*0.001f, 120);
        Manager->drawAll();
    }

    //When the device is closed, delete the irrEngine manager to cause a "domino" effect of deletion :)
    delete Manager;

    if (Device)
        Device->drop();
}
