#include "ecs.h"

void initEntities(void)
{
    for (int32_t i = 0; i < MAX_ENTITIES; i++)
    {
        availableEntityArr[i] = i;
        entities[i] = -1;
    }
}

void updateAvailableEntities(void)
{
    int32_t count = 0;
    for (int32_t i = 0; i < MAX_ENTITIES; i++)
    {
        if (entities[i] == -1)
        {
            availableEntityArr[count++] = i;
        }
    }
    availableEntityCount = count;
}

int32_t getAvailableEntities(void)
{
    updateAvailableEntities();
    return availableEntityCount;
}

int32_t createEntity(void)
{
    if (entityCount >= MAX_ENTITIES)
    {
        puts("Error: Cant create more entities!");
        return -1;
    }
    printf("EntityID of current EntityCount: %d\n",entities[entityCount]);
    if (entities[entityCount] != -1)
    {
        availableEntityCount = getAvailableEntities();
        if (availableEntityCount > 0)
        {
            entityCount++;
            int32_t id = availableEntityArr[0];
            availableEntityArr[0] = -1;
            printf("Created entity id from createEntity(): %d\n", id);
            entities[id] = id;
            updateAvailableEntities();
            return id;
        } else return -1;
    }
    entityCount++;
    entities[entityCount] = entityCount;
    printf("Entitycount from createEntity(): %d\n", entityCount);
    return entityCount;
}

void removeEntity(int32_t EntityID)
{
    entities[EntityID] = -1;
    int32_t count = getAvailableEntities();
    availableEntityArr[count] = EntityID;
    entityCount--;
}

void attachComponent(int32_t EntityID, Component component)
{
    if (EntityID < 0)
    {
        puts("Error: EntityID below 0!");
        return;
    }
    uint32_t componentID = entityComponentCount[EntityID]++;
    printf("ComponentID = %d\n",componentID);
    if (componentID >= MAX_COMPONENTS)
    {
        printf("Error: Entity ID %d has already reached maximum amount of components!\n", EntityID);
        return;
    }
    componentArray[EntityID][componentID] = component;
}

int main(int argc, char* argv[])
{
    initEntities();

    int32_t gameEntites[MAX_ENTITIES];

    for (int32_t i = 0; i < MAX_ENTITIES ; i++)
    {
        gameEntites[i] = createEntity();
        entityComponentCount[i] = 0;
    }

    int32_t count = getAvailableEntities();

    printf("Available entity count = %d\n", count);
    printf("Current entity count = %d\n", entityCount);

    removeEntity(2);
    count = getAvailableEntities();
    puts("Removed entity 2");

    int32_t asd = createEntity();
    printf("asdasd: %d\n", asd);

    int32_t asd2 = createEntity();
    printf("asdasd2: %d\n", asd2);

    count = getAvailableEntities();

    printf("Available entity count = %d\n", count);
    printf("First available entity id = %d\n", availableEntityArr[0]);
    printf("Current entity count = %d\n", entityCount);

    attachComponent(421, VEL_COMPONENT);
    printf("421 component = %d\n", componentArray[421][0]);
    return 0;
}
