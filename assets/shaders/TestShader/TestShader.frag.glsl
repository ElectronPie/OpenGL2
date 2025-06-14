#version 430 core

// The color output variable
layout(location = 0) out vec4 FragColor;

// Standard uniform declarations
uniform float u_time;
uniform vec2 u_mouse;
uniform vec2 u_resolution;

#include "Easings.glsl"

vec3 colorA = vec3(0.129,0.336,0.184);
vec3 colorB = vec3(0.863,0.605,0.164);

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution;

    float speed = 0.5;
    float pct = abs(fract(-u_time*speed/2.0)*2.0 - 1.0);
    float y;
    vec3 color = vec3(0);

    //y = pct;
    //y = SinEaseIn(pct);
    //y = SinEaseOut(pct);
    //y = SinEaseInOut(pct);
    //y = SinEaseOutIn(pct);
    //y = CircularEaseIn(pct);
    //y = CircularEaseOut(pct);
    //y = CircularEaseInOut(pct);
    //y = CircularEaseOutIn(pct);
    //y = QuadraticEaseIn(pct);
    //y = QuadraticEaseOut(pct);
    //y = QuadraticEaseInOut(pct);
    //y = QuadraticEaseOutIn(pct);
    //y = CubicEaseIn(pct);
    //y = CubicEaseOut(pct);
    //y = CubicEaseInOut(pct);
    //y = CubicEaseOutIn(pct);
    //y = QuartEaseIn(pct);
    //y = QuartEaseOut(pct);
    //y = QuartEaseInOut(pct);
    //y = QuartEaseOutIn(pct);
    //y = QuintEaseIn(pct);
    //y = QuintEaseOut(pct);
    //y = QuintEaseInOut(pct);
    //y = QuintEaseOutIn(pct);
    //y = ExponentialEaseIn(pct);
    //y = ExponentialEaseOut(pct);
    //y = ExponentialEaseInOut(pct);
    //y = ExponentialEaseOutIn(pct);
    //y = EaseInBack(pct);
    //y = EaseOutBack(pct);
    //y = EaseInOutBack(pct);
    //y = EaseOutInBack(pct);
    //y = ElasticEaseIn(pct);
    //y = ElasticEaseOut(pct);
    //y = ElasticEaseInOut(pct);
    //y = ElasticEaseOutIn(pct);
    //y = EaseInBounce(pct);
    //y = EaseOutBounce(pct);
    //y = EaseInOutBounce(pct);
    y = EaseOutInBounce(pct);

    color = mix(colorA, colorB, pct);

    FragColor = vec4(color, 1.0);
}
