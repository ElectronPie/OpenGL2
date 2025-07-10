#version 430 core

// The color output variable
layout(location = 0) out vec4 FragColor;

// Standard uniform declarations
uniform float u_time;
uniform vec2 u_mouse;
uniform vec2 u_resolution;

uniform vec4 u_rectangle;

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

    // Bottom left corner
    vec2 bl = step(u_rectangle.xy, st);
    float pct = bl.x * bl.y;

    // Top right corner
    vec2 tr = step(1.0 - u_rectangle.zw, 1.0 - st);
    pct *= tr.x * tr.y;

    color = vec3(pct);

    FragColor = vec4(color, 1.0);
}
