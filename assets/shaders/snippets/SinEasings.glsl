#ifndef SINE_EASINGS_INCLUDED
#define SINE_EASINGS_INCLUDED

#include "Constants.glsl"

//------------------------------------------------
float SinEaseIn(float x)
{
    x = clamp(x, 0.0, 1.0);
    return 1 - cos(x * HALF_PI);
}

//------------------------------------------------
float SinEaseOut(float x)
{
    x = clamp(x, 0.0, 1.0);
    return sin(x * HALF_PI);
}

//------------------------------------------------
float SinEaseInOut(float x)
{
    x = clamp(x, 0.0, 1.0);
    return (1 - cos(x * PI)) / 2;
}

//------------------------------------------------
float SinEaseOutIn(float x)
{
    x = clamp(x, 0.0, 1.0);
    return x < 0.5 ? SinEaseOut(x * 2.0) / 2.0 : SinEaseIn(x * 2.0 - 1) / 2.0 + 0.5;
}

#endif
