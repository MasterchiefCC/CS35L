1. Unmodified Version
time ./srt 1-test.ppm >1-test.ppm.tmp
real    0m44.433s
user    0m44.400s
sys     0m0.000s

2. Modified version
time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m42.443s
user    0m42.400s
sys     0m0.000s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m21.640s
user    0m43.044s
sys     0m0.003s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m11.212s
user    0m44.288s
sys     0m0.017s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m5.765s
user    0m44.709s
sys     0m0.003s

Beacuse the multithreading ,the real time is decreasing as the threads increase.
However, the user time is increasing as the threads increase, beacause it is the cost of mutithreading.
To create is going to increase the time.
The eight-thread version is much faster than single-thread version, beacause paralleism.
