#version 430 core

// The color output variable
layout(location = 0) out vec4 FragColor;

// Standard uniform declarations
uniform float u_time;
uniform vec2 u_mouse;
uniform vec2 u_resolution;

uniform int u_functionID;
uniform float u_zoom;
uniform vec2 u_p1;
uniform vec2 u_p2;
uniform float u_point;
uniform float u_inflection;
uniform int u_exponent;
uniform float u_radius;

#include "Polynomial.glsl"
#include "Exponential.glsl"
#include "CircularElliptical.glsl"
#include "Bezier.glsl"
#include "Identities.glsl"
#include "Impulses.glsl"
#include "UnitaryRemappings.glsl"
#include "PulsesBumpsSteps.glsl"

float plot(vec2 st, float pct)
{
    return smoothstep(pct - 0.02, pct, st.y) - smoothstep(pct, pct + 0.02, st.y);
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution;

    float x = st.x;
    float y;
    switch(u_functionID)
    {
    case 0:
        y = x;
        break;
    case 1:
        y = BlinnWyvilCosApprox(x * u_zoom);
        break;
    case 2:
        y = DoubleCubicSeat(x, u_p1);
        break;
    case 3:
        y = DoubleCubicSeatWithLinearBlend(x, u_point, u_inflection);
        break;
    case 4:
        y = DoubleOddPolynomialSeat(x, u_p1, u_exponent);
        break;
    case 5:
        y = DoublePolynomialSigmoid(x, u_exponent);
        break;
    case 6:
        y = QuadraticThroughGivenPoint(x, u_p1);
        break;
    case 7:
        y = ExponentialEasing(x, u_inflection);
        break;
    case 8:
        y = DoubleExponentialSeat(x, u_inflection);
        break;
    case 9:
        y = DoubleExponentialSigmoid(x, u_inflection);
        break;
    case 10:
        y = LogisticSigmoid(x, u_inflection);
        break;
    case 11:
        y = CircularEaseIn(x);
        break;
    case 12:
        y = CircularEaseOut(x);
        break;
    case 13:
        y = DoubleCircleSeat(x, u_point);
        break;
    case 14:
        y = DoubleCircleSigmoid(x, u_point);
        break;
    case 15:
        y = DoubleEllipticSeat(x, u_p1);
        break;
    case 16:
        y = DoubleEllipticSigmoid(x, u_p1);
        break;
    case 17:
        y = CircularFillet(x, u_p1, u_radius);
        break;
    case 18:
        y = CircularArcThroughPoint(x, u_p1);
        break;
    case 19:
        y = QuadraticBezier(x, u_p1);
        break;
    case 20:
        y = CubicBezier(x, u_p1, u_p2);
        break;
    case 21:
        y = CubicBezierNearlyThroughTwoPoints(x, u_p1, u_p2);
        break;
    case 22:
        y = AlmostIdentity(x*u_zoom, u_p1.x, u_p1.y)/u_zoom;
        break;
    case 23:
        y = AlmostAbs(x*u_zoom, u_point)/u_zoom;
        break;
    case 24:
        y = SmoothstepIntegral(x*u_zoom, u_point)/u_zoom;
        break;
    case 25:
        y = ExponentialImpulse(x*u_zoom, u_inflection)/u_zoom;
        break;
    case 26:
        y = QuadraticImpulse(x*u_zoom, u_inflection)/u_zoom;
        break;
    case 27:
        y = PolynomialImpulse(x*u_zoom, u_inflection, u_exponent)/u_zoom;
        break;
    case 28:
        y = ExponentialSustainedImpulse(x*u_zoom, u_p1.x, u_p1.y)/u_zoom;
        break;
    case 29:
        y = Sinc(x*u_zoom, u_point)/u_zoom/2.0 + 0.5;
        break;
    case 30:
        y = TruncatedFalloff(x*u_zoom, u_point)/u_zoom;
        break;
    case 31:
        y = AlmostUnitIdentity(x);
        break;
    case 32:
        y = Gain(x, u_inflection);
        break;
    case 33:
        y = Parabola(x, u_inflection);
        break;
    case 34:
        y = PowerCurve(x, u_p1.x, u_p1.y);
        break;
    case 35:
        y = Tone(x, u_inflection);
        break;
    case 36:
        y = CubicPulse(x, u_p1.x, u_p1.y);
        break;
    case 37:
        y = RationalBump(x, u_inflection);
        break;
    case 38:
        y = ExponentialStep(x, u_exponent);
        break;
    }

    vec3 color = vec3(y);
    float pct;

    switch(u_functionID)
    {
    case 2:
    case 4:
    case 6:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        pct = 1.0 - length(st - u_p1)/0.03;
        pct = sqrt(pct);
        pct = clamp(pct, 0.0, 1.0);
        color = (1.0 - pct)*color + pct*vec3(1.0, 0.0, 0.0);
        break;
    case 3:
    case 13:
    case 14:
        pct = plot(st.yx, u_point);
        color = (1.0 - pct)*color + pct*vec3(1.0, 0.0, 0.0);
        break;
    case 20:
    case 21:
        pct = 1.0 - length(st - u_p2)/0.03;
        pct = sqrt(pct);
        pct = clamp(pct, 0.0, 1.0);
        color = (1.0 - pct)*color + pct*vec3(1.0, 1.0, 0.0);
        pct = 1.0 - length(st - u_p1)/0.03;
        pct = sqrt(pct);
        pct = clamp(pct, 0.0, 1.0);
        color = (1.0 - pct)*color + pct*vec3(1.0, 0.0, 0.0);
        break;
    case 22:
        pct = 1.0 - length(st - u_p1/u_zoom)/0.03;
        pct = sqrt(pct);
        pct = clamp(pct, 0.0, 1.0);
        color = (1.0 - pct)*color + pct*vec3(1.0, 0.0, 0.0);
        break;
    case 23:
    case 24:
    case 30:
        pct = plot(st.yx, u_point/u_zoom);
        color = (1.0 - pct)*color + pct*vec3(1.0, 0.0, 0.0);
        break;
    }

    // Plot a line
    pct = plot(st, y);
    color = (1.0 - pct)*color + pct*vec3(0.0, 1.0, 0.0);

    FragColor = vec4(color, 1.0);
}
