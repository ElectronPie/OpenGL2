#ifndef CIRCULAR_EASINGS_INCLUDED
#define CIRCULAR_EASINGS_INCLUDED

// CircularEaseIn and CircularEaseOut defined in CircularEllipticalBase.glsl
#include "CircularEllipticalBase.glsl"

//------------------------------------------------
float CircularEaseInOut(float x)
{
    return DoubleCircleSigmoid(x, 0.5);
}

//------------------------------------------------
float CircularEaseOutIn(float x)
{
    return DoubleCircleSeat(x, 0.5);
}

#endif
