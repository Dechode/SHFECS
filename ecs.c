#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_ENTITIES 1024
#define MAX_COMPONENTS 32

static int32_t entityCount = 0; 

typedef struct
{
    int32_t entities[MAX_ENTITIES];
    int32_t availableEntityArr[MAX_ENTITIES];
    int32_t availableEntityCount;
      
} EntityRegistry;

typedef struct
{
    float x, y;
} PositionComponent;

int32_t createEntity(void)
{   
    if (entityCount >= MAX_ENTITIES)
    {
        puts("Cant create more entities!");
        return -1;
    }
    return entityCount++;
}

void initEntities(EntityRegistry* registry)
{
    for (int32_t i = 0; i < MAX_ENTITIES; i++)
    { 
        registry->availableEntityArr[i] = -1;
        registry->entities[i] = -1;
    }
}

int32_t getAvilableEntities(EntityRegistry* registry)
{
    int32_t count = 0;
    for (int32_t i = 0; i < MAX_ENTITIES; i++)
    {
        if (registry->entities[i] == -1)
        {
            count++;
            registry->availableEntityArr[count - 1] = i;
        }
    }
    return count;
}

typedef enum 
{
    NO_COMPONENT = 0,
    PosComponent,
} ComponentList;

typedef struct
{
    uint32_t componentArray[MAX_ENTITIES][MAX_COMPONENTS];
    uint32_t entityComponentCount[MAX_ENTITIES];
} ComponentRegistry;

void setComponent(ComponentRegistry* reg, int32_t EntityID, ComponentList component)
{
    reg->entityComponentCount[EntityID] += 1;
    uint32_t i = reg->entityComponentCount[EntityID];
    reg->componentArray[EntityID][i] = component;
}

void positionSystemUpdate(void)
{
    uint32_t posComponentCount = 0;
    for (uint32_t i = 0; i < posComponentCount; i++)
    {
      // posComponentPool[i].positionUpdate() 
    }
}

int main(int argc, char* argv[])
{
    EntityRegistry er;
    initEntities(&er);

    for (int i = 0; i < MAX_ENTITIES + 1; i++)
    {
        er.entities[i] = createEntity();
        printf(" Entity array: %d \n", er.entities[i]);
    }

    int32_t count = getAvilableEntities(&er);

    printf(" First available entity: %d \n", er.availableEntityArr[0]);

    printf("Available entity count = %d\n", count);
    printf("First EntityID = %d \n", er.entities[0]);
    printf("Current entity count = %d\n", entityCount);
    printf("available entity id:s %d , %d\n", er.availableEntityArr[0], er.availableEntityArr[1]);

    return 0;
}
