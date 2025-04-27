#ifndef CIRCULAR_ELLIPTICAL_INCLUDED
#define CIRCULAR_ELLIPTICAL_INCLUDED

#include "Sq.glsl"

// Taken from Golan Levin's paper "Circular & Elliptical Shaping Functions"
// https://www.flong.com/archive/texts/code/shapers_circ/

//------------------------------------------------
float CircularEaseIn(float x)
{
    float y = 1 - sqrt(1 - x*x);
    return y;
}

//------------------------------------------------
float CircularEaseOut(float x)
{
    float y = sqrt(1 - sq(1-x));
    return y;
}

//------------------------------------------------
float DoubleCircleSeat(float x, float a)
{
    float min_param_a = 0.0f;
    float max_param_a = 1.0f;
    a = clamp(a, min_param_a, max_param_a);

    float y;
    if(x <= a)
    {
        y = sqrt(sq(a) - sq(x-a));
    }
    else
    {
        y = 1 - sqrt(sq(1-a) - sq(x-a));
    }
    return y;
}

//------------------------------------------------
float DoubleCircleSigmoid(float x, float a)
{
    float min_param_a = 0.0f;
    float max_param_a = 1.0f;
    a = clamp(a, min_param_a, max_param_a);

    float y;
    if(x <= a)
    {
        y = a - sqrt(a*a - x*x);
    }
    else
    {
        y = a + sqrt(sq(1-a) - sq(x-1));
    }
    return y;
}

//------------------------------------------------
float DoubleEllipticSeat(float x, vec2 p)
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
    if (x <= a)
    {
        y = (b/a) * sqrt(sq(a) - sq(x-a));
    }
    else
    {
        y = 1 - ((1-b)/(1-a))*sqrt(sq(1-a) - sq(x-a));
    }
    return y;
}

//------------------------------------------------
float DoubleEllipticSigmoid(float x, vec2 p)
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
    if (x <= a)
    {
        y = b * (1 - (sqrt(sq(a) - sq(x))/a));
    }
    else
    {
        y = b + ((1-b)/(1-a))*sqrt(sq(1-a) - sq(x-1));
    }
    return y;
}

//------------------------------------------------
// Joining Two Lines with a Circular Arc Fillet
// Adapted from Robert D. Miller / Graphics Gems III.

float arcStartAngle = 0.0;
float arcEndAngle = 0.0;
vec2 arcStart = vec2(0.0);
vec2 arcEnd = vec2(0.0);
vec2 arcCenter = vec2(0.0);
float arcRadius = 0.0;

// Return signed distance from line ax + by + c = 0 to point p
float LineToPoint(float a, float b, float c, vec2 p)
{
    float lp = 0.0;
    float d = sqrt(a*a + b*b);
    if(d != 0.0)
    {
        lp = (a*p.x + b*p.y + c)/d;
    }
    return lp;
}

void ComputeFilletParameters(vec2 p1, vec2 p2, vec2 p3, vec2 p4, float R)
{
    float c1 = p2.x*p1.y - p1.x*p2.y;
    float a1 = p2.y - p1.y;
    float b1 = p1.x - p2.x;
    float c2 = p4.x*p3.y - p3.x*p4.y;
    float a2 = p4.y - p3.y;
    float b2 = p3.x - p4.x;
    if(a1*b2 == a2*b1)
    {
        // Parallel or coincident lines
        return;
    }

    float d1, d2;
    vec2 mP;
    mP = (p3 + p4)/2.0;
    d1 = LineToPoint(a1, b1, c1, mP); // Find distance p1p2 to p3
    if(d1 == 0.0)
    {
        return;
    }
    mP = (p1 + p2)/2.0;
    d2 = LineToPoint(a2, b2, c2, mP); // Find distance p3p4 to p2
    if(d2 == 0.0)
    {
        return;
    }

    float c1p, c2p;
    float rr = R;
    if(d1 >= 0.0)
    {
        rr = -rr;
    }
    c1p = c1 + rr*sqrt((a1*a1)+(b1*b1)); // Line parallel to l1 at d
    rr = R;
    if(d2 <= 0.0)
    {
        rr = -rr;
    }
    c2p = c2 - rr*sqrt((a2*a2)+(b2*b2)); // Line parallel to l2 at d

    float d = (a1*b2) - (a2*b1);
    vec2 pC = vec2(c2p*b1-c1p*b2, c1p*a2-c2p*a1)/d; // Intersect constructed lines to find center of arc
    vec2 pA = vec2(0.0);
    vec2 pB = vec2(0.0);
    float dP, cP;

    // Clip or extend lines as required
    dP = (a1*a1) + (b1*b1);
    if(dP != 0.0)
    {
        cP = a1*pC.y - b1*pC.x;
        pA.x = (-a1*c1 - b1*cP)/dP;
        pA.y = ( a1*cP - b1*c1)/dP;
    }
    dP = (a2*a2) + (b2*b2);
    if(dP != 0.0){
        cP = a2*pC.y - b2*pC.x;
        pB.x = (-a2*c2 - b2*cP)/dP;
        pB.y = ( a2*cP - b2*c2)/dP;
    }

    vec2 gv1 = pA - pC;
    vec2 gv2 = pB - pC;

    float arcStart_ = atan(gv1.y, gv1.x);
    float arcAngle = 0.0;
    float dd = length(gv1)*length(gv2);
    if(dd != 0.0)
    {
        arcAngle = acos(dot(gv1, gv2)/dd);
    }
    float crossProduct = gv1.x*gv2.y - gv2.x*gv1.y;
    if(crossProduct < 0.0)
    {
        arcStart_ -= arcAngle;
    }

    float arc1 = arcStart_;
    float arc2 = arcStart_ + arcAngle;
    if(crossProduct < 0.0)
    {
        arc1 = arcStart_ + arcAngle;
        arc2 = arcStart_;
    }

    arcCenter     = pC;
    arcStartAngle = arc1;
    arcEndAngle   = arc2;
    arcRadius     = R;
    arcStart      = arcCenter + arcRadius*vec2(cos(arcStartAngle), sin(arcStartAngle));
    arcEnd        = arcCenter + arcRadius*vec2(cos(arcEndAngle), sin(arcEndAngle));
}

