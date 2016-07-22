#ifndef INCLUDE_GUIBUTTON
#define INCLUDE_GUIBUTTON

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace video;

class CGUIButton : public CEntity
{
 public:
  CGUIButton(IrrlichtDevice *device);
  ~CGUIButton(void);

  void setScale(vector2df scale);
  void setRelativeScale(vector2df scale); //Does the same thing as setScale except it works as relative to the top left corner
  void setPosition(vector2df position);
  void setRelativePosition(vector2df position);

  vector2df getScale();
  vector2df getRelativePosition();

  void setToolTipText(const wchar_t* text);

 private:
  IrrlichtDevice *Device;
  IVideoDriver *Video;
  IGUIEnvironment *Gui;
  IGUIButton *Button;
  vector2df Scale;
};
#endif
