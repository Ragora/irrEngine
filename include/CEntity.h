#ifndef INCLUDE_CENTITY
#define INCLUDE_CENTITY

#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace video;

enum E_ENTITY_TYPE
{
    E_ENTITY_NULL = 0, //Used when entites are created but nothing is assigned to them
    E_ENTITY_STATICPROP = 1,
    E_ENTITY_SOFTBODY = 2,
    E_ENTITY_RIGIDBODY = 3,
    E_ENTITY_RIGIDBOX = 4,
    E_ENTITY_LIQUIDBODY = 5,
    E_ENTITY_RENDERTARGET = 6,
    E_ENTITY_TRACERPROJECTILE = 7,
    E_ENTITY_FIELD = 8,
    E_ENTITY_TERRAIN = 9,
    E_ENTITY_PLAYER = 10,
    E_ENTITY_WHEELEDVEHICLE = 11,
    E_ENTITY_RAGDOLL = 12,
    E_ENTITY_FPSCONTROLLER = 13,
};

enum E_COLLISION_TYPE
{
  E_COLLISION_NULL = 0,
  E_COLLISION_SOIL = 1,
  E_COLLISION_STONE = 2,
  E_COLLISION_FLESH = 3,
  E_COLLISION_GLASS = 4,
  E_COLLISION_WOOD = 5,
  E_COLLISION_WATER = 6,
};

//Entities simply act as pointers for the engine to dynamically resolve
//thoughts and pointer issues
class CEntity
{
public:
     CEntity(void);

     E_ENTITY_TYPE getType();
     unsigned int getID();

     void setType(E_ENTITY_TYPE type);
     void setID(unsigned int id);

     void setMaterial(E_COLLISION_TYPE type);
     void setControlSchemeEnable(bool enable);

     CInputHandle *getControlScheme();

      //Think is defined here, but not coded so you can program
      //Your own high-level think on your entities
     void think();

private:
     bool useScheme;
     CInputHandle *Scheme;
     E_ENTITY_TYPE Type;
     E_COLLISION_TYPE Collision;
     unsigned int entityId; //Used by the engine for entity selection
};
#endif

