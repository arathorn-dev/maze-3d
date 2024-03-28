#include "../includes/screens.h"

//----------------------------------------------------------------------------------
//  Statics function declaration.
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//  Public function implementation.
//----------------------------------------------------------------------------------

MAZE Screen_t *create_menu(void)
{
    Screen_t *screen = MemAlloc(sizeof(Screen_t));
    if (screen == NULL)
    {
        TraceLog(LOG_INFO, "[MENU] Error to create Screen_t * pointer.");
        return NULL;
    }
    
    screen->type = SCREEN_MENU;
    TraceLog(LOG_DEBUG, "[MENU] Screen_t pointer created successfully.");
    return screen;
}

MAZE void update_menu(Screen_t *const screen)
{
    // TODO
}

MAZE void draw_menu(const Screen_t *const screen)
{
    ClearBackground(BLUE);
}

MAZE void destroy_menu(Screen_t **ptr)
{
    if (*ptr != NULL)
    {
        MemFree(*ptr);
        *ptr = NULL;
        TraceLog(LOG_DEBUG, "[MENU] Screen_t pointer destroyed successfully.");
    }
}

//----------------------------------------------------------------------------------
//  Statics function implementation.
//----------------------------------------------------------------------------------

