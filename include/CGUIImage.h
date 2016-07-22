#ifndef INCLUDE_GUIIMAGE
#define INCLUDE_GUIIMAGE

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace video;

class CGUIImage : public CEntity
{
 public:
  CGUIImage(IrrlichtDevice *device);
  ~CGUIImage(void);

  void setScale(vector2df scale);
  void setRelativeScale(vector2df scale); //Does the same thing as setScale except it works as relative to the top left corner
  void setPosition(vector2df position);
  void setRelativePosition(vector2df position);

  vector2df getPosition();

  vector2df getScale();
  vector2df getRelativePosition();

  void setToolTipText(const wchar_t* text);
  void setImage(video::ITexture* image);

 private:
  IrrlichtDevice *Device;
  IVideoDriver *Video;
  IGUIEnvironment *Gui;
  IGUIImage *Image;
  vector2df Scale;
  ITexture *Texture;
};
#endif
