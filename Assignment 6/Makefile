CC = gcc
CFLAGS = -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter
LDLIBS = -lm -lpthread

all: srt

srt_objects = main.o raymath.o shaders.o
srt: $(srt_objects)
	$(CC) $(CFLAGS) -o $@ $(srt_objects) $(LDLIBS)

main.o raymath.o: raymath.h
main.o shaders.o: shaders.h

tests = 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm
check: baseline.ppm $(tests)
	for file in $(tests); do \
	  diff -u baseline.ppm $$file || exit; \
	done
$(tests): srt
	time ./srt $@ >$@.tmp
	mv $@.tmp $@

dist: srt.tgz
sources = COPYING Makefile main.c raymath.c raymath.h shaders.c shaders.h \
   baseline.ppm
srt.tgz: $(sources)
	tar cf - --transform='s|^|srt/|' $(sources) | gzip -9 >$@

clean:
	rm -f *.o *.tmp $(tests) srt srt.tgz
