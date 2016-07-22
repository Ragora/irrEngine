#include <CEntityGroup.h>

CEntityGroup::CEntityGroup(void)
{
    Type = E_GROUP_NULL;
}

void CEntityGroup::think()
{

}

void CEntity::setType(E_ENTITY_TYPE type)
{
    Type = type;
}

void CEntityGroup::getType()
{
    return Type;
}
