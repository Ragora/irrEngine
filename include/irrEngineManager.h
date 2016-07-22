#include <irrlicht.h>
#include <irrBullet.h>
#include <CInputHandle.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

//irr Klang Lib
#include <irrklang.h>
#include <irrKlangSceneNode.h>
using namespace irrklang;

// SPARK lib
#include <SPK.h>
#include <SPK_IRR.h>

using namespace SPK;
using namespace SPK::IRR;

// irrEngine Classes
#include <CEntity.h>
#include <CEntityGroup.h>
#include <CMasterGroup.h>
#include <stringOperations.h>
#include <vectorOperations.h>

#include <fileOperations.h>
#include <CMapLoader.h>
#include <CRigidBody.h>
#include <CStaticProp.h>
#include <CSoftBody.h>
#include <CTracerProjectile.h>
#include <CField.h>
#include <CLiquidBody.h>
#include <CRigidBox.h>
#include <CRenderTarget.h>
#include <CFPSController.h>
#include <CMirror.h>

// irrEngine Manager (simply create this, it handles everything for you.)
class irrEngineManager
{
public:
    irrEngineManager();
    ~irrEngineManager(void);

    void drawAll();
    IrrlichtDevice *getDevice();
    irrBulletWorld *getBulletWorld();
    ISceneManager *getSceneManger();
    IVideoDriver *getVideoDriver();

    void setGravity(vector3df gravity);

    void registerGroup(CEntityGroup *group);
    void cleanup();

    void setWindowCaption(const wchar_t* text);

    //Used by System
    void registerEntity(CEntity *entity);
    void unregisterEntity(unsigned int id);

    void setColor(SColor color);
    unsigned int getEntityCount();

    CEntity *getObject(unsigned int id);

    void setTimeScale(f32 time);

    ISoundEngine *getSoundEngine();

    void setActivePlayer(CFPSController *controller);

    //Registry Commands
    void registerStaticProp(CStaticProp *prop);
    void registerSoftBody(CSoftBody *body);
    void registerRigidBody(CRigidBody *body);
    void registerRigidBox(CRigidBox *box);
    void registerLiquidBody(CLiquidBody *body);
    void registerRenderTarget(CRenderTarget *target);
    void registerRagdoll(CRagdoll *ragdoll);
    void registerFPSController(CFPSController *controller);

    bool run();

private:
    unsigned int width;
    unsigned int height;

    IrrlichtDevice *Device;
    irrBulletWorld *World;
    ISceneManager *Smgr;
    IVideoDriver *Video;
    ISoundEngine *Sound;
    IGUIEnvironment *Gui;

    f32 timeScale;

    CFPSController *activePlayer;

    SColor renderColor;
    CMasterGroup *masterGroup;

    //Entity Table
    unsigned int entityCount;
    CEntity *entities[];

    //Tables begin
    unsigned int staticPropCount;
    CStaticProp *staticProps[];

    unsigned int softBodyCount;
    CSoftBody *softBodies[];

    unsigned int rigidBodyCount;
    CRigidBody *rigidBodies[];

    unsigned int rigidBoxCount;
    CRigidBox *rigidBoxes[];

    unsigned int liquidBodyCount;
    CLiquidBody *liquidBodies[];

    unsigned int renderTargetCount;
    CRenderTarget *renderTargets[];

    unsigned int ragdollCount;
    CRagdoll *ragdolls[];

    unsigned int fpsControllerCount;
    CFPSController *fpsControllers[];

};

