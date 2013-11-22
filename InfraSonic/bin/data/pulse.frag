#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec3 pulseFreq;

void main( void ) {

    vec2 position = ( gl_FragCoord.xy / resolution.xy ) + mouse / 4.0;

    vec3 color = vec3(0.0, 0.0, 0.0);
    float r = sin(time * pulseFreq.r * 4.0);
    //float g = sin(time * pulseFreq.g);
    float g =  0.0;
    float b = sin(time * pulseFreq.b * 4.0);
   
    if(r > 0.0){
        color.r = 1.0;
    }
    if(g > 0.0){
        color.g = 1.0;
    }
    if(b > 0.0){
        color.b = 1.0;
    }
    /*
    color.r = r;
    color.g = g;
    color.b = b;
     */
    gl_FragColor = vec4( color, 1.0 );

}