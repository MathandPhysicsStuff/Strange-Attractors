#include "header.h"

/*finds constants that create a chaotic attractor*/
//c is an array of constants
//c_len is the number of constants 
//c_range is the range of the constants centered around 0, so c_range = 2 is picking values from -2 to 2 
int find_2d_attractor(double *c, int c_len, double c_range)
{
    int i, j, k;
    double x, y, x2, y2, xp, yp;
    double xn, yn, x2n, y2n; //next x and y
    double xl, yl, xln, yln, dx, dy, d0, d; //for lyapunov exponent test
    double lyapunov;

    double max = 1000;
    double min = 0.000001;
    
    int found = FALSE;
    int attractor;
    int counter = 0;
    
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

        x2 = 0.002*((double)rand() / (double)RAND_MAX) - 0.001; 
        y2 = 0.002*((double)rand() / (double)RAND_MAX) - 0.001; 

        //initializing a point very close to (x,y) for the lyapunov exponent test
        xl = x + 0.0001*((double)rand() / (double)RAND_MAX);
        yl = y + 0.0001*((double)rand() / (double)RAND_MAX);

        dx = xl - x;
        dy = yl - y;
        d0 = sqrt(dx*dx + dy*dy);

        attractor = CHAOTIC; 
        lyapunov = 0;
        counter += 1;

        /* 
        Iterating over the equation using
        the random constants to see if the attractor is chaotic. */
        for (k = 0; k < 10000; k++)
        {

            xn = c[0] + c[1]*x + c[2]*x*x + c[3]*x*y + c[4]*y*y + c[5]*y;
            yn = c[6] + c[7]*x + c[8]*x*x + c[9]*x*y + c[10]*y*y + c[11]*y;
 
            x2n = c[0] + c[1]*x2 + c[2]*x2*x2 + c[3]*x2*y2 + c[4]*y2*y2 + c[5]*y2;
            y2n = c[6] + c[7]*x2 + c[8]*x2*x2 + c[9]*x2*y2 + c[10]*y2*y2 + c[11]*y2;
            
            
            //checking if attractor is stable
            if ((fabs(x2 - x) < min && fabs(y2 - y) < min))
            {
                attractor = STABLE;
                break;
            }
          
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
                
                xl = xln;
                yl = yln;

                dx = x - xl;
                dy = y - yl;
                d = sqrt(dx*dx + dy*dy);

                lyapunov += log(fabs(d/d0));

                xl = xn + d0*dx/d;
                yl = yn + d0*dy/d;
            }
 
            x = xn;
            y = yn;

            x2 = x2n;
            y2 = y2n;
        }

        //if chaotic attractor was found
        if ((attractor == CHAOTIC) && (lyapunov > 10))
        { 
            //printf("\ncounter: %d\n", counter);
            //printf("lyapunov exponent: %lf\n", lyapunov);
            found = TRUE;  
            return found;
        }

    }
    return found;
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

        x = xn;
        y = yn;
        
        p[i].x = xn;
        p[i].y = yn;
        //printf("%lf %lf\n", xn, yn);
    }
}


/*creates the array of points to be rendered and animates it*/
//p is an array of points
//iterations is the array length 
void update_2d_attractor(Point *p, double *c, int iterations, double *inc, int *count)
{
    int i;
    double x, y, xn, yn;

    x = 0.002*((double)rand() / (double)RAND_MAX) - 0.001; 
    y = 0.002*((double)rand() / (double)RAND_MAX) - 0.001; 
    
    c[0] += *inc;

    for (i = 0; i < iterations; i++)
    {
        xn = c[0] + c[1]*x + c[2]*x*x + c[3]*x*y + c[4]*y*y + c[5]*y;
        yn = c[6] + c[7]*x + c[8]*x*x + c[9]*x*y + c[10]*y*y + c[11]*y;
        
        if (fabs(x) > 10000000000 || fabs(y) > 10000000000)
            *count += 1;
            if (*count == 10000)
            {
                *inc *= -1;
                *count = 0;
            }

        if (fabs(xn - x) < 0.000001 && fabs(yn - y) < 0.000001)
            *inc *= -1;

        x = xn;
        y = yn;
        
        p[i].x = xn;
        p[i].y = yn;
        //printf("%lf %lf\n", xn, yn);
    }
}






















