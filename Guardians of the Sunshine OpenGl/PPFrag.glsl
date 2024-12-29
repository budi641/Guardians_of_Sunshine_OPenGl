#version 300 es
precision highp float;

uniform sampler2D screenTexture; 
uniform vec2 u_resolution;  
uniform float u_time;      

out vec4 fragColor;

// Random noise function
float random(vec2 uv) {
    return fract(sin(dot(uv.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution;

    // Chromatic aberration offsets
    vec2 offset = vec2(0.005 * sin(u_time), 0.005 * cos(u_time));
    vec4 colR = texture(screenTexture, uv + offset.x);
    vec4 colG = texture(screenTexture, uv);
    vec4 colB = texture(screenTexture, uv - offset.x);

    // Combine RGB with chromatic aberration
    vec4 color = vec4(colR.r, colG.g, colB.b, 1.0);

    // Add scanlines
    float scanline = sin(uv.y * u_resolution.y * 0.5 + u_time * 10.0) * 0.1;
    color.rgb += scanline;

    // Random pixel displacement
    vec2 noise = vec2(random(uv + u_time), random(uv - u_time)) * 0.005;
    color.rgb += texture(screenTexture, uv + noise).rgb * 0.1;

    // Final output
    fragColor = color;
}
