(
SynthDef("ripple", {
	arg freq_l = 10, freq_r = 10, amp = 0.5;
	var out;
	out = SinOsc.ar([freq_l, freq_r]);
	Out.ar(0, out * amp);
}).store;

SynthDef("noise", {
	arg freq = 10, rq = 0.1, delay = 0.3, amp = 0.5;
	var noise1 = RLPF.ar(LFNoise0.ar([400, 410], 1),freq, rq);
	var noise2 = RLPF.ar(LFNoise1.ar([400, 410], 1),freq * 1.5, rq);
	var in = noise1 + noise2;
	//var out = Limiter.ar(CombN.ar(in, delay, delay, 4.0));
	var out = Limiter.ar(in, 2.0);
	Out.ar(0, out * amp);
}).store;

SynthDef("harmony", {
	arg base=20, lpf=100, rq=1.7, detune=0.0, allAmp = 2.0;
	var harm, ratio, s1, s2, s3, s4, s5, s6, s7, s8, w, mod, pul, out, amp;
	ratio = 1.5;
	harm = 1.5;
	amp = 0.2;
	
	s1 = Saw.ar([base+detune.rand, base+detune.rand],3.14.rand)*amp
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand],3.14.rand)*amp;
	s2 = Saw.ar([base+detune.rand, base+detune.rand]*ratio,3.14.rand)*(amp/2.0)
	+Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*ratio,3.14.rand)*(amp/2.0);
	s3 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**2),3.14.rand)*(amp/4.0)
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**2),3.14.rand)*(amp/4.0);
	s4 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**3),3.14.rand)*amp/8.0
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**3),3.14.rand)*amp/8.0;
	s5 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**4),3.14.rand)*amp/16.0
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**4),3.14.rand)*amp/16.0;
	s6 = Saw.ar([base+detune.rand, base+detune.rand]*(ratio**5),3.14.rand)*amp/16
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand]*(ratio**5),3.14.rand)*amp/16;
	
	out = RLPF.ar(s1+s2+s3+s4+s5+s6, lpf, rq);
	//2.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.03,0.2), 2) });
	//out = PanAz.ar(8, out.at(0), LFSaw.kr(5.0)) + PanAz.ar(8, out.at(1), LFSaw.kr(6.0));
	//out = out * Decay2.ar(pul, 0.01, 0.3);
	out = out * EnvGen.kr(Env.new([0,1], [3], 'sine'));
	32.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 4.0) });
	out = CompanderD.ar(out);
	Out.ar(0, out * allAmp);
	
}).store;
)

/*
SynthDef("harmony", {
	arg lpf=100, rq=0.4, amp = 1.0, detune=0.5;
	var mix;
	mix = Mix.fill(30, {arg i;
		var out;
		out = Saw.ar([17+detune, 17-detune] * (1.5 * (i+1)));
		out;

	});
	mix = mix * EnvGen.kr(Env.new([0,1], [10], 'sine'));
	mix = RLPF.ar(mix, lpf, rq);
	mix = GVerb.ar(mix, 100, 1, drylevel:0.5);
	Out.ar(0, Limiter.ar(mix) * amp);
}).store;


SynthDef("harmony", {
        arg lpf=100, rq=0.4, amp = 1.0, detune=0.5;
        var mix;
        mix = Mix.fill(12, {arg i;
                var base=10, amp=1.0;
                var harm, ratio, s1, s2, s3, s4, s5, s6, s7, s8, w, mod, pul, out, part;
                ratio = 2;
                harm = 1.5;
                //detune = 0.1;
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
*/
)

