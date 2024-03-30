#ifndef __MAZE_MAP_H__
#define __MAZE_MAP_H__

#include "config.h"

MAZE typedef struct {
    uint32_t *vector;
    uint32_t width;
    uint32_t height;
} Map_t;

#if defined(__cplusplus)
  extern "C" {
#endif
  MAZE Map_t *create_map(const char *filename);
  MAZE void update_map(Map_t *const map);
  MAZE void draw_map(const Map_t *const map);
  MAZE void destroy_map(Map_t **ptr);
#if defined(__cplusplus)
  }
#endif
#endif
