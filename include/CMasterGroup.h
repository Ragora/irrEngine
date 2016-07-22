#ifndef INCLUDE_MASTER
#define INCLUDE_MASTER

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class CMasterGroup
{
public:
    CMasterGroup(void);
    ~CMasterGroup(void);

    //Counts how many sub-groups exist under here
    unsigned int getCount();

    //Registers an entity to the master group
    void registerEntity(CEntity *entity);

    CEntity *getObject(unsigned int id);

    void cleanup();

private:
    unsigned int entityCount;
    CEntity *entities[];
};
#endif
