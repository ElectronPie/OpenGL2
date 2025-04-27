#ifndef POLYNOMIAL_INCLUDED
#define POLYNOMIAL_INCLUDED

// Taken from Golan Levin's paper "Polynomial Shaping Functions"
// https://www.flong.com/archive/texts/code/shapers_poly/

//------------------------------------------------
float BlinnWyvilCosApprox(float x)
{
    float x2 = x * x;
    float x4 = x2 * x2;
    float x6 = x4 * x2;

    float fa =  4.0/9.0;
    float fb = 17.0/9.0;
    float fc = 22.0/9.0;

    float y = fa*x6 - fb*x4 + fc*x2;
    return y;
}

//------------------------------------------------
// Joins two 3rd-order polynomials meeting with horizontal inflection
// at point p in the unit square
float DoubleCubicSeat(float x, vec2 p)
{
    float a = p.x;
    float b = p.y;
    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0;
    float max_param_b = 1.0;
    a = clamp(a, min_param_a, max_param_a);
    b = clamp(b, min_param_b, max_param_b);

    float y = 0;
    if(x <= a)
    {
        y = b - b*pow(1 - x/a, 3.0);
    }
    else
    {
        y = b + (1 - b)*pow((x - a)/(1 - a), 3.0);
    }
    return y;
}

//------------------------------------------------
// Same as before but at point (a; a) with inflection determined by b
float DoubleCubicSeatWithLinearBlend(float x, float a, float b)
{
    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0;
    float max_param_b = 1.0;
    a = clamp(a, min_param_a, max_param_a);
    b = clamp(b, min_param_b, max_param_b);
    b = 1.0 - b; //reverse for intelligibility.

    float y = 0;
    if (x <= a)
    {
        y = b*x + (1 - b)*a*(1 - pow(1 - x/a, 3.0));
    }
    else
    {
        y = b*x + (1 - b)*(a + (1 - a)*pow((x - a)/(1 - a), 3.0));
    }
    return y;
}

//------------------------------------------------
// Generalization of the above for (2n + 1) order polynomials
// where n controls the flatness/breadth of the curve at the meeting point
float DoubleOddPolynomialSeat(float x, vec2 p, int n)
{
    float a = p.x;
    float b = p.y;
    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0;
    float max_param_b = 1.0;
    a = clamp(a, min_param_a, max_param_a);
    b = clamp(b, min_param_b, max_param_b);

    int p_ = 2*n + 1;
    float y = 0;
    if (x <= a){
        y = b - b*pow(1-x/a, p_);
    }
    else
    {
        y = b + (1-b)*pow((x-a)/(1-a), p_);
    }
    return y;
}

//------------------------------------------------
// A sigmoid obtained by joining two nth order polynomials
// F(0) = 0, dFdx(0) = 0, F(1) = 1, dFdx(1) = 0, F(0.5) = 0.5
float DoublePolynomialSigmoid(float x, int n)
{
    float y = 0.0;
    if(x <= 0.5)
    {
        y = pow(2.0*x, n)/2.0;
    }
    else
    {
        y = 1.0 - pow(2.0*(1.0 - x), n)/2.0;
    }
    return y;
}

//------------------------------------------------
// A parabola passing through (0; 0), p, (1; 0)
float QuadraticThroughGivenPoint(float x, vec2 p)
{
    float a = p.x;
    float b = p.y;
    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0f;
    float max_param_b = 1.0f;
    a = clamp(a, min_param_a, max_param_a);
    b = clamp(b, min_param_b, max_param_b);

    float A = (b - a)/(a*a - a);
    float B = 1.0 - A;
    float y = A*(x*x) + B*(x);
    y = clamp(y, 0.0, 1.0);

    return y;
}

#endif
