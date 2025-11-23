#ifndef IDENTITIES_INCLUDED
#define IDENTITIES_INCLUDED

// Taken from Inigo Quilez's article "Useful little functions"
// https://iquilezles.org/articles/functions/

// m - threshold, n - substitute value
float AlmostIdentity(float x, float m, float n)
{
    if(x > m)
        return x;

    float a = 2.0 * n - m;
    float b = 2.0 * m - 3.0 * n;
    float t = x / m;
    return (a * t + b) * t * t + n;
}

float AlmostAbs(float x, float n)
{
    return sqrt(x * x + n * n);
}

float SmoothstepIntegral(float x, float T)
{
    if(x > T)
        return x - T / 2.0;

    return x * x * x * (1.0 - x * 0.5 / T) / T / T;
}

#endif
