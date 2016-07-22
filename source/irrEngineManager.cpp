#include <CInputHandle.h>
#include <CEntity.cpp>
#include <stringOperations.cpp>
#include <vectorOperations.cpp>
#include <fileOperations.cpp>

#include <irrKlangSceneNode.cpp>

#include <CCamera.cpp>
#include <CMapLoader.cpp>
#include <CRagdoll.cpp>
#include <CRigidBody.cpp>
#include <CStaticProp.cpp>
#include <CSoftBody.cpp>
#include <CTracerProjectile.cpp>
#include <CField.cpp>
#include <CLiquidBody.cpp>
#include <CRigidBox.cpp>
#include <CRenderTarget.cpp>
#include <CMirror.cpp>
#include <CGUIButton.cpp>
#include <CGUIImage.cpp>
#include <CFPSController.cpp>

#include <irrEngineManager.h>

//irrEngineManager functions
irrEngineManager::irrEngineManager()
{
    printf("irrEngine 1.3.1 initialize ...\n");
    width = 1024;
    height = 600;

    Device =
        createDevice( video::EDT_OPENGL, dimension2d<u32>(width, height), 32,
                      true, true, true, 0);
    Device->setWindowCaption(L"irrEngine Private Version");

    Smgr = Device->getSceneManager();
    Video = Device->getVideoDriver();
    World = createIrrBulletWorld(Device, true, true);
    Sound = createIrrKlangDevice();
    Gui = Device->getGUIEnvironment();

    World->setDebugMode(EPDM_DrawAabb |
                        EPDM_DrawContactPoints);

    timeScale = 1.0f;

    entityCount = 0;
    staticPropCount = 0;
    softBodyCount = 0;
    rigidBodyCount = 0;
    rigidBoxCount = 0;
    liquidBodyCount = 0;
    renderTargetCount = 0;
    fpsControllerCount = 0;
}

irrEngineManager::~irrEngineManager()
{
    printf("Deintializing engine ...\n");
    Sound->drop();
    delete World;
}

void irrEngineManager::registerEntity(CEntity *entity)
{
    entity->setID(entityCount);
    entities[entityCount] = entity;
    entityCount++;
}

void irrEngineManager::unregisterEntity(unsigned int id)
{

}

void irrEngineManager::drawAll()
{
    //Now that everyone has done what they want this iteration, render the scene
    Video->beginScene(true, true, renderColor);

    unsigned int index = 0;
    unsigned int count = entityCount;
    bool isDirty = false;

    for (index = 0; index < count; index++)
    {
        CEntity *entity = entities[index];

        if (entity)
        {
            E_ENTITY_TYPE type = entity->getType();
            unsigned int id = entity->getID();

            switch(type)
            {
                //Handle yout entity thinking here
            case E_ENTITY_STATICPROP:
                staticProps[id]->think();
                break;
            case E_ENTITY_SOFTBODY:
                softBodies[id]->think();
                break;
            case E_ENTITY_RIGIDBODY:
                rigidBodies[id]->think();
                break;
            case E_ENTITY_RIGIDBOX:
                rigidBoxes[id]->think();
                break;
            case E_ENTITY_LIQUIDBODY:
                liquidBodies[id]->think();
                break;
            case E_ENTITY_FPSCONTROLLER:
                if (fpsControllers[id])
                    fpsControllers[id]->think();
                break;
            case E_ENTITY_RENDERTARGET:
                if (renderTargets[id])
                    renderTargets[id]->think();
                break;
            }
        }
        else
            isDirty = true;
    }

    if (isDirty)
        cleanup();

    World->debugDrawWorld(true);

    Smgr->drawAll();
    Gui->drawAll();
    Video->endScene();
}

bool irrEngineManager::run()
{
    return Device->run();
}

void irrEngineManager::setColor(SColor color)
{
    renderColor = color;
}

irrBulletWorld *irrEngineManager::getBulletWorld()
{
    return World;
}

IrrlichtDevice *irrEngineManager::getDevice()
{
    return Device;
}

unsigned int irrEngineManager::getEntityCount()
{
    return 5;
}

//Group Registry


//Registry Commands
void irrEngineManager::registerStaticProp(CStaticProp *prop)
{
    unsigned int count = entityCount;
    registerEntity(prop);

    staticProps[count] = prop;
    staticPropCount++;
}

void irrEngineManager::registerSoftBody(CSoftBody *body)
{
    unsigned int count = entityCount;
    registerEntity(body);

    softBodies[count] = body;
    softBodyCount++;
}

void irrEngineManager::registerRigidBody(CRigidBody *body)
{
    unsigned int count = entityCount;
    registerEntity(body);

    rigidBodies[count] = body;
    rigidBodyCount++;
}

void irrEngineManager::registerRigidBox(CRigidBox *box)
{
    unsigned int count = entityCount;
    registerEntity(box);

    rigidBoxes[count] = box;
    rigidBoxCount++;
}

void irrEngineManager::registerLiquidBody(CLiquidBody *body)
{
    unsigned int count = entityCount;
    registerEntity(body);

    liquidBodies[count] = body;
    liquidBodyCount++;
}

void irrEngineManager::registerRenderTarget(CRenderTarget *target)
{
    unsigned int count = entityCount;
    registerEntity(target);

    renderTargets[count] = target;
    renderTargetCount++;
}

void irrEngineManager::registerRagdoll(CRagdoll *ragdoll)
{
    unsigned int count = entityCount;
    registerEntity(ragdoll);

    ragdolls[count] = ragdoll;
    ragdollCount++;
}

void irrEngineManager::registerFPSController(CFPSController *controller)
{
    unsigned int count = entityCount;
    registerEntity(controller);

    fpsControllers[count] = controller;
    fpsControllerCount++;
}

CEntity *irrEngineManager::getObject(unsigned int id)
{
    return entities[id];
}

void irrEngineManager::cleanup()
{
    unsigned int index = 0;
    unsigned int subIndex = 0;
    unsigned int count = entityCount;

    for (index = 0; index < count; index++)
    {
        CEntity *entity = entities[index];

        if (!entity)
        {
            for (subIndex = index; subIndex < count - index; subIndex++)
            {
                unsigned int id = subIndex++;
                entities[subIndex] = entities[id];
            }
        }
    }
}

void irrEngineManager::setGravity(vector3df gravity)
{
    World->setGravity(gravity);
}

void irrEngineManager::setTimeScale(f32 time)
{

}

void irrEngineManager::setWindowCaption(const wchar_t* text)
{
    Device->setWindowCaption(text);
}

ISoundEngine *irrEngineManager::getSoundEngine()
{
    return Sound;
}

void irrEngineManager::setActivePlayer(CFPSController *controller)
{
    if (activePlayer)
        activePlayer->setIsActive(false);

    activePlayer = controller;
    activePlayer->setIsActive(true);
}
