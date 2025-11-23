#version 430 core

in vec2 texCoords;

out vec4 FragColor;

uniform bool u_displayDepthBuffer;
uniform float u_near;
uniform float u_far;
uniform sampler2D u_texture;

void main()
{
    if(!u_displayDepthBuffer)
    {
        // Sample the texture at the given texture coordinates
        FragColor = texture(u_texture, texCoords);
    }
    else
    {
        float ndc   = 2.0 * gl_FragCoord.z - 1.0; // Convert to NDC
        float depth = (2.0 * u_near * u_far) / (u_far + u_near - ndc * (u_far - u_near));
        FragColor   = vec4(vec3(depth), 1.0f);
    }
}
