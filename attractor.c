#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "SDL2/SDL.h"

#include "header.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int SCREEN_WIDTH = 1280; //640 405;
const int SCREEN_HEIGHT = 720; //640;
const int screen_centerX = SCREEN_WIDTH / 2;
const int screen_centerY = SCREEN_HEIGHT / 2;

int main()
{
    //Initiating SDL2 stuff
    if (SDL_Init(SDL_INIT_VIDEO) < 0) printf("SDL2 video failed to initialize: \n", SDL_GetError());
    else printf("System is ready to go!\n");

    window = SDL_CreateWindow("Strange Attractor",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED);

     srand(time(NULL));

    /*Place where variables, structs, and some functions are initiated*/
    /*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/ 
    /*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/ 
    RenderData render_data =
    {
        .center_x = screen_centerX, 
        .center_y = screen_centerY,
        .scale = 150 
    };

    FILE *write_attractor = fopen("cool_attractors.bin", "ab");
    FILE *read_attractor = fopen("cool_attractors.bin", "rb");
    if (write_attractor == NULL || read_attractor == NULL)
    {
        printf("file not found\n");
        exit(1);
    }

    int c_len = 12;
    int number_of_points = 100000;
    double c[c_len];
    double c_copy[c_len]; 
    double c_buffer[c_len]; 
    Point points[number_of_points];

    double shift = 0;
    int animate = FALSE;
    int slide_show = FALSE;
    int b = 0;
   
    /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
    /*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
   
    //Main render loop
    SDL_bool running = SDL_TRUE;
    while (running == SDL_TRUE)
    {

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = SDL_FALSE;
                break;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    //exit program
                    case SDLK_ESCAPE:
                        running = SDL_FALSE;
                        break;
                    
                    //generate new attractor
                    case SDLK_RIGHT:
                        find_2d_attractor(c, c_len, 2);
                        create_2d_attractor(points, c, number_of_points);
                        memcpy(c_copy, c, sizeof(c));
                        animate = FALSE; 
                        break; 
                    
                    //start slide show of attractors 
                    case SDLK_UP:
                        slide_show = TRUE; 
                        break;
                    
                    //reset attractor 
                    case SDLK_r:
                        memcpy(c, c_copy, sizeof(c_copy));
                        create_2d_attractor(points, c, number_of_points);
                        slide_show = FALSE; 
                        animate = FALSE; 
                        break;
                    
                    //save attractor to text file
                    case SDLK_s:
                        fwrite(c, sizeof(double), c_len, write_attractor);
                        break;
                    
                    //animate attractor
                    case SDLK_a:
                        animate = TRUE; 
                        break; 

                    case SDLK_m:
                        fread(c_buffer, sizeof(double), c_len, read_attractor);

                        fseek(read_attractor, b, SEEK_SET);
                        b += sizeof(double)*c_len;

                        memcpy(c, c_buffer, sizeof(c_buffer));
                        create_2d_attractor(points, c, number_of_points);

                        animate = FALSE; 
                        break; 

                    case SDLK_n:

                        fseek(read_attractor, 0, SEEK_SET);
                        b = 0; // sizeof(double)*c_len;

                        fread(c_buffer, sizeof(double), c_len, read_attractor);

                        memcpy(c, c_buffer, sizeof(c_buffer));
                        create_2d_attractor(points, c, number_of_points);

                        animate = FALSE; 
                        break; 
                }
            }
        }
        
        if (slide_show == TRUE)
        {
            usleep(1200000);
            find_2d_attractor(c, c_len, 2);
            create_2d_attractor(points, c, number_of_points);
        }

        if (animate == TRUE)
        {
            create_2d_attractor(points, c, number_of_points);
            shift += 0.0005;
            c[0] += 0.0002*sin(shift);
            //printf("c_0: %lf\n", c[0]);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render_2d_attractor(renderer, &render_data, points, number_of_points);

        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }
   
    fclose(write_attractor);
    fclose(read_attractor);

    SDL_DestroyWindow(window);
    SDL_Quit();
}



























