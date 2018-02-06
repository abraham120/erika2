# This makefile let you choose if you want to compile the example as a
# typical source distribution or as a binary distribution

# to do that, you have to specify TYPE=b or TYPE=s

all:
	rm -rf out_source
	mkdir -p out_source
	make -C ../../../dist/source DIST=E7T_ALL E7T_MOVE=Y
	cd out_source; cp ../base/*.* .
	cd out_source; ./lancia.bat; cd Debug; make

# these two examples has not been ported yet
#	rm -rf out_binaryfull
#	mkdir -p out_binaryfull
#	cd out_binaryfull; cp -sf ../*.* .
# 	cd out_binaryfull; cp -sf ../binary_full/* . ||:
# 	make -C ../../../dist/binary DISTFILE=$(shell pwd)/binary_full/conf.mk DIST=BINARY_OO1
# 	mv ../../../dist/binary/ee_BINARY_OO1 out_binaryfull
# 	make -C out_binaryfull EEBASE=ee_BINARY_OO1

# 	rm -rf out_binarylimited
# 	mkdir -p out_binarylimited
# 	cd out_binarylimited; cp -sf ../*.* .
# 	cd out_binarylimited; cp -sf ../binary_limited/* . ||:
# 	make -C ../../../dist/binary DISTFILE=$(shell pwd)/binary_limited/conf.mk DIST=BINARY_OO1
# 	mv ../../../dist/binary/ee_BINARY_OO1 out_binarylimited
# 	make -C out_binarylimited EEBASE=ee_BINARY_OO1

clean:
	rm -rf out*
