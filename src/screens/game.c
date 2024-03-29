#include "../includes/screens.h"
#include "../includes/map.h"

//----------------------------------------------------------------------------------
//  Statics variables & function declaration.
//----------------------------------------------------------------------------------
static Map_t *_map = NULL;

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
}

MAZE void draw_game(const Screen_t *const screen)
{
    ClearBackground(GREEN);
    draw_map(_map);
}

MAZE void destroy_game(Screen_t **ptr)
{
    if (*ptr != NULL)
    {
        destroy_map(&_map);
        _map = NULL;
        MemFree(*ptr);
        *ptr = NULL;
        TraceLog(LOG_DEBUG, "[GAME] Screen_t pointer destroyed successfully.");
    }
}

//----------------------------------------------------------------------------------
//  Statics function implementation.
//----------------------------------------------------------------------------------
