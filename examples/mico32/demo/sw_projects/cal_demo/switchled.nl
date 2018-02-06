network switchled() ==> :
var
	int dynamicSZ := 8;
entities
	switch0 = art_switch(dynamicSZ = dynamicSZ);
	led0 = art_led(dynamicSZ = dynamicSZ);
structure
	switch0.outp --> led0.inp {bufferSize = 1;};
end
