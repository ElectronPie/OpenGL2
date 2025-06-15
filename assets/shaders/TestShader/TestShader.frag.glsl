#version 430 core

// The color output variable
layout(location = 0) out vec4 FragColor;

// Standard uniform declarations
uniform float u_time;
uniform vec2 u_mouse;
uniform vec2 u_resolution;

#include "Constants.glsl"
#include "HSV.glsl"

float shaping(in float h)
{
    return h <= 0.5 ?
        2.0/3.0*h :
        4.0/3.0*h - 1.0/3.0;
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution;
    vec3 color = vec3(0.0);

    // Use polar coordinates instead of cartesian
    vec2 toCenter = vec2(0.5) - st;
    float angle = atan(toCenter.y, toCenter.x);
    angle = mod(angle+u_time, TWO_PI);
    float radius = length(toCenter);
    radius = radius >= 0.5 ? 0.0 : radius;

    // Map the angle (-PI to PI) to the Hue (from 0 to 1)
    // and the Saturation to the radius
    color = HSV2RGB(vec3(shaping(angle/TWO_PI), 2.0*radius, 1.0));

    FragColor = vec4(color, 1.0);
}
