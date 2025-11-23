#version 430 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D u_texture;
uniform vec2 u_offset;

void main()
{
    // clang-format off
    vec2 offsets[9] = vec2[](
        vec2(-u_offset.x,  u_offset.y), // top-left
        vec2( 0.0f,        u_offset.y), // top-center
        vec2( u_offset.x,  u_offset.y), // top-right
        vec2(-u_offset.x,  0.0f),       // center-left
        vec2( 0.0f,        0.0f),       // center-center
        vec2( u_offset.x,  0.0f),       // center-right
        vec2(-u_offset.x, -u_offset.y), // bottom-left
        vec2( 0.0f,       -u_offset.y), // bottom-center
        vec2( u_offset.x, -u_offset.y)  // bottom-right
    );

    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );
    // clang-format on

    vec3 sampleTex[9];
    for(int i = 0; i < 9; ++i)
    {
        sampleTex[i] = vec3(texture(u_texture, texCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; ++i)
    {
        col += sampleTex[i] * kernel[i];
    }

    FragColor = vec4(col, 1.0);
}
