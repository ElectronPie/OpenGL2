#ifndef BEZIER_INCLUDED
#define BEZIER_INCLUDED

// Taken from Golan Levin's paper "Bezier and Othr Parametric Shaping Functions"
// https://www.flong.com/archive/texts/code/shapers_bez/

//------------------------------------------------
// Adapted from BEZMATH.PS (1993)
// by Don Lancaster, SYNERGETICS Inc.
// http://www.tinaja.com/text/bezmath.html
float QuadraticBezier(float x, vec2 p)
{
    float epsilon = 0.00001;
    float a       = clamp(p.x, 0.0, 1.0);
    float b       = clamp(p.y, 0.0, 1.0);
    if(a == 0.5)
    {
        a += epsilon;
    }

    // Solve t from x (an inverse operation)
    float om2a = 1.0 - 2.0 * a;
    float t    = (sqrt(a * a + om2a * x) - a) / om2a;
    float y    = (1.0 - 2.0 * b) * (t * t) + (2.0 * b) * t;
    return y;
}

//------------------------------------------------
// Adapted from BEZMATH.PS (1993)
// by Don Lancaster, SYNERGETICS Inc.
// http://www.tinaja.com/text/bezmath.html

// Helper functions:
float SlopeFromt(float t, float A, float B, float C)
{
    float dtdx = 1.0 / (3.0 * A * t * t + 2.0 * B * t + C);
    return dtdx;
}

float xFromt(float t, float A, float B, float C, float D)
{
    float x = A * (t * t * t) + B * (t * t) + C * t + D;
    return x;
}

float yFromt(float t, float E, float F, float G, float H)
{
    float y = E * (t * t * t) + F * (t * t) + G * t + H;
    return y;
}

float CubicBezier(float x, vec2 p1, vec2 p2)
{
    float y0a = 0.0;  // initial y
    float x0a = 0.0;  // initial x
    float y1a = p1.y; // 1st influence y
    float x1a = p1.x; // 1st influence x
    float y2a = p2.y; // 2nd influence y
    float x2a = p2.x; // 2nd influence x
    float y3a = 1.0;  // final y
    float x3a = 1.0;  // final x

    float A = x3a - 3.0 * x2a + 3.0 * x1a - x0a;
    float B = 3.0 * x2a - 6.0 * x1a + 3.0 * x0a;
    float C = 3.0 * x1a - 3.0 * x0a;
    float D = x0a;

    float E = y3a - 3.0 * y2a + 3.0 * y1a - y0a;
    float F = 3.0 * y2a - 6.0 * y1a + 3.0 * y0a;
    float G = 3.0 * y1a - 3.0 * y0a;
    float H = y0a;

    // Solve for t given x (using Newton-Raphelson), then solve for y given t.
    // Assume for the first guess that t = x.
    float currentt            = x;
    int nRefinementIterations = 5;
    for(int i = 0; i < nRefinementIterations; ++i)
    {
        float currentx     = xFromt(currentt, A, B, C, D);
        float currentSlope = SlopeFromt(currentt, A, B, C);
        currentt -= (currentx - x) * currentSlope;
        currentt = clamp(currentt, 0.0, 1.0);
    }

    float y = yFromt(currentt, E, F, G, H);
    return y;
}

//------------------------------------------------

// Helper functions.
float B0(float t)
{
    return (1 - t) * (1 - t) * (1 - t);
}

float B1(float t)
{
    return 3 * t * (1 - t) * (1 - t);
}

float B2(float t)
{
    return 3 * t * t * (1 - t);
}

float B3(float t)
{
    return t * t * t;
}

float Findx(float t, float x0, float x1, float x2, float x3)
{
    return x0 * B0(t) + x1 * B1(t) + x2 * B2(t) + x3 * B3(t);
}

float Findy(float t, float y0, float y1, float y2, float y3)
{
    return y0 * B0(t) + y1 * B1(t) + y2 * B2(t) + y3 * B3(t);
}

float CubicBezierNearlyThroughTwoPoints(float x, vec2 p1, vec2 p2)
{
    float y           = 0.0;
    float epsilon     = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0 + epsilon;
    float max_param_b = 1.0 - epsilon;
    float a           = clamp(p1.x, min_param_a, max_param_a);
    float b           = clamp(p1.y, min_param_b, max_param_b);
    float c           = p2.x;
    float d           = p2.y;

    vec2 p0 = vec2(0.0);
    vec2 p4 = vec2(a, b);
    vec2 p5 = vec2(c, d);
    vec2 p3 = vec2(1.0);
    vec2 p1_, p2_; // to be solved

    // Arbitrary but reasonable t-values for interior control points
    float t1 = 0.3;
    float t2 = 0.7;

    float B0t1 = B0(t1);
    float B1t1 = B1(t1);
    float B2t1 = B2(t1);
    float B3t1 = B3(t1);
    float B0t2 = B0(t2);
    float B1t2 = B1(t2);
    float B2t2 = B2(t2);
    float B3t2 = B3(t2);

    vec2 cc = p4 - p0 * B0t1 - p3 * B3t1;
    vec2 ff = p5 - p0 * B0t2 - p3 * B3t2;

    p2_ = (cc - (ff * B1t1) / B1t2) / (B2t1 - (B1t1 * B2t2) / B1t2);
    p1_ = (cc - p2_ * B2t1) / B1t1;

    p1_.x = clamp(p1_.x, 0.0 + epsilon, 1.0 - epsilon);
    p2_.x = clamp(p2_.x, 0.0 + epsilon, 1.0 - epsilon);

    // Note that this function also requires CubicBezier()!
    y = CubicBezier(x, p1_, p2_);
    y = clamp(y, 0.0, 1.0);
    return y;
}

#endif
