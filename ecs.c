#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_ENTITIES 1024
#define MAX_COMPONENTS 32 // Per entity

static int32_t entityCount = 0; 
static int32_t entities[MAX_ENTITIES];
static int32_t availableEntityArr[MAX_ENTITIES];
static int32_t availableEntityCount;

// typedef struct
// {
//     int32_t entities[MAX_ENTITIES];
//     int32_t availableEntityArr[MAX_ENTITIES];
//     int32_t availableEntityCount;
//
// } EntityRegistry;

void initEntities(EntityRegistry* registry)
{
    for (int32_t i = 0; i < MAX_ENTITIES; i++)
    { 
        registry->availableEntityArr[i] = -1;
        registry->entities[i] = -1;
    }
}

int32_t createEntity(void)
{
    if (entityCount >= MAX_ENTITIES)
    {
        puts("Cant create more entities!");
        return -1;
    }
    return entityCount++;
}

int32_t getAvailableEntities(EntityRegistry* registry)
{
    int32_t count = 0;
    for (int32_t i = 0; i < MAX_ENTITIES; i++)
    {
        if (registry->entities[i] == -1)
        {
            registry->availableEntityArr[count++] = i;
        }
    }
    return count;
}

void removeEntity(EntityRegistry* reg, int32_t EntityID)
{
    reg->entities[EntityID] = -1;
    int32_t count = getAvailableEntities(reg);
    reg->availableEntityArr[count] = EntityID;
    entityCount--;
}

typedef enum 
{
    NO_COMPONENT = 0,
    POS_COMPONENT,
    VEL_COMPONENT,
    SPRITE_COMPONENT,
} Component;

typedef struct
{
    float x, y;
} PositionComponent;

typedef struct
{
    uint32_t componentArray[MAX_ENTITIES][MAX_COMPONENTS];
    uint32_t entityComponentCount[MAX_ENTITIES];
    PositionComponent posComponents[100];
    uint32_t posComponentCount;

} ComponentRegistry;

void setComponent(ComponentRegistry* reg, int32_t EntityID, Component component)
{
    if (reg->entityComponentCount[EntityID] >= MAX_COMPONENTS)
    {
        printf("Entity ID %d has maximum amount of components!", EntityID);
        return;
    }
    uint32_t i = reg->entityComponentCount[EntityID]++;
    reg->componentArray[EntityID][i] = component;
}

void positionSystemUpdate(void)
{
}

int main(int argc, char* argv[])
{
    EntityRegistry er;
    initEntities(&er);

    for (int i = 0; i < MAX_ENTITIES ; i++)
    {
        er.entities[i] = createEntity();
        // printf(" Entity array: %d \n", er.entities[i]);
    }

    int32_t count = getAvailableEntities(&er);

    // printf("First available entity: %d \n", er.availableEntityArr[0]);

    printf("Available entity count = %d\n", count);
    // printf("First EntityID = %d \n", er.entities[0]);
    printf("Current entity count = %d\n", entityCount);
    // printf("available entity id:s %d , %d\n", er.availableEntityArr[0], er.availableEntityArr[1]);

    removeEntity(&er, 420);
    count = getAvailableEntities(&er);

    printf("Available entity count = %d\n", count);
    printf("Current entity count = %d\n", entityCount);


    return 0;
}
