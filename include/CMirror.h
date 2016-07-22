#ifndef INCLUDE_MIRROR
#define INCLUDE_MIRROR

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CMirror : public CEntity
{
  public:
   CMirror(const CRenderTarget& test);
   ~CMirror(void);

  private:
};
#endif
