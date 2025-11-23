#ifndef EXPONENTIAL_BASE_INCLUDED
#define EXPONENTIAL_BASE_INCLUDED

// Taken from Golan Levin's paper "Exponential Shaping Functions"
// https://www.flong.com/archive/texts/code/shapers_exp/

//------------------------------------------------
float ExponentialEasing(float x, float a)
{
    float epsilon     = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    a                 = clamp(a, min_param_a, max_param_a);

    float y = 0.0;
    if(a <= 0.5)
    {
        // emphasis
        a = 2.0 * (a);
        y = pow(x, a);
    }
    else
    {
        // de-emphasis
        a = 2.0 * (a - 0.5);
        y = pow(x, 1.0 / (1.0 - a));
    }
    return y;
}

//------------------------------------------------
float DoubleExponentialSeat(float x, float a)
{
    float epsilon     = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    a                 = clamp(a, min_param_a, max_param_a);

    float y;
    if(x <= 0.5)
    {
        y = pow(2.0 * x, 1.0 - a) / 2.0;
    }
    else
    {
        y = 1.0 - pow(2.0 * (1.0 - x), 1.0 - a) / 2.0;
    }
    return y;
}

//------------------------------------------------
float DoubleExponentialSigmoid(float x, float a)
{
    float epsilon     = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    a                 = clamp(a, min_param_a, max_param_a);
    a                 = 1.0 - a; // for sensible results

    float y;
    if(x <= 0.5)
    {
        y = pow(2.0 * x, 1.0 / a) / 2.0;
    }
    else
    {
        y = 1.0 - pow(2.0 * (1.0 - x), 1.0 / a) / 2.0;
    }
    return y;
}

//------------------------------------------------
float LogisticSigmoid(float x, float a)
{
    // n.b.: this Logistic Sigmoid has been normalized.

    float epsilon     = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    a                 = clamp(a, min_param_a, max_param_a);
    a                 = 1 / (1 - a) - 1;

    float A = 1.0 / (1.0 + exp(0 - ((x - 0.5) * a * 2.0)));
    float B = 1.0 / (1.0 + exp(a));
    float C = 1.0 / (1.0 + exp(0 - a));
    float y = (A - B) / (C - B);
    return y;
}

#endif
