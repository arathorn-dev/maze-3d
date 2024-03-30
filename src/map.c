#include <string.h>
#include "includes/config.h"
#include "includes/map.h"
#include "includes/raylib.h"

//----------------------------------------------------------------------------------
//  Statics function declaration.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
  extern "C" {
#endif

    MAZE static Map_t *_load_map_by_file(const char *filename);

    MAZE static void _get_dimension_by_text(char *data, uint32_t *const width, uint32_t *const height);
    MAZE static void _get_width_by_text(char *data, uint32_t *const width);
    MAZE static uint32_t *_create_vector_by_text(char *data, uint32_t width, uint32_t height);

#if defined(__cplusplus)
  }
#endif

static char *(*strtok_maze)(char *str, const char *delim, char **saveptr) = NULL;

//----------------------------------------------------------------------------------
//  Public function implementation.
//----------------------------------------------------------------------------------
MAZE Map_t *create_map(const char *filename)
{

#if defined(_WIN32)
    strtok_maze = strtok_s;
#elif defined(__APPLE__)
    strtok_maze = strtok_r;
#elif defined(__linux__)
    strtok_maze = strtok_r;
#endif
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
            
            uint32_t value = map->vector[j + (i * map->width)];
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
        MemFree((*ptr)->vector);
        (*ptr)->vector = NULL;
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
    uint32_t *vector = NULL;
    uint32_t width = 0;
    uint32_t height = 0;
    char *data = NULL;

    char buffer[500];
    if (FileExists(filename))
    {
        data = LoadFileText(filename);
        TextCopy(buffer, data);
        _get_dimension_by_text(buffer, &width, &height);
        vector = _create_vector_by_text(data, width, height);       
        UnloadFileText(data);
    }

    if (vector != NULL)
    {
        map = MemAlloc(sizeof(Map_t));
        if (map != NULL)
        {
            map->vector = vector;
            map->width = width;
            map->height = height;
        }
    }
    
    return map;
}

MAZE static void _get_dimension_by_text(char *data, uint32_t *const width, uint32_t *const height)
{
    char *ctx = NULL;
    char *token = strtok_maze(data, MAZE_LINE_TOKEN_MAP, &ctx);
    while (token != NULL)
    {
        if (*width == 0) _get_width_by_text(token, width);
        token = strtok_maze(NULL, MAZE_LINE_TOKEN_MAP, &ctx);
        (*height)++;
    }    
}

MAZE static void _get_width_by_text(char *data, uint32_t *const width)
{
    char *ctx = NULL;
    char *token = strtok_maze(data, MAZE_ELEM_TOKEN_MAP, &ctx);
    while (token != NULL)
    {
        token = strtok_maze(NULL, MAZE_ELEM_TOKEN_MAP, &ctx);
        (*width)++;
    }
}

MAZE static uint32_t *_create_vector_by_text(char *data, uint32_t width, uint32_t height)
{
    char buffer[500];
    char *ctx0 = NULL;
    char *ctx1 = NULL;    
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t *vector = MemAlloc(sizeof(uint32_t) * width * height);

    TextCopy(buffer, data);
    char *line = strtok_maze(buffer, MAZE_LINE_TOKEN_MAP, &ctx0);
    while (line != NULL)
    {
        char *token = strtok_maze(line, MAZE_ELEM_TOKEN_MAP, &ctx1);
        while (token != NULL)
        {
            vector[j + (i * width)] = TextToInteger(token);
            token = strtok_maze(NULL, MAZE_ELEM_TOKEN_MAP, &ctx1);
            j++;
        }
        
        line = strtok_maze(NULL, MAZE_LINE_TOKEN_MAP, &ctx0);
        j = 0;
        i++;
    }
    return vector;
}
