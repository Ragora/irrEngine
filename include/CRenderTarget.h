#ifndef INCLUDE_RENDERTARGET
#define INCLUDE_RENDERTARGET

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CRenderTarget : public CEntity
{
public:
    CRenderTarget(IrrlichtDevice *device, ISceneNode *node);
    ~CRenderTarget(void);

    void setCameraPosition(vector3df position);
    void setDevice(IrrlichtDevice *device);

    void setFollowMode(bool enabled, ISceneNode *node);
    void setTrailMode(bool enabled, ISceneNode *node, bool keepOffset, bool keepRotation);

    ICameraSceneNode *getCamera();
    ISceneNode *getNode();
    ITexture *getTexture();

    void think();

    void setColor(SColor color);

private:
    IrrlichtDevice *Device;
    ISceneNode *Node;
    ITexture *Texture;
    ICameraSceneNode *Camera;
    ISceneManager *Smgr;
    IVideoDriver *Video;

    ISceneNode *followNode;
    ISceneNode *trailNode;

    bool followMode;
    bool trailMode;
    bool keepRotation;
    vector3df Rotation;

    SColor renderColor;
};
#endif
