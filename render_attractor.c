#include "header.h"

void render_2d_attractor(SDL_Renderer *renderer, RenderData *RD, Point *p, int iterations)
{
    int i;
    SDL_Rect point;
    point.w = 1;    
    point.h = 1;    

    for (i = 0; i < iterations; i++)
    {
        point.x = RD->center_x + RD->scale*p[i].x; 
        point.y = RD->center_y + RD->scale*p[i].y;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &point); 
    }
}
