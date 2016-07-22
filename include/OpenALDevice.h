#ifndef INCLUDE_OPENALDEVICE
#define INCLUDE_OPENALDEVICE

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace video;
//Entities simply act as pointers for the engine to dynamically resolve
//thoughts and pointer issues

class OpenALDevice
{
public:
    OpenALDevice(void);
    ~OpenALDevice(void);

    E_ENTITY_TYPE getType();

private:
    CWaves *waveLoader;
};
#endif

