#include "ecs.h"

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
