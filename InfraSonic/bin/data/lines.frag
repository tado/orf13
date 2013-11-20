#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float level;
uniform int num;


float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.545354678);
}

void main(){
    vec4 col = vec4(0, 0, 0, 1);
    vec3 vsum = vec3(0.0);
    for ( int i = 1; i < num; i++ ){
        vec3 v = vec3(0.0, 0.0, 0.0);
        float rdm = rand(vec2(float(i) + 1.0, float(i))) * 0.2 - 0.1;
        float c = (sin(gl_FragCoord.y * float(i) * rdm + time) - 0.996) * 30.0;
        if (c <= 0.0) {
            c = 0.0;
        }
        c *= 2.0;
        vsum += vec3(c, c, c);
    }
    gl_FragColor = vec4(vsum, 1.0);
}