#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_ENTITIES 1024
#define MAX_COMPONENTS 32 // Per entity

static int32_t entityCount = 0;
static int32_t availableEntityCount;

static int32_t entities[MAX_ENTITIES];
static int32_t availableEntityArr[MAX_ENTITIES];

static uint32_t componentArray[MAX_ENTITIES][MAX_COMPONENTS];
static uint32_t entityComponentCount[MAX_ENTITIES];

void initEntities(void);

void updateAvailableEntities(void);

int32_t getAvailableEntities(void);

int32_t createEntity(void);

void removeEntity(int32_t EntityID);

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

void attachComponent(int32_t EntityID, Component component);
