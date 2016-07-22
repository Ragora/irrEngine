#include <OpenALDevice.h>

OpenALDevice::OpenALDevice(void)
{
    waveLoader = new CWaves();
}

OpenALDevice::~OpenALDevice(void)
{
    printf("irrEngine: Deinitializing OpenAL ...");
    delete waveLoader;
}
