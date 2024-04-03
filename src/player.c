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

    player->camera = (Vector2){.x=0, .y=-1};
    player->direction = (Vector2){.x=1, .y=0};

    player->angle = 0;

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
    Vector2 cam = player->camera;
   
    DrawLine(
        pos.x,
        pos.y,
        pos.x + (10.5 * dir.x),
        pos.y + (10.5 * dir.y),
        GREEN
    );
    
    DrawLine(
        pos.x + (10.5 * dir.x),
        pos.y + (10.5 * dir.y),
        (pos.x + (10.5 * dir.x)) + 10.5 * cam.x,
        (pos.y + (10.5 * dir.y)) + 10.5 * cam.y,
        BLUE
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
    Vector2 (*vector2Fn)(Vector2, Vector2) = NULL;
    if (IsKeyDown(KEY_W))
    {
        vector2Fn = Vector2Add;
    }
    else if(IsKeyDown(KEY_S))
    {
        vector2Fn = Vector2Subtract;
    }
    
    if (vector2Fn != NULL)
    {
        Vector2 position = vector2Fn(player->position, player->direction);
        Vector2 mapPosition = Vector2Scale(position, (float)1/MAZE_TILE);

        uint32_t i = mapPosition.x;
        uint32_t j = mapPosition.y;

        uint32_t value = map->vector[j + (i * map->width) ];
        if (value == 0)
        {
            player->position = position;
        }
    }
}

MAZE static void _rotation_player(Player_t *const player)
{
    float angle = player->angle;
    if (IsKeyDown(KEY_LEFT))
    {
        angle -= 0.1;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        angle += 0.1;
    }

    if (angle != player->angle)
    {
        angle = Clamp(angle, 0, MAZE_2PI);       
        if (angle == MAZE_2PI)
        {
            angle = 0;
        } else if(angle == 0)
        {
            angle = MAZE_2PI;
        }
        player->angle = angle;    

        //    x        y
        // [cos(x)  -sin(x)]
        // [sin(x)  cos(x)]
        player->camera.x = cosf(angle + PI/2);
        player->camera.y = -sinf(angle + PI/2);
    
        player->direction.x = cosf(angle);
        player->direction.y = sinf(angle);
    }
}
