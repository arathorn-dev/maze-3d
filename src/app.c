#include "./includes/app.h"

//----------------------------------------------------------------------------------
//  Statics variable & function declaration.
//----------------------------------------------------------------------------------
static int32_t _nextIndexScreen = -1; 
static float _alphaTransition = 0.0f;

#if defined(__cplusplus)
    extern "C" {
#endif

    static void _init_app(void);
    static void _init_screen_app(App_t *const app);
    static void _destroy_screen_app(void);
    static void _update_app(App_t *const app);
    static void _draw_app(const App_t *const app);
    static void _transition_app(App_t *const app);
    static void _reset_transition_app(void);
    static void _load_screen_app(App_t *const app, size_t index);
    static void _unload_screen_app(App_t *const app);
    static void _draw_transition_app(void);

#if defined(__cplusplus)
    }
#endif

//----------------------------------------------------------------------------------
//  Public function implementation.
//----------------------------------------------------------------------------------
MAZE App_t* create_app(void)
{
    App_t *app = MemAlloc(sizeof(App_t));
    if (app == NULL)
    {
        TraceLog(LOG_INFO, "Error to create App_t pointer.");
        return NULL;
    }
    _init_app();
    _init_screen_app(app);
    return app;
}

MAZE void run_app(App_t *const app)
{
    while(!WindowShouldClose())
    {
        _update_app(app);
        _draw_app(app);
    }
}

MAZE void destroy_app(App_t **ptr)
{
    if (ptr != NULL)
    {        
        _unload_screen_app(*ptr);
        MemFree((*ptr)->screens);
        (*ptr)->screens = NULL;
        MemFree(*ptr);
        *ptr = NULL;
        TraceLog(LOG_DEBUG, "[APP] App_t pointer destroyed successfully.");
        
        _destroy_screen_app();
    }
}

//----------------------------------------------------------------------------------
//   Statics functions implementation.
//----------------------------------------------------------------------------------
MAZE static void _init_app(void)
{
    InitWindow(
            MAZE_WIDTH_SCREEN,
            MAZE_HEIGHT_SCREEN,
            MAZE_TITLE_SCREEN
            );
    
#if defined(MAZE_DEBUG)
    SetTraceLogLevel(LOG_DEBUG);
#endif
    SetTargetFPS(MAZE_FPS);
}

MAZE static void _init_screen_app(App_t *const app)
{
    app->screens = MemAlloc(sizeof(Screen_t) * APP_SCREEN_SIZE);
    _load_screen_app(app, 1);
}

MAZE static void _destroy_screen_app(void)
{
    CloseWindow();
}

MAZE static void _update_app(App_t *const app)
{
    if (IsKeyPressed(KEY_ONE))
    {
        _nextIndexScreen = 0;
    }
    else if (IsKeyPressed(KEY_TWO))
    {
        _nextIndexScreen = 1;
    }
    
    if (_nextIndexScreen == -1)
    {
        switch(app->currentIndex)
        {
            case 0:
                update_menu(app->screens[0]);
                break;
            case 1:
                update_game(app->screens[1]);
                break;
        }
    } else {
        _transition_app(app);
    }
}

MAZE static void _draw_app(const App_t *const app)
{
    BeginDrawing();
    // ClearBackground(SKYBLUE);
    switch(app->currentIndex)
    {
        case 0:
            draw_menu(app->screens[0]);
            break;
        case 1:
            draw_game(app->screens[1]);
            break;
    }
    
    _draw_transition_app();
    EndDrawing();
}

MAZE static void _transition_app(App_t *const app)
{
    if (_alphaTransition >= 1.0f) {
        _unload_screen_app(app);
        _load_screen_app(app, _nextIndexScreen);
        _reset_transition_app();
    } else {
        _alphaTransition += 0.09f;
    }
}

MAZE static void _reset_transition_app(void)
{
    _alphaTransition = 0.0f;
    _nextIndexScreen = -1; 
}

MAZE static void _load_screen_app(App_t *const app, size_t index)
{
    switch(index)
    {
        case 0:
            app->screens[0] = create_menu();
            app->currentIndex = index;
            break;
        case 1:
            app->screens[1] = create_game("data/maps/map_0.data");
            app->currentIndex = index;
            break;
    }
}

MAZE static void _unload_screen_app(App_t *const app)
{
    size_t index = app->currentIndex;
    switch(index)
    {
        case 0:
            destroy_menu(&app->screens[index]);
            break;
        case 1:
            destroy_game(&app->screens[index]);
            break;
    }
}

MAZE static void _draw_transition_app(void)
{
    if (_nextIndexScreen > -1)
    {
        DrawRectangle(
            0,
            0,
            MAZE_WIDTH_SCREEN,
            MAZE_HEIGHT_SCREEN,
            Fade(BLACK, _alphaTransition)
            );
    }
}

