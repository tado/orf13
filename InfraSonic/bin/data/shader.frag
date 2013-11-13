#ifdef GL_ES
precision highp float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float freq_r;
uniform float freq_l;

float waveLength = 200.0;
float speed = 100.0;

void main( void ) {
    
	vec2 pos1 = vec2(0.25, 0.5)*resolution;
	vec2 lenVec1 = pos1.xy - gl_FragCoord.xy;
	float dist1 = 1.0 - length(lenVec1);
	float wave1 = (sin((dist1/waveLength) * freq_l + time*speed) + 1.0) / 2.0;
    
    vec2 pos2 = vec2(0.75, 0.5)*resolution;
	vec2 lenVec2 = pos2.xy - gl_FragCoord.xy;
	float dist2 = 1.0 - length(lenVec2);
	float wave2 = (cos((dist2/waveLength) * freq_r + time*speed) + 1.0) / 2.0;
    
    float add = (wave1 + wave2) / 2.0 ;
    gl_FragColor = vec4(add, add, add, 1.);
    
}

