#include <CTextureArray.h>

CTextureArray::CTextureArray(IrrlichtDevice *device)
{
    textureCount = 0;
    Device = device;
    Video = Device->getVideoDriver();
}

CTextureArray::~CTextureArray(void)
{
 textureList->remove();
}

void CTextureArray::registerTexture(const io::path& filename)
{

}

void CTextureArray::registerTexture(ITexture *texture)
{

}
