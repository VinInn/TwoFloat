# TwoFloat
An implementation of DoubleWord Arithmetic as a simple C++ templated class.

It implements algorithms from

1. Mioara Maria Joldes, Jean-Michel Muller, Valentina Popescu. |
Tight and rigorous error bounds for basic building blocks of double-word arithmetic."
ACM Transactions on Mathematical Software, 2017, 44 (2), pp.1 - 27. .10.1145/3121432.. https://hal.science/hal-01351529v3

2. Vincent Lefèvre, Nicolas Louvet, Jean-Michel Muller, Joris Picot, Laurence Rideau. 
"Accurate Calculation of Euclidean Norms using Double-Word Arithmetic."
ACM Transactions on Mathematical Software, 2023, 49.  https://hal.science/hal-03482567

3. S. M. Rump and M. Lange. 
"Faithfully Rounded Floating-Point Computation."
ACM Transactions on Mathematical Software, 46(3):1–20, jul 2020. https://www.tuhh.de/ti3/paper/rump/LaRu2017b.pdf


The code is contained in just one file *TwoFloat.h*.
The file consists in four sections:
1. Basic Block of DoubleWord Arithmetic imported from a previous project in C.
2. The TwoFloat class itself
3. A set of operators implementing the 4 arithmetic operations and comparisons
4. A small set of elementary functions plus some utilities

## Usage

The TwoFloat class is designed to be a seamless drop-in replacement for float-types in any code included templated libraries such as Eigen.

Implicit conversions to and from the single-word type (the template argument) are supported.
That will also allow the implicit promotion to double following the C++ language rule often producing not the result the coder expected.

Implicit promotion to double can be easily detected using compiler option *"-Wdouble-promotion"*.

Conversion can be forced to be explicit defining the macro *"TWOFLOAT_EXPLICIT"*

