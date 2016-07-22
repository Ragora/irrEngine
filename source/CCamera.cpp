#include <CCamera.h>

CCamera::CCamera(IrrlichtDevice *device)
{
    Device = device;
    Smgr = Device->getSceneManager();
    Video = Device->getVideoDriver();

    setType(E_CAMERA_NORMAL);
}

void CCamera::setType(E_CAMERA_TYPE type)
{
    Type = type;
    if (Camera)
        Camera->remove();

    switch(Type)
    {
    case E_CAMERA_NORMAL:
        Camera = Smgr->addCameraSceneNode();
        break;
    }
}

E_CAMERA_TYPE CCamera::getType()
{
    return Type;
}
