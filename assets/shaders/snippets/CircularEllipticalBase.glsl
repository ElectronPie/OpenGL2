#ifndef CIRCULAR_ELLIPTICAL_BASE_INCLUDED
#define CIRCULAR_ELLIPTICAL_BASE_INCLUDED

#include "Pows.glsl"

// Taken from Golan Levin's paper "Circular & Elliptical Shaping Functions"
// https://www.flong.com/archive/texts/code/shapers_circ/

//------------------------------------------------
float CircularEaseIn(float x)
{
    float y = 1 - sqrt(1 - x*x);
    return y;
}

//------------------------------------------------
float CircularEaseOut(float x)
{
    float y = sqrt(1 - sq(1-x));
    return y;
}

//------------------------------------------------
float DoubleCircleSeat(float x, float a)
{
    float min_param_a = 0.0f;
    float max_param_a = 1.0f;
    a = clamp(a, min_param_a, max_param_a);

    float y;
    if(x <= a)
    {
        y = sqrt(sq(a) - sq(x-a));
    }
    else
    {
        y = 1 - sqrt(sq(1-a) - sq(x-a));
    }
    return y;
}

//------------------------------------------------
float DoubleCircleSigmoid(float x, float a)
{
    float min_param_a = 0.0f;
    float max_param_a = 1.0f;
    a = clamp(a, min_param_a, max_param_a);

    float y;
    if(x <= a)
    {
        y = a - sqrt(a*a - x*x);
    }
    else
    {
        y = a + sqrt(sq(1-a) - sq(x-1));
    }
    return y;
}

//------------------------------------------------
float DoubleEllipticSeat(float x, vec2 p)
{
    float a = p.x;
    float b = p.y;
    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0;
    float max_param_b = 1.0;
    a = clamp(a, min_param_a, max_param_a);
    b = clamp(b, min_param_b, max_param_b);

    float y = 0;
    if (x <= a)
    {
        y = (b/a) * sqrt(sq(a) - sq(x-a));
    }
    else
    {
        y = 1 - ((1-b)/(1-a))*sqrt(sq(1-a) - sq(x-a));
    }
    return y;
}

//------------------------------------------------
float DoubleEllipticSigmoid(float x, vec2 p)
{
    float a = p.x;
    float b = p.y;
    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0;
    float max_param_b = 1.0;
    a = clamp(a, min_param_a, max_param_a);
    b = clamp(b, min_param_b, max_param_b);

    float y = 0;
    if (x <= a)
    {
        y = b * (1 - (sqrt(sq(a) - sq(x))/a));
    }
    else
    {
        y = b + ((1-b)/(1-a))*sqrt(sq(1-a) - sq(x-1));
    }
    return y;
}

#endif
