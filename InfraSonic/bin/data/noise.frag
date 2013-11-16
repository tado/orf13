#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float freq;
uniform float rq;
uniform float amp;

float  tri( float x ){
    return (abs(fract(x)-0.5)-0.25);
}
vec3 tri( vec3 p ){
    return vec3( tri(p.x), tri(p.y), tri(p.z) );
}

#define N 30
#define PI2 (3.14159265*2.0)
void main( void ) {
    vec3 v = vec3( (gl_FragCoord.xy - resolution/2.0) / min(resolution.y,resolution.x) * 1.5, 0.0);
    v.z = time * 10.0;
    
    float mx = sin(1.32 + time * 0.0037312) * 1.45 + 0.5;
    float my = cos(1.01 + time * 0.0023312) * 1.45 + 0.5;
    
    float c1 = cos(my * PI2);
    float s1 = sin(my * PI2);
    float c2 = cos(mx * PI2);
    float s2 = sin(mx * PI2);
    float c3 = cos(freq / 1000.0 * PI2);
    float s3 = sin(freq / 1000.0 * PI2);
    vec3 vsum = vec3(0.0);
    for ( int i = 0; i < N; i++ ){
        float f = float(i) / float(N);
        
        v *= 1.0 + 0.1/(f*f+0.45);
        v += (rq-.5)*2.0;
        v = vec3( v.x*c1-v.y*s1, v.y*c1+v.x*s1, v.z ); // rotate
        v = vec3( v.x, v.y*c2-v.z*s2, v.z*c2+v.y*s2 ); // rotate
        v = vec3( v.x*c3-v.z*s3, v.y, v.z*c3+v.x*s3 ); // rotate
        v = tri( v ); // fold
        vsum += v;
        vsum *= 0.9;
        
    }
    v = vsum *.3;
    gl_FragColor = vec4( sin(v * PI2 * 4.0)*.5+.5, amp);
    
}