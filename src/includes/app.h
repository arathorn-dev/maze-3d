#ifndef __MAZE_APP_H__
#define __MAZE_APP_H__
#include "config.h"
#include "screens.h"

#define APP_SCREEN_SIZE 2

typedef struct {
    Screen_t **screens;    
    size_t currentIndex; 
} App_t;

#if defined(__cplusplus)
    extern "C" {
#endif

    MAZE App_t* create_app(void);
    MAZE void run_app(App_t *const app);
    MAZE void destroy_app(App_t **ptr);

#if defined(__cplusplus)
    }
#endif

#endif