float CircularFillet(float x, vec2 p, float R)
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

    ComputeFilletParameters(vec2(0.0), p, p, vec2(1.0), R);
    float t;
    float y;
    x = clamp(x, 0.0, 1.0);

    if(x <= arcStart.x)
    {
        t = x / arcStart.x;
        y = t * arcStart.y;
    }
    else if(x >= arcEnd.x)
    {
        t = (x - arcEnd.x)/(1 - arcEnd.x);
        y = arcEnd.y + t*(1 - arcEnd.y);
    }
    else
    {
        y = arcCenter.y + sign(arcCenter.x - x)*sqrt(sq(arcRadius) - sq(x - arcCenter.x));
    }
    return y;
}

//------------------------------------------------
// Adapted from Paul Bourke

vec2 m_center = vec2(0.0);
float m_dRadius = 0.0;

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
    else if(abs(dB.x)<= epsilon)
    {
        return true;
    }
    else return false;
}

void CalcCircleFrom3Points(vec2 p1, vec2 p2, vec2 p3)
{
    vec2 dA = p2 - p1;
    vec2 dB = p3 - p2;
    float epsilon = 0.000001;

    if(abs(dA.x) <= epsilon && abs(dB.x) <= epsilon)
    {
        m_center = 0.5*vec2(p2.x + p3.x, p1.y + p2.y);
        m_dRadius = length(m_center - p1);
        return;
    }

    // IsPerpendicular() assures d*.x is not zero
    float aSlope = dA.y / dA.x;
    float bSlope = dB.y / dB.x;
    // Checking whether the given points are colinear
    if(abs(aSlope - bSlope) <= epsilon)
        return;

    // Calc center
    m_center.x = (
        aSlope*bSlope*(p1.y - p3.y) +
        bSlope*(p1.x + p2.x) -
        aSlope*(p2.x + p3.x)
    )/(2.0*(bSlope - aSlope));
    m_center.y = (-1.0/aSlope)*(m_center.x - (p1.x+p2.x)/2.0) + (p1.y+p2.y)/2.0;
    m_dRadius = length(m_center - p1);
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

    if(!IsPerpendicular(p1, p2, p3))
        CalcCircleFrom3Points(p1, p2, p3);
    else if(!IsPerpendicular(p1, p3, p2))
        CalcCircleFrom3Points(p1, p3, p2);
    else if(!IsPerpendicular(p2, p1, p3))
        CalcCircleFrom3Points(p2, p1, p3);
    else if(!IsPerpendicular(p2, p3, p1))
        CalcCircleFrom3Points(p2, p3, p1);
    else if(!IsPerpendicular(p3, p1, p2))
        CalcCircleFrom3Points(p3, p1, p2);
    else if(!IsPerpendicular(p3, p2, p1))
        CalcCircleFrom3Points(p3, p2, p1);
    else
    {
        return 0.0;
    }

    if(m_dRadius == 0.0)
        return x;

    // constrain
    if(
        clamp(m_center.x, 0.0+epsilon, 1.0-epsilon) == m_center.x &&
        clamp(m_center.y, 0.0+epsilon, 1.0-epsilon) == m_center.y
    )
    {
        if(a < m_center.x)
        {
            m_center = vec2(1.0, 0.0);
            m_dRadius = 1.0;
        }
        else
        {
            m_center = vec2(0.0, 1.0);
            m_dRadius = 1.0;
        }
    }

    float y = 0.0;
    if(x >= m_center.x)
    {
        y = m_center.y - sqrt(sq(m_dRadius) - sq(x - m_center.x));
    }
    else
    {
        y = m_center.y + sqrt(sq(m_dRadius) - sq(x - m_center.x));
    }
    return y;
}

#endif
