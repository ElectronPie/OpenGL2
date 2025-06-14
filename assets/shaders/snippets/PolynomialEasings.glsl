#ifndef POLYNOMIAL_EASINGS_INCLUDED
#define POLYNOMIAL_EASINGS_INCLUDED

//------------------------------------------------
float PolynomialEaseIn(float x, int n)
{
    x = clamp(x, 0.0, 1.0);
    return pow(x, n);
}

//------------------------------------------------
float PolynomialEaseOut(float x, int n)
{
    x = clamp(x, 0.0, 1.0);
    return 1.0 - pow(1.0 - x, n);
}

//------------------------------------------------
float PolynomialEaseInOut(float x, int n)
{
    x = clamp(x, 0.0, 1.0);
    return x < 0.5 ?
        pow(2.0*x, n)/2.0 :
        (1.0 - pow(2.0 - 2.0*x, n))/2.0 + 0.5;
}

//------------------------------------------------
float PolynomialEaseOutIn(float x, int n)
{
    x = clamp(x, 0.0, 1.0);
    return x < 0.5 ?
        (1.0 - pow(1.0 - 2.0*x, n))/2.0 :
        pow(2.0*x - 1.0, n)/2.0 + 0.5;
}

//------------------------------------------------
float QuadraticEaseIn(float x)
{
    return PolynomialEaseIn(x, 2);
}

//------------------------------------------------
float QuadraticEaseOut(float x)
{
    return PolynomialEaseOut(x, 2);
}

//------------------------------------------------
float QuadraticEaseInOut(float x)
{
    return PolynomialEaseInOut(x, 2);
}

//------------------------------------------------
float QuadraticEaseOutIn(float x)
{
    return PolynomialEaseOutIn(x, 2);
}

//------------------------------------------------
float CubicEaseIn(float x)
{
    return PolynomialEaseIn(x, 3);
}

//------------------------------------------------
float CubicEaseOut(float x)
{
    return PolynomialEaseOut(x, 3);
}

//------------------------------------------------
float CubicEaseInOut(float x)
{
    return PolynomialEaseInOut(x, 3);
}

//------------------------------------------------
float CubicEaseOutIn(float x)
{
    return PolynomialEaseOutIn(x, 3);
}

//------------------------------------------------
float QuartEaseIn(float x)
{
    return PolynomialEaseIn(x, 4);
}

//------------------------------------------------
float QuartEaseOut(float x)
{
    return PolynomialEaseOut(x, 4);
}

//------------------------------------------------
float QuartEaseInOut(float x)
{
    return PolynomialEaseInOut(x, 4);
}

//------------------------------------------------
float QuartEaseOutIn(float x)
{
    return PolynomialEaseOutIn(x, 4);
}

//------------------------------------------------
float QuintEaseIn(float x)
{
    return PolynomialEaseIn(x, 5);
}

//------------------------------------------------
float QuintEaseOut(float x)
{
    return PolynomialEaseOut(x, 5);
}

//------------------------------------------------
float QuintEaseInOut(float x)
{
    return PolynomialEaseInOut(x, 5);
}

//------------------------------------------------
float QuintEaseOutIn(float x)
{
    return PolynomialEaseOutIn(x, 5);
}

#endif
