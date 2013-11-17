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

SynthDef("harmony", {
	arg lpf=100, rq=0.4, amp = 1.0;
	var mix;
	mix = Mix.fill(12, {arg i;
		var base=10, amp=1.0;
		var detune, harm, ratio, s1, s2, s3, s4, s5, s6, s7, s8, w, mod, pul, out, part;
		ratio = 2;
		harm = 1.5;
		detune = 0.1;
		pul = Impulse.ar(12.0);
		part = (i + 1) * 1.5;
		base = base * part;
		s1 = Saw.ar([base+detune.rand, base+detune.rand])*amp
		+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand])*amp;
		s2 = Saw.ar([base+detune.rand, base+detune.rand]*ratio)*(amp/2.0)
		+Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*ratio)*(amp/2.0);
		s3 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**2))*(amp/4.0)
		+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**2))*(amp/4.0);
		s4 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**3))*amp/8.0
		+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**3))*amp/8.0;
		s5 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**4))*amp/16.0
		+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**4))*amp/16.0;
		s6 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**5))*amp/16
		+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**5))*amp/16;

		out = s1+s2+s3+s4+s5+s6;
		out;
	});
	mix = mix * EnvGen.kr(Env.new([0,1], [10], 'sine'));
	mix = RLPF.ar(mix, lpf, rq);
	Out.ar(0, Limiter.ar(mix) * amp);

}).store;

)

