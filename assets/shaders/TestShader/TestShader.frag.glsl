#version 430 core

// The color output variable
layout(location = 0) out vec4 FragColor;

// Standard uniform declarations
uniform float u_time;
uniform vec2 u_mouse;
uniform vec2 u_resolution;

uniform int u_functionID;

#include "Easings.glsl"

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
        y = SinEaseIn(x);
        break;
    case 2:
        y = SinEaseOut(x);
        break;
    case 3:
        y = SinEaseInOut(x);
        break;
    case 4:
        y = SinEaseOutIn(x);
        break;
    case 5:
        y = CircularEaseIn(x);
        break;
    case 6:
        y = CircularEaseOut(x);
        break;
    case 7:
        y = CircularEaseInOut(x);
        break;
    case 8:
        y = CircularEaseOutIn(x);
        break;
    case 9:
        y = QuadraticEaseIn(x);
        break;
    case 10:
        y = QuadraticEaseOut(x);
        break;
    case 11:
        y = QuadraticEaseInOut(x);
        break;
    case 12:
        y = QuadraticEaseOutIn(x);
        break;
    case 13:
        y = CubicEaseIn(x);
        break;
    case 14:
        y = CubicEaseOut(x);
        break;
    case 15:
        y = CubicEaseInOut(x);
        break;
    case 16:
        y = CubicEaseOutIn(x);
        break;
    case 17:
        y = QuartEaseIn(x);
        break;
    case 18:
        y = QuartEaseOut(x);
        break;
    case 19:
        y = QuartEaseInOut(x);
        break;
    case 20:
        y = QuartEaseOutIn(x);
        break;
    case 21:
        y = QuintEaseIn(x);
        break;
    case 22:
        y = QuintEaseOut(x);
        break;
    case 23:
        y = QuintEaseInOut(x);
        break;
    case 24:
        y = QuintEaseOutIn(x);
        break;
    case 25:
        y = ExponentialEaseIn(x);
        break;
    case 26:
        y = ExponentialEaseOut(x);
        break;
    case 27:
        y = ExponentialEaseInOut(x);
        break;
    case 28:
        y = ExponentialEaseOutIn(x);
        break;
    case 29:
        y = EaseInBack(x);
        break;
    case 30:
        y = EaseOutBack(x);
        break;
    case 31:
        y = EaseInOutBack(x);
        break;
    case 32:
        y = EaseOutInBack(x);
        break;
    case 33:
        y = ElasticEaseIn(x);
        break;
    case 34:
        y = ElasticEaseOut(x);
        break;
    case 35:
        y = ElasticEaseInOut(x);
        break;
    case 36:
        y = ElasticEaseOutIn(x);
        break;
    case 37:
        y = EaseInBounce(x);
        break;
    case 38:
        y = EaseOutBounce(x);
        break;
    case 39:
        y = EaseInOutBounce(x);
        break;
    case 40:
        y = EaseOutInBounce(x);
        break;
    }

    vec3 color = vec3(y);
    float pct;

    // Plot a line
    pct = plot(st, y);
    color = (1.0 - pct)*color + pct*vec3(0.0, 1.0, 0.0);

    FragColor = vec4(color, 1.0);
}
