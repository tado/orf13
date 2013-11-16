(
SynthDef("ripple", {
	arg freq_l = 50, freq_r = 50, amp = 0.5;
	var out;
	out = SinOsc.ar([freq_l, freq_r]);
	Out.ar(0, out * amp);
}).store;

SynthDef("noise", {
	arg freq = 100, rq = 0.1, delay = 0.3, amp = 0.5;
	var noise1 = RLPF.ar(LFNoise0.ar([400, 410], 1),freq, rq);
	var noise2 = RLPF.ar(LFNoise1.ar([400, 410], 1),freq * 1.5, rq);
	var in = noise1 + noise2;
	//var out = Limiter.ar(CombN.ar(in, delay, delay, 4.0));
	var out = Limiter.ar(in, 2.0);
	Out.ar(0, out * amp);
}).store;
)

