#ifndef CIRCULAR_ARC_INCLUDED
#define CIRCULAR_ARC_INCLUDED

#include "Pows.glsl"

//------------------------------------------------
// Adapted from Paul Bourke

// Check the given point are perpendicular to x or y axis
bool IsPerpendicular(vec2 p1, vec2 p2, vec2 p3)
{
    vec2 dA = p2 - p1;
    vec2 dB = p3 - p2;
    float epsilon = 0.000001;

    // checking whether the line of the two pts are vertical
    if(abs(dA.x) <= epsilon && abs(dB.y) <= epsilon)
    {
        return false;
    }
    if(abs(dA.y) <= epsilon)
    {
        return true;
    }
    else if(abs(dB.y) <= epsilon)
    {
        return true;
    }
    else if(abs(dA.x) <= epsilon)
    {
        return true;
    }
    else if(abs(dB.x) <= epsilon)
    {
        return true;
    }
    else return false;
}

void CalcCircleFrom3Points(
    in vec2 p1, in vec2 p2, in vec2 p3,
    out vec2 center, out float dRadius
)
{
    vec2 dA = p2 - p1;
    vec2 dB = p3 - p2;
    float epsilon = 0.000001;

    if(abs(dA.x) <= epsilon && abs(dB.x) <= epsilon)
    {
        center = 0.5*vec2(p2.x + p3.x, p1.y + p2.y);
        dRadius = length(center - p1);
        return;
    }

    // IsPerpendicular() assures d*.x is not zero
    float aSlope = dA.y / dA.x;
    float bSlope = dB.y / dB.x;
    // Checking whether the given points are colinear
    if(abs(aSlope - bSlope) <= epsilon)
    {
        center = vec2(0.0, 0.0);
        dRadius = 0.0;
        return;
    }

    // Calc center
    center.x = (
        aSlope*bSlope*(p1.y - p3.y) +
        bSlope*(p1.x + p2.x) -
        aSlope*(p2.x + p3.x)
    )/(2.0*(bSlope - aSlope));
    center.y = (-1.0/aSlope)*(center.x - (p1.x+p2.x)/2.0) + (p1.y+p2.y)/2.0;
    dRadius = length(center - p1);
}

float CircularArcThroughPoint(float x, vec2 p)
{
    float a = p.x;
    float b = p.y;
    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0 + epsilon;
    float max_param_b = 1.0 - epsilon;
    a = clamp(a, min_param_a, max_param_a);
    b = clamp(b, min_param_b, max_param_b);
    x = clamp(x, 0.0+epsilon, 1.0-epsilon);

    vec2 p1 = vec2(0.0);
    vec2 p2 = vec2(a, b);
    vec2 p3 = vec2(1);

    vec2 center = vec2(0.0, 0.0);
    float dRadius = 0.0;

    if(!IsPerpendicular(p1, p2, p3))
        CalcCircleFrom3Points(p1, p2, p3, center, dRadius);
    else if(!IsPerpendicular(p1, p3, p2))
        CalcCircleFrom3Points(p1, p3, p2, center, dRadius);
    else if(!IsPerpendicular(p2, p1, p3))
        CalcCircleFrom3Points(p2, p1, p3, center, dRadius);
    else if(!IsPerpendicular(p2, p3, p1))
        CalcCircleFrom3Points(p2, p3, p1, center, dRadius);
    else if(!IsPerpendicular(p3, p1, p2))
        CalcCircleFrom3Points(p3, p1, p2, center, dRadius);
    else if(!IsPerpendicular(p3, p2, p1))
        CalcCircleFrom3Points(p3, p2, p1, center, dRadius);
    else
    {
        return 0.0;
    }

    if(dRadius == 0.0)
        return x;

    // constrain
    if(
        clamp(center.x, 0.0+epsilon, 1.0-epsilon) == center.x &&
        clamp(center.y, 0.0+epsilon, 1.0-epsilon) == center.y
    )
    {
        if(a < center.x)
        {
            center = vec2(1.0, 0.0);
            dRadius = 1.0;
        }
        else
        {
            center = vec2(0.0, 1.0);
            dRadius = 1.0;
        }
    }

    float y = 0.0;
    if(x >= center.x)
    {
        y = center.y - sqrt(sq(dRadius) - sq(x - center.x));
    }
    else
    {
        y = center.y + sqrt(sq(dRadius) - sq(x - center.x));
    }
    return y;
}

#endif
