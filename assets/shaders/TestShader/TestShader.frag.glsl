#version 430 core

// The color output variable
layout(location = 0) out vec4 FragColor;

// Standard uniform declarations
uniform float u_time;
uniform vec2 u_mouse;
uniform vec2 u_resolution;

#include "HSV.glsl"

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution;

    vec3 color = vec3(0.0);

    // We map x (0.0 - 1.0) to the hue (0.0 - 1.0)
    // And the y (0.0 - 1.0) to the brightness
    color = HSV2RGB(vec3(st.x, 1.0, st.y));

    FragColor = vec4(color, 1.0);
}
