#version 430 core

// The color output variable
layout(location = 0) out vec4 FragColor;

// Standard uniform declarations
uniform float u_time;
uniform vec2 u_mouse;
uniform vec2 u_resolution;

void main()
{
    vec2 st = vec2(gl_FragCoord.x, u_mouse.y) / u_resolution;
    FragColor = vec4(st, 0.0, 1.0);
}
