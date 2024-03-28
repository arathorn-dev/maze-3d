#ifndef __MAZE_SCREEN_H__
#define __MAZE_SCREEN_H__

#include "config.h"

MAZE typedef enum {
    SCREEN_MENU = 0,
    SCREEN_GAME
} Screen_e;

MAZE typedef struct {
    Screen_e type;
} Screen_t;


#if defined(__cplusplus)
    extern "C" {
#endif
    MAZE Screen_t *create_menu(void);
    MAZE void update_menu(Screen_t *const screen);
    MAZE void draw_menu(const Screen_t *const screen);
    MAZE void destroy_menu(Screen_t **ptr);

    MAZE Screen_t *create_game(void);
    MAZE void update_game(Screen_t *const screen);
    MAZE void draw_game(const Screen_t *const screen);
    MAZE void destroy_game(Screen_t **ptr);

#if defined(__cplusplus)
    }
#endif
#endif
