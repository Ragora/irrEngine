#ifndef INCLUDE_TEXTUREARRAY
#define INCLUDE_TEXTUREARRAY

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CTextureArray : public CEntity
{
public:
    CTextureArray(IrrlichtDevice *device);
    ~CTextureArray(void);

    ITexture *getTextureList();
    ITexture *getTexture(unsigned int id);
    unsigned int getCount();

    void registerTexture(const io::path& filename);
    void registerTexture(ITexture *texture);
    void removeTexture(unsigned int id);

    void cleanup();
    void think();
private:
    unsigned int textureCount;
    IrrlichtDevice *Device;
    IVideoDriver *Video;
    ITexture *textureList[];
};
#endif
