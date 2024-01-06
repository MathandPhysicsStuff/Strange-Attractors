#include "header.h"

/*finds constants that create a chaotic attractor*/
//c is an array of constants
//c_len is the number of constants 
//c_range is the range of the constants centered around 0, so c_range = 2 is picking values from -2 to 2 
int find_2d_attractor(double *c, int c_len, double c_range)
{
    int i, j, k;
    double x, y;
    double xn, yn; //next x and y
    double xl, yl, xln, yln, dx, dy, d0, d; //for lyapunov exponent test
    double lyapunov;

    double max = 1000;
    double min = 0.000001;

    int found = FALSE;
    int attractor;
    
    //number of tries before giving up
    for (i = 0; i < 10000; i++)
    {
        //creating the random constants
        for (j = 0; j < c_len; j++)
        {
            c[j] = c_range*((double)rand() / (double)RAND_MAX) - (c_range/2);
        }

        
        //initializing a point (x,y)
        x = 0.002*((double)rand() / (double)RAND_MAX) - 0.001; 
        y = 0.002*((double)rand() / (double)RAND_MAX) - 0.001; 
        
        //initializing a point very close to (x,y) for the lyapunov exponent test
        xl = x + 0.0001*((double)rand() / (double)RAND_MAX);
        yl = y + 0.0001*((double)rand() / (double)RAND_MAX);

        dx = xl - x;
        dy = yl - y;
        d0 = sqrt(dx*dx + dy*dy);

        attractor = CHAOTIC; 
        lyapunov = 0;

        /* 
        Iterating over the equation using
        the random constants to see if the attractor is chaotic. */
        for (k = 0; k < 10000; k++)
        {
            xn = c[0] + c[1]*x + c[2]*x*x + c[3]*x*y + c[4]*y*y + c[5]*y;
            yn = c[6] + c[7]*x + c[8]*x*x + c[9]*x*y + c[10]*y*y + c[11]*y;
        
            //checking if point is unbounded
            if ((fabs(x) > max) || (fabs(y) > max))
            {
                attractor = UNBOUNDED;
                break;
            }
            
            //checking if point decays
            if ((fabs(xn - x) < min) && (fabs(yn - y) < min))
            {
                attractor = DECAY;
                break;
            }

            //checking if point is chaotic
            if (k > 1000)
            {
                xln = c[0] + c[1]*xl + c[2]*xl*xl + c[3]*xl*yl + c[4]*yl*yl + c[5]*yl;
                yln = c[6] + c[7]*xl + c[8]*xl*xl + c[9]*xl*yl + c[10]*yl*yl + c[11]*yl;

                dx = xln - xl;
                dy = yln - yl;
                d = sqrt(dx*dx + dy*dy);

                lyapunov += log(fabs(d/d0));

                xln = x + d0*dx/d;
                yln = y + d0*dy/d;
            }
        }

        //if chaotic attractor was found
        if (attractor == CHAOTIC && lyapunov > 10)
        {
            return found;
        }
    }
}

/*creates the array of points to be rendered*/
//p is an array of points
//iterations is the array length 
void create_2d_attractor(Point *p, double *c, int iterations)
{
    int i;
    double x, y, xn, yn;

    x = 0.002*((double)rand() / (double)RAND_MAX) - 0.001; 
    y = 0.002*((double)rand() / (double)RAND_MAX) - 0.001; 

    for (i = 0; i < iterations; i++)
    {
        xn = c[0] + c[1]*x + c[2]*x*x + c[3]*x*y + c[4]*y*y + c[5]*y;
        yn = c[6] + c[7]*x + c[8]*x*x + c[9]*x*y + c[10]*y*y + c[11]*y;
        
        p[i].x = xn;
        p[i].y = yn;
    }
}






















