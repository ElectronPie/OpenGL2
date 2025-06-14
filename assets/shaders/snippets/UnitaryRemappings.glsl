#ifndef UNITARY_REMAPPINGS_INCLUDED
#define UNITARY_REMAPPINGS_INCLUDED

#include "BlinnWyvilCosApprox.glsl"

// Taken from Inigo Quilez's article "Useful little functions"
// https://iquilezles.org/articles/functions/

float AlmostUnitIdentity(float x)
{
    return x*x*(2.0-x);
}

float Gain(float x, float k)
{
    float a = 0.5*pow(2.0*((x < 0.5) ? x : 1.0-x), k);
    return (x < 0.5) ? a : 1.0-a;
}

float Parabola(float x, float k)
{
    return pow(4.0*x*(1.0-x), k);
}

float PowerCurve(float x, float a, float b)
{
    float k = pow(a+b, a+b)/(pow(a, a)*pow(b, b));
    return k*pow(x, a)*pow(1.0-x, b);
}

float Tone(float x, float k)
{
    return (k+1.0)/(1.0+k*x);
}

#endif
