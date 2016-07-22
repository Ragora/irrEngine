#include <CRenderTarget.h>

CRenderTarget::CRenderTarget(IrrlichtDevice *device, ISceneNode *node)
{
    Device = device;
    Smgr = Device->getSceneManager();
    Video = Device->getVideoDriver();
    followMode = false;
    followNode = 0;
    Rotation = vector3df(0,0,0);
    setType(E_ENTITY_RENDERTARGET);

    renderColor = SColor(0,0,0,255);

    Node = node;
    Texture = Video->addRenderTargetTexture(core::dimension2d<u32>(1024,1024), "RTT1");
    Node->setMaterialTexture(0, Texture);

    Camera = Smgr->addCameraSceneNode(0, vector3df(0,0,0), vector3df(0,0,100), -1, false);
}

CRenderTarget::~CRenderTarget()
{
    Node->remove();
}

//CRenderTarget&CEntity;

void CRenderTarget::think()
{
    ICameraSceneNode *Return = Smgr->getActiveCamera();
    Smgr->setActiveCamera(Camera);
    Video->setRenderTarget(Texture, true, true, renderColor);

    if (followMode)
        if (followNode)
            Camera->setTarget(followNode->getPosition());
        else
            Camera->setTarget(Node->getPosition());

    if (trailMode)
        if (keepRotation)
        {
            Camera->setParent(0);
            Camera->setRotation(Rotation);
            Camera->setParent(trailNode);
        }
    Smgr->drawAll();

    Smgr->setActiveCamera(Return);
    Video->setRenderTarget(0, true, true, SColor(0, 135, 206, 250));
    Smgr->drawAll();
}

void CRenderTarget::setCameraPosition(vector3df position)
{
    Camera->setPosition(position);
}

ICameraSceneNode *CRenderTarget::getCamera()
{
    return Camera;
}

ISceneNode *CRenderTarget::getNode()
{
    return Node;
}

ITexture *CRenderTarget::getTexture()
{
    return Texture;
}

void CRenderTarget::setColor(SColor color)
{
    renderColor = color;
}

void CRenderTarget::setDevice(IrrlichtDevice *device)
{
    Device = device;
}

//follow mode. If node is not specified, the camera will watch its parent Node
void CRenderTarget::setFollowMode(bool enabled, ISceneNode *node=0)
{
    followMode = enabled;
    followNode = node;
}

void CRenderTarget::setTrailMode(bool enabled, ISceneNode *node=0, bool keepOffset=false, bool keeprotation=false)
{
    if (node)
        trailNode = node;
    else
        trailNode = Node;

    if (keepOffset)
        Camera->setParent(trailNode);
    if (keepRotation)
        Rotation = Camera->getRotation();

    keepRotation = keeprotation;
    trailMode = enabled;
}
