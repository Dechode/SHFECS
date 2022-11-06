#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_ENTITIES 1024
#define MAX_COMPONENTS 32 // Per entity

static int32_t entityCount = 0; 
static int32_t availableEntityCount;

static int32_t entities[MAX_ENTITIES];
static int32_t availableEntityArr[MAX_ENTITIES];

void initEntities(void)
{
    for (int32_t i = 0; i < MAX_ENTITIES; i++)
    { 
        availableEntityArr[i] = i;
        entities[i] = -1;
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

int32_t getAvailableEntities(void)
{
    int32_t count = 0;
    for (int32_t i = 0; i < MAX_ENTITIES; i++)
    {
        if (entities[i] == -1)
        {
            availableEntityArr[count++] = i;
        }
    }
    return count;
}

void removeEntity(int32_t EntityID)
{
    entities[EntityID] = -1;
    int32_t count = getAvailableEntities();
    availableEntityArr[count] = EntityID;
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

void attachComponent(ComponentRegistry* reg, int32_t EntityID, Component component)
{
    if (reg->entityComponentCount[EntityID] >= MAX_COMPONENTS)
    {
        printf("Entity ID %d has already reached maximum amount of components!\n", EntityID);
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
    initEntities();

    for (int i = 0; i < MAX_ENTITIES ; i++)
    {
       entities[i] = createEntity();
    }

    int32_t count = getAvailableEntities();

    printf("Available entity count = %d\n", count);
    printf("Current entity count = %d\n", entityCount);

    removeEntity(420);
    count = getAvailableEntities();

    printf("Available entity count = %d\n", count);
    printf("First available entity id = %d\n", availableEntityArr[0]);
    printf("Current entity count = %d\n", entityCount);

    return 0;
}
