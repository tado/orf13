#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec3 pulseFreq;

void main( void ) {
    vec3 color = vec3(0.0, 0.0, 0.0);
    float color_l;
    float color_r;
    
    float r = sin(time * pulseFreq.r *6.283185);
    float g =  0.0;
    float b = sin(time * pulseFreq.b *6.283185);

    if(r > 0.0){color_l = 1.0;} else {color_l = 0.0;}
    if(b > 0.0){color_r = 1.0;} else {color_r = 0.0;}

    color.r = color_l;
    color.g = (color_l + color_r) * 0.5;
    color.b = color_r;

    gl_FragColor = vec4( color, 1.0 );
}