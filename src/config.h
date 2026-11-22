#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define ARENA_CENTER_CIRCLE_RADIUS 150

#define ENTITY_PLACEMENT_PADDING 40
#define MAX_ENTITIES 3

typedef struct
{
    bool shouldRenderDebugEntityData;
} DynamicConfig;

#endif
