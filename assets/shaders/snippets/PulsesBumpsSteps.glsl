#ifndef PULSES_BUMPS_STEPS_INCLUDED
#define PULSES_BUMPS_STEPS_INCLUDED

// Taken from Inigo Quilez's article "Useful little functions"
// https://iquilezles.org/articles/functions/

float CubicPulse(float x, float c, float w)
{
    x = abs(x - c);
    if(x > w)
        return 0.0;
    x /= w;
    return 1.0 - x * x * (3.0 - 2.0 * x);
}

float RationalBump(float x, float k)
{
    return 1.0 / (1.0 + k * x * x);
}

float ExponentialStep(float x, float n)
{
    return exp2(-exp2(n) * pow(x, n));
}

#endif
