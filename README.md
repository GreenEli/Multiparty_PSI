# PSI From Lightweight OPRF
This is the implementation of our paper **Private Set Intersection in the Internet Setting From Lightweight Oblivious PRF** published in CRYPTO 2020 [[eprint](https://eprint.iacr.org/2020/729.pdf)].

## Installation
The implementation has been tested on Linux. To download the code and compile, run the following commands. It will also download and compile the libraries of [`libOTe`](https://github.com/osu-crypto/libOTe), [`Boost`](https://sourceforge.net/projects/boost/), and [`Miracl`](https://github.com/miracl/MIRACL).
```
$ git clone --recursive https://github.com/peihanmiao/OPRF-PSI.git
$ cd OPRF-PSI
$ bash compile
```

## Running the Code
### Parameters:
```
-r 0/1   to run a sender/receiver.
-ss      log of the set size on sender side.
-rs      log of the set size on receiver side.
-w       width of the matrix.
-h       log of the height of the matrix.
-hash    hash output length in bytes.
-ip      ip address (and port).
```
### Examples:
```
$ ./bin/PSI_test -r 0 -ss 16 -rs 16 -w 609 -h 16 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 609 -h 16 -hash 9 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 16 -rs 16 -w 408 -h 16 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 408 -h 16 -hash 9 -ip 127.0.0.1

$ ./bin/PSI_test -r 0 -ss 16 -rs 16 -w 400 -h 16 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 400 -h 16 -hash 9 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 18 -rs 18 -w 412 -h 18 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 18 -rs 18 -w 412 -h 18 -hash 10 -ip 127.0.0.1


$ ./bin/PSI_test -r 0 -ss 20 -rs 20 -w 621 -h 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 621 -h 20 -hash 10 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 416 -h 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 416 -h 20 -hash 10 -ip 127.0.0.1

<!-- $ ./bin/PSI_test -r 0 -ss 22 -rs 22 -w 400 -h 16 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 400 -h 16 -hash 9 -ip 127.0.0.1 -->
./bin/PSI_test -r 0 -ss 22 -rs 22 -w 420 -h 22 -hash 11 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 22 -rs 22 -w 420 -h 22 -hash 11 -ip 127.0.0.1


$ ./bin/PSI_test -r 0 -ss 20 -rs 20 -w 621 -h 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 621 -h 20 -hash 10 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 24 -rs 24 -w 424 -h 24 -hash 11 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 24 -rs 24 -w 424 -h 24 -hash 11 -ip 127.0.0.1
```
./bin/PSI_test -r 0 -ss 18 -rs 18 -w 615 -h 18 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 18 -rs 18 -w 615 -h 18 -hash 10 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 18 -rs 18 -w 412 -h 18 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 18 -rs 18 -w 412 -h 18 -hash 10 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 18 -rs 18 -w 615 -h 17 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 18 -rs 18 -w 615 -h 17 -hash 10 -ip 127.0.0.1

------------------------------------------------------My Experiment-------------------------------------------------------------
test ./bin/PSI_test -r 0 -ss 12 -rs 12 -w 136 -h 10 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 136 -h 10 -hash 8 -ip 127.0.0.1
------------------------------------------------------------Semi-Honest---------------------------------------------------------------------------------
n=4 ./bin/PSI_test -r 0 -ss 12 -rs 12 -w 623 -h 11 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 623 -h 11 -hash 8 -ip 127.0.0.1
n=10 ./bin/PSI_test -r 0 -ss 12 -rs 12 -w 260 -h 11 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 260 -h 11 -hash 8 -ip 127.0.0.1
n=15 ./bin/PSI_test -r 0 -ss 12 -rs 12 -w 198 -h 11 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 198 -h 11 -hash 8 -ip 127.0.0.1

n=4 ./bin/PSI_test -r 0 -ss 16 -rs 16 -w 636 -h 15 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 636 -h 15 -hash 9 -ip 127.0.0.1
n=10 ./bin/PSI_test -r 0 -ss 16 -rs 16 -w 264 -h 15 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 264 -h 15 -hash 9 -ip 127.0.0.1
n=15 ./bin/PSI_test -r 0 -ss 16 -rs 16 -w 201 -h 15 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 201 -h 15 -hash 9 -ip 127.0.0.1

n=4 ./bin/PSI_test -r 0 -ss 20 -rs 20 -w 649 -h 19 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 649 -h 19 -hash 10 -ip 127.0.0.1
n=10 ./bin/PSI_test -r 0 -ss 20 -rs 20 -w 268 -h 19 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 268 -h 19 -hash 10 -ip 127.0.0.1
n=15 ./bin/PSI_test -r 0 -ss 20 -rs 20 -w 204 -h 19 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 204 -h 19 -hash 10 -ip 127.0.0.1

n=4 ./bin/PSI_test -r 0 -ss 24 -rs 24 -w 662 -h 23 -hash 11 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 24 -rs 24 -w 662 -h 23 -hash 11 -ip 127.0.0.1
n=10 ./bin/PSI_test -r 0 -ss 24 -rs 24 -w 272 -h 23 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 24 -w 272 -h 23 -hash 10 -ip 127.0.0.1
n=15 ./bin/PSI_test -r 0 -ss 24 -rs 24 -w 207 -h 23 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 24 -w 207 -h 23 -hash 10 -ip 127.0.0.1
------------------------------------------------------------------------Malicious----------------------------------------------------------------------

./bin/PSI_test -r 0 -ss 12 -rs 12 -w 111 -w1 597 -h 10 -h1 12 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 111 -w1 597 -h 10 -h1 12 -hash 8 -ip 127.0.0.1

n=(4,1) 
./bin/PSI_test -r 0 -ss 12 -rs 12 -w 104 -w1 597 -h 12 -h1 12 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 104 -w1 597 -h 12 -h1 12 -hash 8 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 16 -rs 16 -w 111 -w1 609 -h 16 -h1 16 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 111 -w1 609 -h 16 -h1 16 -hash 9 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 119 -w1 621 -h 20 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 119 -w1 621 -h 20 -h1 20 -hash 10 -ip 127.0.0.1

n=(4,3) 
---

n=(10,1) 
./bin/PSI_test -r 0 -ss 12 -rs 12 -w 107 -w1 597 -h 11 -h1 12 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 107 -w1 597 -h 11 -h1 12 -hash 8 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 16 -rs 16 -w 107 -w1 609 -h 15 -h1 16 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 107 -w1 609 -h 15 -h1 16 -hash 9 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 107 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 107 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1

n=(10,4) 
...

n=(10,9) 
...

n=(15,1) 
./bin/PSI_test -r 0 -ss 12 -rs 12 -w 107 -w1 597 -h 11 -h1 12 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 107 -w1 597 -h 11 -h1 12 -hash 8 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 16 -rs 16 -w 107 -w1 609 -h 15 -h1 16 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 107 -w1 609 -h 15 -h1 16 -hash 9 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 107 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 107 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1

n=(15,4) 
...
n=(15,7) 
...
n=(15,14) 
...

n=(20,1) 
./bin/PSI_test -r 0 -ss 12 -rs 12 -w 107 -w1 597 -h 11 -h1 12 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 107 -w1 597 -h 11 -h1 12 -hash 8 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 16 -rs 16 -w 107 -w1 609 -h 15 -h1 16 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 107 -w1 609 -h 15 -h1 16 -hash 9 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 107 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 107 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1
...
n=(30,1) 
./bin/PSI_test -r 0 -ss 12 -rs 12 -w 107 -w1 597 -h 11 -h1 12 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 107 -w1 597 -h 11 -h1 12 -hash 8 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 16 -rs 16 -w 107 -w1 609 -h 15 -h1 16 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 107 -w1 609 -h 15 -h1 16 -hash 9 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 107 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 107 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1
...
n=(50,1) 
./bin/PSI_test -r 0 -ss 12 -rs 12 -w 107 -w1 597 -h 11 -h1 12 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 107 -w1 597 -h 11 -h1 12 -hash 8 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 16 -rs 16 -w 107 -w1 609 -h 15 -h1 16 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 107 -w1 609 -h 15 -h1 16 -hash 9 -ip 127.0.0.1
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 107 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 107 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1
...

Big Size 2^{24} (3,1)
./bin/PSI_test -r 0 -ss 24 -rs 24 -w 226 -w1 633 -h 24 -h1 24 -hash 11 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 24 -rs 24 -w 226 -w1 633 -h 24 -h1 24 -hash 11 -ip 127.0.0.1
...
Big Size 2^{24} (4,1)
./bin/PSI_test -r 0 -ss 24 -rs 24 -w 127 -w1 633 -h 24 -h1 24 -hash 11 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 24 -rs 24 -w 127 -w1 633 -h 24 -h1 24 -hash 11 -ip 127.0.0.1

Banlance (n=3)
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 211 -w1 621 -h 20 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 211 -w1 621 -h 20 -h1 20 -hash 10 -ip 127.0.0.1


free--n=(10,1)--free 
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 101 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 101 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1

free--n=(15,1)--free 
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 80 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 80 -w1 621 -h 19 -h1 20 -hash 10 -ip 127.0.0.1

free--n=(50,1)--free 
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 122 -w1 621 -h 18 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 122 -w1 621 -h 18 -h1 20 -hash 10 -ip 127.0.0.1

free--n=(100,1)--free 
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 80 -w1 621 -h 18 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 80 -w1 621 -h 18 -h1 20 -hash 10 -ip 127.0.0.1

## Help
For any questions on building or running the library, please contact [`Peihan Miao`](https://sites.google.com/view/peihanmiao) at peihan at berkeley dot edu
./bin/PSI_test -r 0 -ss 12 -rs 12 -w 271 -w1 597  -h 12 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 271 -w1 597  -h 12 -hash 8 -ip 127.0.0.1

./bin/PSI_test -r 0 -ss 16 -rs 16 -w 280 -w1 609  -h 16 -hash 9 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 16 -rs 16 -w 280 -w1 609  -h 16 -hash 9 -ip 127.0.0.1

./bin/PSI_test -r 0 -ss 20 -rs 20 -w 289 -w1 621  -h 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 289 -w1 621  -h 20 -hash 10 -ip 127.0.0.1

./bin/PSI_test -r 0 -ss 24 -rs 24 -w 298 -w1 633  -h 24 -hash 11 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 24 -rs 24 -w 298 -w1 633  -h 24 -hash 11 -ip 127.0.0.1


------------------------------
./bin/PSI_test -r 0 -ss 12 -rs 12 -w 111 -w1 597  -h 10 -hash 8 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 12 -rs 12 -w 111 -w1 597  -h 10 -hash 8 -ip 127.0.0.1 Experiment output 138; Theory output about 136+13

free--n=(50,1)--free 
./bin/PSI_test -r 0 -ss 20 -rs 20 -w 122 -w1 621 -h 18 -h1 20 -hash 10 -ip 127.0.0.1 & ./bin/PSI_test -r 1 -ss 20 -rs 20 -w 122 -w1 621 -h 18 -h1 20 -hash 10 -ip 127.0.0.1
output 146; Theory output about 100+34+11
