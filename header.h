#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "SDL2/SDL.h"

enum BOOL { FALSE, TRUE };
enum ATTRACTOR_FOUND { CHAOTIC, DECAY, STABLE, UNBOUNDED };

typedef struct Point
{
    double x, y, z;
}Point;

typedef struct RenderData
{
    int screen_width, screen_height;
    int center_x, center_y;
    double scale;
}RenderData;

//create_attractor.c functions
int find_2d_attractor(double *c, int c_len, double c_range); //finds constants that create a chaotic attractor
void create_2d_attractor(Point *p, double *c, int iter); //creates the array of points to be rendered

//render_attractor.c functions
void render_2d_attractor(SDL_Renderer *renderer, RenderData *RD, Point *p, int iterations);

//matrix_math.c functions

//predefined_attractors.c functions

#endif
























