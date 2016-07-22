#ifndef INCLUDE_ENTITYGROUP
#define INCLUDE_ENTITYGROUP

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace video;

enum E_GROUP_TYPE
{
    E_GROUP_NULL = 0, //Used when entites are created but nothing is assigned to them
    E_GROUP_STATICPROP = 1,
    E_GROUP_SOFTBODY = 2,
    E_GROUP_RIGIDBODY = 3,
    E_GROUP_RIGIDBOX = 4,
    E_GROUP_LIQUIDBODY = 5,
    E_GROUP_RENDERTARGET = 6,
    E_GROUP_TRACERPROJECTILE = 7,
    E_GROUP_FIELD = 8,
    E_GROUP_TERRAIN = 9,
    E_GROUP_PLAYER = 10,
    E_GROUP_WHEELEDVEHICLE = 11,
    E_GROUP_RAGDOLL = 12,
};

class CEntityGroup
{
public:
    CEntityGroup(void);
    void think();
    E_GROUP_TYPE getType();
    void setType(E_GROUP_TYPE type);

private:
    E_GROUP_TYPE Type;
    unsigned int entityCount;
    CEntity *entityList[];
};
#endif
