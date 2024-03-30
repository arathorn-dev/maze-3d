#include "includes/player.h"
#include "includes/raylib.h"
#include "includes/raymath.h"
#include <math.h>

//----------------------------------------------------------------------------------
//  Statics function declaration.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
    extern "C" {
#endif

    MAZE static void _movement_player(Player_t *const player, const Map_t *const map);
    MAZE static void _rotation_player(Player_t *const player);    

#if defined(__cplusplus)
    }
#endif

//----------------------------------------------------------------------------------
//  Public function implementation.
//----------------------------------------------------------------------------------

MAZE  Player_t *create_player(Vector2 position)
{
    Player_t *player = MemAlloc(sizeof(Player_t));
    if (player == NULL)
    {
        TraceLog(LOG_DEBUG, "Error to create Player_t pointer.");
        return NULL;
    }

    player->position = position;
    player->dimension = (Vector2){.x=1, .y=1};
    player->angle = 0.0f;

    player->direction = (Vector2){.x=-1, .y=0};
    player->camera = (Vector2){.x=0, .y=0.66};

    TraceLog(LOG_DEBUG, "Player_t pointer created successfully.");
    return player;
}

MAZE  void update_player(Player_t *const player, const Map_t *const map)
{
    _movement_player(player, map);
    _rotation_player(player);
}

MAZE  void draw_player(const Player_t *const player)
{
    Vector2 pos = player->position;
    Vector2 dir = player->direction;
    DrawLine(
        pos.x,
        pos.y,
        pos.x + (10.5 * dir.x),
        pos.y + (10.5 * dir.y),
        GREEN
    );
    
    DrawRectangle(
        player->position.x,
        player->position.y,
        player->dimension.x,
        player->dimension.y,
        RAYWHITE
    );

}

MAZE  void destroy_player(Player_t **ptr)
{
    if ((*ptr) != NULL)
    {
        MemFree((*ptr));
        (*ptr) = NULL;
        TraceLog(LOG_DEBUG, "Player_t pointer destroyed successfully.");
    }  
}

//----------------------------------------------------------------------------------
//  Statics function implementation.
//----------------------------------------------------------------------------------
MAZE static void _movement_player(Player_t *const player, const Map_t *const map )
{
    Vector2 direction = {0};
    float angle = player->angle;
    if (IsKeyDown(KEY_W))
    {
        direction.y = -1 * sinf(angle);
    }
    else if (IsKeyDown(KEY_S))
    {
        direction.y = 1 * sinf(angle);
    }
    else if (IsKeyDown(KEY_A))
    {
        direction.x = -1 * cosf(angle);
    }
    else if (IsKeyDown(KEY_D))
    {
        direction.x = 1 * cosf(angle);
    }

    Vector2 position = Vector2Add(player->position, direction);
    Vector2 mapPosition = Vector2Scale(position, (float)1/MAZE_TILE);

    uint32_t i = mapPosition.x;
    uint32_t j = mapPosition.y;

    uint32_t value = map->vector[j + (i * map->width) ];
    if (value == 0)
    {
        player->position = position;
    }
}

MAZE static void _rotation_player(Player_t *const player)
{
    float angle = player->angle;
    if (IsKeyDown(KEY_LEFT))
    {
        angle -= 5;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        angle += 5;
    }

    angle = Clamp(angle, 0, 360);       
    if (angle == 360)
    {
        angle = 0;
    } else if(angle == 0)
    {
        angle = 360;
    }
    player->angle = angle;    
    angle = DEG2RAD * angle;
    player->direction.x = cosf(angle);
    player->direction.y = sinf(angle);
    
    // Vector2 direction = (Vector2){
    //     .x=cosf(angle) * player->direction.x,
    //     .y=sinf(angle) * player->direction.y
    // };

    // Vector2 camera = (Vector2){
    //     .x=-sinf(angle) * player->camera.x,
    //     .y=cosf(angle) * player->camera.y
    // };
    // player->direction = direction;
    // player->camera = camera;
}
