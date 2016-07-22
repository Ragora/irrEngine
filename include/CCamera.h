#ifndef INCLUDE_CAMERA
#define INCLUDE_CAMERA

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

enum E_CAMERA_TYPE
{
    E_CAMERA_NULL = 0,
    E_CAMERA_NORMAL = 1,
    E_CAMERA_FPS = 2,
    E_CAMERA_MAYA = 3,
    E_CAMERA_RTS = 4,
};

class CCamera : public CEntity
{
public:
    CCamera(IrrlichtDevice *device);
    ~CCamera(void);

    void setType(E_CAMERA_TYPE type);
    E_CAMERA_TYPE getType();

private:
    IrrlichtDevice *Device;
    ISceneManager *Smgr;
    IVideoDriver *Video;
    ICameraSceneNode *Camera;

    E_CAMERA_TYPE Type;
};
#endif
