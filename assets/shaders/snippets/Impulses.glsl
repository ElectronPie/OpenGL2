#ifndef IMPULSES_INCLUDED
#define IMPULSES_INCLUDED

#include "Constants.glsl"

// Taken from Inigo Quilez's article "Useful little functions"
// https://iquilezles.org/articles/functions/

// k controls the stretching of the function
float ExponentialImpulse(float x, float k)
{
    float h = k * x;
    return h * exp(1.0 - h);
}

float QuadraticImpulse(float x, float k)
{
    return 2.0 * sqrt(k) * x / (1.0 + k * x * x);
}

// n is the degree of the polynomial
float PolynomialImpulse(float x, float k, int n)
{
    return ((1.0 * n) / (n - 1.0)) * pow((n - 1.0) * k, 1.0 / n) * x / (1.0 + k * pow(x, n));
}

// k controls the width of attack, f controls the release
float ExponentialSustainedImpulse(float x, float k, float f)
{
    float s = max(x - f, 0.0);
    return min((x * x) / (f * f), 1.0 + (2.0 / f) * s * exp(-k * s));
}

float Sinc(float x, float k)
{
    float a = PI * (k * x - 1.0);
    return sin(a) / a;
}

// Reaches zero at m
float TruncatedFalloff(float x, float m)
{
    x /= m;
    return (x - 2.0) * x + 1.0;
}

#endif
