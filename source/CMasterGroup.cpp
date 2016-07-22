#include <CMasterGroup.h>

CMasterGroup::CMasterGroup()
{
    entityCount = 0;
}

CMasterGroup::~CMasterGroup()
{
}

unsigned int CMasterGroup::getCount()
{
    return entityCount;
}

void CMasterGroup::cleanup()
{
    unsigned int index = 0;
    unsigned int subIndex = 0;
    unsigned int count = entityCount;

    for (index = 0; index < count; index++)
    {
        CEntity *entity = entities[index];

        if (!entity)
        {
            for (subIndex = index; subIndex < count - index; subIndex++)
            {
                unsigned int id = subIndex++;
                entities[subIndex] = entities[id];
            }
        }
    }
}

void CMasterGroup::registerEntity(CEntity *entity)
{
    entity->setID(entityCount);
    entities[entityCount] = entity;
    entityCount++;
}

CEntity *CMasterGroup::getObject(unsigned int id)
{
    return entities[id];
}
