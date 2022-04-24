# K4SIDH
A 4 way SIMD Implementation of SIDH Compatible Isogeny Evaluations on Kummer Surfaces

In 2018, Costello [[1]](#1) proposed a method that allows simpler computations for the work done in SIDH. Instead of performing the arithmetic on the supersingular Montgomery curve, it computes a set of supersingular Kummer surface parameters from the corresponding Montgomery curve and does the computations of key pairs on that Kummer surface. This mapping reveals the path for a 4 way parallel SIMD implementation of SIDH thanks to the structure of Kummer surfaces.

K4SIDH forms the isogeny evaluations part of Alice’s side of SIDH key exchange. The application computes a chain of Richelot isogenies [[2]](#2) on Kummer surfaces. In K4SIDH, Alice’s 4-isogenies are replaced with (2,2) isogenies and Kummer surface arithmetic is used. Usage of Kummer surfaces leads to the introduction of 4 way AVX2 SIMD instruction set in arithmetic functions such as field multiplication, field squaring, modular reduction and Hadamard operation.

The source code can be compiled and run with:

```
gcc -m64 -mavx2 -Wall -O3 main.c kummer_isogeny.c -o K4SIDH.out && ./K4SIDH.out
```

Note that Python3 must be installed in order to run the validation test on Online Magma (http://magma.maths.usyd.edu.au/calc/). 

For detailed information, please refer to K4SIDH.pdf.


## References
<a id="1">[1]</a> 
Costello, C. (2018). 
Computing Supersingular Isogenies on Kummer Surfaces
In Advances in Cryptology – ASIACRYPT 2018, 428–456. Springer International Publishing.

<a id="2">[2]</a> 
Richelot F. (1836) 
Essai sur une methode generale pour determiner la valuer des integrales ultra-elliptiques, fondee sur des transformations remarquables des ce transcendantes. 
CR Acad. Sc. Paris, 2:622–627, 1836.
