#ifndef __MAZE_PLAYER_H__
#define __MAZE_PLAYER_H__

#include "config.h"
#include "map.h"

MAZE typedef struct
{
    Vector2 position;
    Vector2 camera;
    Vector2 direction;    
    Vector2 dimension;

    float angle;
} Player_t;


#if defined(__cplusplus)
    extern "C" {
#endif

    MAZE Player_t *create_player(Vector2 position);
    MAZE void update_player(Player_t *const player, const Map_t *const map);
    MAZE void draw_player(const Player_t *const player);
    MAZE void destroy_player(Player_t **ptr);

#if defined(__cplusplus)
    }
#endif

#endif
