#include "../includes/screens.h"
#include "../includes/map.h"
#include "../includes/player.h"

//----------------------------------------------------------------------------------
//  Statics variables & function declaration.
//----------------------------------------------------------------------------------
static Map_t *_map = NULL;
static Player_t *_player = NULL;

#if defined(__cplusplus)
    extern "C" {
#endif
#if defined(__cplusplus)
    }
#endif
//----------------------------------------------------------------------------------
//  Public function implementation.
//----------------------------------------------------------------------------------

MAZE Screen_t *create_game(const char *filename)
{
    Screen_t *screen = MemAlloc(sizeof(Screen_t));
    if (screen == NULL)
    {
        TraceLog(LOG_INFO, "[GAME] Error to create Screen_t * pointer.");
        return NULL;
    }
    
    screen->type = SCREEN_GAME;
    _map = create_map(filename);

    _player = create_player((Vector2){.x= 2 * MAZE_TILE, .y= 2 * MAZE_TILE});
    if (_map == NULL)
    {
        MemFree(screen);
        screen = NULL;
        return NULL;
    }
    TraceLog(LOG_DEBUG, "[GAME] Screen_t pointer created successfully.");
    return screen;
}

MAZE void update_game(Screen_t *const screen)
{
    update_map(_map);
    update_player(_player, _map);
}

MAZE void draw_game(const Screen_t *const screen)
{
    ClearBackground(GREEN);
    draw_map(_map);
    draw_player(_player);
}

MAZE void destroy_game(Screen_t **ptr)
{
    if (*ptr != NULL)
    {
        destroy_map(&_map);
        destroy_player(&_player);
        _map = NULL;
        MemFree(*ptr);
        *ptr = NULL;
        TraceLog(LOG_DEBUG, "[GAME] Screen_t pointer destroyed successfully.");
    }
}

//----------------------------------------------------------------------------------
//  Statics function implementation.
//----------------------------------------------------------------------------------
