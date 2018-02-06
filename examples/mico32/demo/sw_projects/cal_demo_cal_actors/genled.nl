network genled() ==> :
var
	int dynamicSZ := 8;
entities
	gen0 = gen(dynamicSZ = dynamicSZ);
	led0 = art_led(dynamicSZ = dynamicSZ);
structure
	gen0.outp --> led0.inp {bufferSize = 1;};
end
