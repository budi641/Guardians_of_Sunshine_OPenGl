#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;


void main() {
    vec2 redShift = vec2(0.005 * sin(time), 0.0);
    vec2 greenShift = vec2(0.0, 0.005 * cos(time));
    vec2 blueShift = vec2(-0.005 * sin(time), 0.0);

    float r = texture(screenTexture, TexCoords + redShift).r;
    float g = texture(screenTexture, TexCoords + greenShift).g;
    float b = texture(screenTexture, TexCoords + blueShift).b;

    FragColor = vec4(r, g, b, 1.0);
}
