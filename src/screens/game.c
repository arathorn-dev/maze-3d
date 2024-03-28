#include "../includes/screens.h"

//----------------------------------------------------------------------------------
//  Statics function declaration.
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//  Public function implementation.
//----------------------------------------------------------------------------------

MAZE Screen_t *create_game(void)
{
    Screen_t *screen = MemAlloc(sizeof(Screen_t));
    if (screen == NULL)
    {
        TraceLog(LOG_INFO, "[GAME] Error to create Screen_t * pointer.");
        return NULL;
    }
    
    screen->type = SCREEN_GAME;
    TraceLog(LOG_DEBUG, "[GAME] Screen_t pointer created successfully.");
    return screen;
}

MAZE void update_game(Screen_t *const screen)
{
    // TODO
}

MAZE void draw_game(const Screen_t *const screen)
{
    ClearBackground(GREEN);
}

MAZE void destroy_game(Screen_t **ptr)
{
    if (*ptr != NULL)
    {
        MemFree(*ptr);
        *ptr = NULL;
        TraceLog(LOG_DEBUG, "[GAME] Screen_t pointer destroyed successfully.");
    }
}

//----------------------------------------------------------------------------------
//  Statics function implementation.
//----------------------------------------------------------------------------------

