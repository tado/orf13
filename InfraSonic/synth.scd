(
SynthDef("ripple", {
	arg freq_l = 50, freq_r = 50;
	var out;
	out = SinOsc.ar([freq_l, freq_r]);
	Out.ar(0, out);
}).store;
)