#ifndef EASINGS_INCLUDED
#define EASINGS_INCLUDED

#include "Constants.glsl"

#include "CircularEasings.glsl"
#include "ExponentialEasings.glsl"
#include "PolynomialEasings.glsl"
#include "SinEasings.glsl"

//------------------------------------------------
float EaseInBack(float x)
{
    x = clamp(x, 0.0, 1.0);

    float c1 = BOUNCE;
    float c3 = c1 + 1.0;

    return c3*x*x*x - c1*x*x;
}


//------------------------------------------------
float EaseOutBack(float x)
{
    x = clamp(x, 0.0, 1.0);

    float c1 = BOUNCE;
    float c3 = c1 + 1.0;

    return 1.0 + c3*cb(x-1.0) + c1*sq(x-1.0);
}

//------------------------------------------------
float EaseInOutBack(float x)
{
    x = clamp(x, 0.0, 1.0);

    float c1 = BOUNCE;
    float c2 = c1 * 1.525;

    return x < 0.5 ?
        (sq(x*2.0) * ((c2 + 1.0)*(x*2.0) - c2)) / 2.0 :
        (sq(x*2.0 - 2.0) * ((c2 + 1.0)*(x*2.0 - 2.0) + c2) + 2.0) / 2.0;
}

//------------------------------------------------
float EaseOutInBack(float x)
{
    x = clamp(x, 0.0, 1.0);

    float c1 = BOUNCE;
    float c2 = c1 * 1.525;

    return x < 0.5 ?
        (sq(x*2.0 - 1.0) * ((c2 + 1.0)*(x*2.0 - 1.0) + c2) + 1.0) / 2.0 :
        (sq(x*2.0 - 1.0) * ((c2 + 1.0)*(x*2.0 - 1.0) - c2) + 1.0) / 2.0;
}

//------------------------------------------------
float ElasticEaseIn(float x)
{
    x = clamp(x, 0.0, 1.0);

    float c4 = TWO_PI / 3.0;

    return x == 0.0 ? 0.0 :
           x == 1.0 ? 1.0 :
        -pow(2.0, x*10.0 - 10.0) * sin((x*10.0 - 10.75) * c4);
}

//------------------------------------------------
float ElasticEaseOut(float x)
{
    x = clamp(x, 0.0, 1.0);

    float c4 = TWO_PI / 3.0;

    return x == 0.0 ? 0.0 :
           x == 1.0 ? 1.0 :
        pow(2.0, -10.0*x) * sin((x*10.0 - 0.75) * c4) + 1.0;
}

//------------------------------------------------
float ElasticEaseInOut(float x)
{
    x = clamp(x, 0.0, 1.0);

    float c5 = TWO_PI / 4.5;

    return x == 0.0 ? 0.0 :
           x == 1.0 ? 1.0 :
           x < 0.5 ?
    -(pow(2.0, 20.0*x - 10.0) * sin((20.0*x - 11.125) * c5)) / 2.0 :
    (pow(2.0, -20.0*x + 10.0) * sin((20.0*x - 11.125) * c5)) / 2.0 + 1.0;
}

//------------------------------------------------
float ElasticEaseOutIn(float x)
{
    x = clamp(x, 0.0, 1.0);

    float c5 = TWO_PI / 4.5;

    return x == 0.0 ? 0.0 :
           x == 1.0 ? 1.0 :
           x < 0.5 ?
    (pow(2.0, -20.0*x) * sin((-20.0*x - 1.125) * c5)) / 2.0 + 0.5 :
    -(pow(2.0, 20.0*x - 20.0) * sin((-20.0*x + 18.875) * c5)) / 2.0 + 0.5;
}

//------------------------------------------------
float EaseOutBounce(float x)
{
    x = clamp(x, 0.0, 1.0);

    float n1 = 7.5625;
    float d1 = 2.75;

    if(x < 1/d1)
    {
        return n1*x*x;
    }
    else if(x < 2/d1)
    {
        return n1*sq(x - 1.5/d1) + 0.75;
    }
    else if(x < 2.5/d1)
    {
        return n1*sq(x - 2.25/d1) + 0.9375;
    }
    else
    {
        return n1*sq(x - 2.625/d1) + 0.984375;
    }
}

//------------------------------------------------
float EaseInBounce(float x)
{
    return 1.0 - EaseOutBounce(1.0 - x);
}

//------------------------------------------------
float EaseInOutBounce(float x)
{
    x = clamp(x, 0.0, 1.0);

    return x < 0.5 ?
        (1.0 - EaseOutBounce(1.0 - x*2.0)) / 2.0 :
        (1.0 + EaseOutBounce(x*2.0 - 1.0)) / 2.0;
}

//------------------------------------------------
float EaseOutInBounce(float x)
{
    x = clamp(x, 0.0, 1.0);

    return x < 0.5 ?
        (EaseOutBounce(x*2.0)) / 2.0 :
        (2.0 - EaseOutBounce(2.0 - x*2.0)) / 2.0;
}

#endif
