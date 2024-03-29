#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "includes/config.h"
#include "includes/map.h"
#include "includes/raylib.h"

#define MAZE_LINE_TOKEN_MAP "-"

//----------------------------------------------------------------------------------
//  Statics function declaration.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
  extern "C" {
#endif

  MAZE static Map_t *_load_map_by_file(const char *filename);
  MAZE static uint32_t **_get_matrix_by_text(char *data, int32_t width, int32_t height);

#if defined(__cplusplus)
  }
#endif
//----------------------------------------------------------------------------------
//  Public function implementation.
//----------------------------------------------------------------------------------
MAZE Map_t *create_map(const char *filename)
{
    Map_t *map = _load_map_by_file(filename);
    if (map == NULL)
    {
        TraceLog(LOG_DEBUG, "Error to create Map_t pointer.");
        return NULL;
    }
    TraceLog(LOG_DEBUG, "Map_t pointer created successfully.");
    return map;
}

MAZE void update_map(Map_t *const map)
{
  // TODO
}

MAZE void draw_map(const Map_t *const map)
{
    uint32_t x = 0;
    uint32_t y = 0;
    Color color = BLACK;
    for (uint32_t i=0; i < map->height; ++i)
    {
        for (uint32_t j=0; j < map->width; ++j)
        {
            
            uint32_t value = map->matrix[i][j];
            switch(value)
            {
                case 0:
                    color = BLACK;
                    break;
                case 1:
                    color = SKYBLUE;
                    break;
                default:
                    color = RED;
            }

            DrawRectangle(x, y, MAZE_TILE, MAZE_TILE, color);
            DrawRectangleLines(x, y, MAZE_TILE, MAZE_TILE, WHITE);
            x += MAZE_TILE;
        }
        x = 0;
        y += MAZE_TILE;
    }
}

MAZE void destroy_map(Map_t **ptr)
{
    if (*ptr != NULL)
    {
        for(size_t i=0; i < (*ptr)->height; ++i)
        {
            MemFree((*ptr)->matrix[i]);
            (*ptr)->matrix[i] = NULL;
        }

        MemFree((*ptr));
        (*ptr) = NULL;
        TraceLog(LOG_DEBUG, "Map_t pointer destroyed successufully.");
    }
}

//----------------------------------------------------------------------------------
//  Statics function implementation.
//----------------------------------------------------------------------------------
MAZE static Map_t *_load_map_by_file(const char *filename)
{
    Map_t *map = NULL;
    uint32_t **matrix = NULL;
    int32_t width = 0;
    int32_t height = 0;
    char *data = NULL;

    if (FileExists(filename))
    {
        data = LoadFileText(filename);
        char *token = strtok(data, MAZE_LINE_TOKEN_MAP);
        uint32_t line = 0;
        while(token != NULL)
        {
            if (line == 0)
            {
                width = TextToInteger(token);
            } 
            else if (line == 1)
            {
                height = TextToInteger(token);
            } 
            else
            {
                matrix = _get_matrix_by_text(token, width, height);
            }
            token = strtok(NULL, MAZE_LINE_TOKEN_MAP);
            line++;
        }
        UnloadFileText(data);
    }

    if (matrix != NULL)
    {
        map = MemAlloc(sizeof(Map_t));
        if (map != NULL)
        {
            map->matrix = matrix;
            map->width = width;
            map->height = height;
        }
    }
    
    return map;
}

static uint32_t **_get_matrix_by_text(char *data, int32_t width, int32_t height)
{
    uint32_t **matrix = MemAlloc(sizeof(uint32_t*) * height);
    if (matrix == NULL)
    {
        return NULL;
    }

    for (size_t i=0; i < height; ++i)
    {
        matrix[i] = MemAlloc(sizeof(uint32_t) * width);
    }

    // TraceLog(LOG_DEBUG, TextForma("%s", data));
    char *token = strtok(data, "\n");
    int32_t i = 0;
    while (token != NULL)
    {
        for (size_t j=0; j < width; ++j)
        {
            const char *value = TextSubtext(token, j, 1);
            matrix[i][j] = TextToInteger(value);
        }
        token = strtok(NULL, "\n");
        i++;  
      }
  
    return matrix;
}
