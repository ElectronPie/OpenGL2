#ifndef CIRCULAR_FILLET_INCLUDED
#define CIRCULAR_FILLET_INCLUDED

#include "Pows.glsl"

//------------------------------------------------
// Joining Two Lines with a Circular Arc Fillet
// Adapted from Robert D. Miller / Graphics Gems III.

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

void ComputeFilletParameters(
    in vec2 p1, in vec2 p2, in vec2 p3, in vec2 p4,
    inout float R,
    out float arcStartAngle,
    out float arcEndAngle,
    out vec2 arcStart,
    out vec2 arcEnd,
    out vec2 arcCenter
)
{
    arcStartAngle = 0.0;
    arcEndAngle = 0.0;
    arcStart = vec2(0.0);
    arcEnd = vec2(0.0);
    arcCenter = vec2(0.0);

    float c1 = p2.x*p1.y - p1.x*p2.y;
    float a1 = p2.y - p1.y;
    float b1 = p1.x - p2.x;
    float c2 = p4.x*p3.y - p3.x*p4.y;
    float a2 = p4.y - p3.y;
    float b2 = p3.x - p4.x;
    if(a1*b2 == a2*b1)
    {
        // Parallel or coincident lines
        R = 0.0;
        return;
    }

    float d1, d2;
    vec2 mP;
    mP = (p3 + p4)/2.0;
    d1 = LineToPoint(a1, b1, c1, mP); // Find distance p1p2 to p3
    if(d1 == 0.0)
    {
        R = 0.0;
        return;
    }
    mP = (p1 + p2)/2.0;
    d2 = LineToPoint(a2, b2, c2, mP); // Find distance p3p4 to p2
    if(d2 == 0.0)
    {
        R = 0.0;
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
    arcStart      = arcCenter + R*vec2(cos(arcStartAngle), sin(arcStartAngle));
    arcEnd        = arcCenter + R*vec2(cos(arcEndAngle), sin(arcEndAngle));
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

    float arcStartAngle;
    float arcEndAngle;
    vec2 arcStart;
    vec2 arcEnd;
    vec2 arcCenter;
    ComputeFilletParameters(
        vec2(0.0), p, p, vec2(1.0),
        R,
        arcStartAngle, arcEndAngle, arcStart, arcEnd, arcCenter
    );
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
        y = arcCenter.y + sign(arcCenter.x - x)*sqrt(sq(R) - sq(x - arcCenter.x));
    }
    return y;
}

#endif
