#include <CEntity.h>

CEntity::CEntity(void)
{
    entityId = 0; //My ID has not been set.
    Type = E_ENTITY_NULL; //Our reference is NULL
    Collision = E_COLLISION_NULL; //No sound unless this is set
    useScheme = false;
}

E_ENTITY_TYPE CEntity::getType()
{
    return Type;
}

unsigned int CEntity::getID()
{
    return entityId;
}

void CEntity::setType(E_ENTITY_TYPE type)
{
    Type = type;
}

void CEntity::setMaterial(E_COLLISION_TYPE type)
{
    Collision = type;
}

void CEntity::setID(unsigned int id)
{
    entityId = id;
}

void CEntity::think()
{

}

CInputHandle *CEntity::getControlScheme()
{
    if (!useScheme)
        return 0;
    else
        return Scheme;
}

void CEntity::setControlSchemeEnable(bool enable)
{
    useScheme = enable;

    if (enable)
        Scheme = new CInputHandle();
    else if (Scheme)
        delete Scheme;
}
