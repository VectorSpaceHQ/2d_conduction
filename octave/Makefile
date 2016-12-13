all: conduction.gif

conduction.gif: conduction.m
	convert -delay 5 -resize 480x360 -colors 32 -loop 0 output/*png output/conduction.gif

conduction.m: output_dir
	octave-cli conduction.m

.PHONY: output_dir
output_dir:
	mkdir -p output

.PHONY: clean
clean:
	rm -rf output
