(
SynthDef("ripple", {
	arg freq_l = 50, freq_r = 50;
	var out;
	out = SinOsc.ar([freq_l, freq_r]);
	Out.ar(0, out);
}).store;

SynthDef("noise", {
	arg freq = 100, rq = 0.1, delay = 1.0;
	var noise1 = RLPF.ar(LFNoise1.ar([8000,8100], 1),freq, rq);
	var noise2 = RLPF.ar(LFNoise2.ar([8000,8100], 1),freq * 1.5, rq);
	var in = noise1 + noise2;
	//var out = Limiter.ar(CombN.ar(in, delay, delay, 4));
	var out = in;
	Out.ar(0, out);
}).store;
)

