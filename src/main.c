// #include "./includes/app.h"

// int main(void)
// {
//     App_t *app = create_app();
//     if (app == NULL)
//     {
//         return 1;   
//     }

//     run_app(app);
//     destroy_app(&app);
//     return 0;
// }

#include <math.h>
#include "./includes/raylib.h"

typedef struct {
    Vector2 position;
    float radius;
    Color color;
    float angle;
} Planet_t;

typedef struct {
    Vector2 position;
    float angle;
    Color color;
} Line_t;

static void _rotate(Line_t *const line);

int main(void)
{
    InitWindow(640, 480, "Test");

    Planet_t sun = {0};
    sun.position = (Vector2){.x=320, .y=240};
    sun.radius = 100;
    sun.angle = 0;
    sun.color = RAYWHITE;

    Line_t green = {0};
    green.position = (Vector2){.x=0, .y=-1};
    green.angle = PI/2;
    green.color = GREEN;
    
    Line_t red = {0};
    red.position = (Vector2){.x=1, .y=0};
    red.angle = 0;
    red.color = RED;

    
    SetTargetFPS(30);
    while(!WindowShouldClose())
    {
        _rotate(&green);
        _rotate(&red);
        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircleLines(sun.position.x, sun.position.y, sun.radius, sun.color);
        DrawLine(
            sun.position.x,
            sun.position.y,
            sun.position.x + 100 * green.position.x, 
            sun.position.y + 100 * green.position.y,
            green.color
        );
        
        DrawLine(
            sun.position.x,
            sun.position.y,
            sun.position.x + 100 * red.position.x, 
            sun.position.y + 100 * red.position.y,
            red.color
        );
        
        DrawLine(
            sun.position.x + 100 * green.position.x, 
            sun.position.y + 100 * green.position.y,
            sun.position.x + 100 * red.position.x, 
            sun.position.y + 100 * red.position.y,
            BLUE
        );
        
        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}

static void _rotate(Line_t *const line)
{
    float angle = line->angle;
    angle += 0.01;
    if (angle > 2*PI)
    {
        angle = 0;
    }
    else if (angle < 0)
    {
        angle = 2*PI;
    }

    line->position.x = cosf(angle);
    line->position.y = sinf(angle);
    line->angle = angle;
}
