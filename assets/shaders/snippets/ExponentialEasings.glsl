#ifndef EXPONENTIAL_EASINGS_INCLUDED
#define EXPONENTIAL_EASINGS_INCLUDED

#include "ExponentialBase.glsl"

//------------------------------------------------
float ExponentialEaseIn(float x)
{
    x = clamp(x, 0.0, 1.0);
    return x == 0.0 ? 0.0 : pow(2.0, 10.0*x - 10.0);
}

//------------------------------------------------
float ExponentialEaseOut(float x)
{
    x = clamp(x, 0.0, 1.0);
    return x == 1.0 ? 1.0 : 1.0 - pow(2.0, -10.0*x);
}

//------------------------------------------------
float ExponentialEaseInOut(float x)
{
    x = clamp(x, 0.0, 1.0);
    return x < 0.5 ?
        ExponentialEaseIn(x*2.0)/2.0 :
        ExponentialEaseOut(x*2.0 - 1.0)/2.0 + 0.5;
}

//------------------------------------------------
float ExponentialEaseOutIn(float x)
{
    x = clamp(x, 0.0, 1.0);
    return x < 0.5 ?
        ExponentialEaseOut(x*2.0)/2.0 :
        ExponentialEaseIn(x*2.0 - 1.0)/2.0 + 0.5;
}

#endif
