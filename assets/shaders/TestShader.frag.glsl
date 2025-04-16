#version 430 core

// The color output variable
layout(location = 0) out vec4 FragColor;

// Standard uniform declarations
uniform float u_time;
uniform vec2 u_mouse;
uniform vec2 u_resolution;

#define PI 3.141596
#define TWO_PI 6.283192

float plot(vec2 st, float pct)
{
    return smoothstep(pct - 0.02, pct, st.y) - smoothstep(pct, pct + 0.02, st.y);
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution;

    float y;

    // Plot a line on Y using a value between 0.0-1.0
    //y = st.x;

    // Make the line curved
    //y = pow(st.x, 5);

    // Step will return 0.0 unless the value is over 0.5, in that case it will return 1.0
    //y = step(0.5, y);

    // Interpolate betweenthe two values smoothly
    //y = smoothstep(0.0, 1.0, st.x);

    // A smooth bump
    //y = smoothstep(0.2,0.5,st.x) - smoothstep(0.5,0.8,st.x);

    // A sine wave
    //y = sin(st.x) / 2.0 + 0.5;
    // Zooming out
    y = sin(st.x * u_time) / 2.0 + 0.5;
    // And displaced
    //y = (sin(st.x * u_time) / 2.0 + 0.5) + 0.6;
    // Or with altered amplitude
    //y = (sin(st.x * u_time) * 2.0 / 2.0 + 0.5);
    // The absolute (looks like a trail of a bouncing ball)
    //y = abs(sin(st.x * u_time));
    // Extract just the fraction part
    //y = fract(sin(st.x * u_time)) / 2.0 + 0.5;
    // Rounding up to the nearest integer
    //y = ceil(sin(st.x * u_time)) / 2.0 + 0.5;
    // Rounding down to the nearest integer
    //y = floor(sin(st.x * u_time)) / 2.0 + 0.5;

    float x = st.x * u_time;

    // Some other useful functions
    //y = mod(x,0.5); // return x modulo of 0.5
    //y = fract(x); // return only the fraction part of a number
    //y = ceil(x);  // nearest integer that is greater than or equal to x
    //y = floor(x); // nearest integer less than or equal to x
    //y = sign(x);  // extract the sign of x
    //y = abs(x);   // return the absolute value of x
    //y = clamp(x,0.0,1.0); // constrain x to lie between 0.0 and 1.0
    //y = min(0.0,x);   // return the lesser of x and 0.0
    //y = max(0.0,x);   // return the greater of x and 0.0

    vec3 color = vec3(y);

    // Plot a line
    float pct = plot(st, y);
    color = (1.0 - pct) * color + pct * vec3(0.0, 1.0, 0.0);

    FragColor = vec4(color, 1.0);
}
