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

### Usage

The TwoFloat class is designed to be a seamless drop-in replacement for float-types in any code, included templated libraries such as Eigen.

Implicit conversions to and from the single-word type (the template argument) are supported.
That will also allow the implicit promotion to double following the C++ language rule often producing not the result the coder expected.

Implicit promotion to double can be easily detected using compiler option *"-Wdouble-promotion"*.

Conversion can be forced to be explicit defining the macro *"TWOFLOAT_EXPLICIT"*

### Choice of algorithms

By default Sum is implemented using Algo 5 from Ref 1 (aka SloppySum), Multiplication by Algo 11 and Division by Algo 17.

More precise algoritms can be selected by defining macro "*TWOFLOAT_PRECISE_SUM*" (Algo 6 for Sum), "*TWOFLOAT_PRECISE_MUL*" (Algo 12 for Multiplication) and
"*TWOFLOAT_PRECISE_Div*" (Algo 18 for Division)

Please refer to table 1 in Ref 1 for details about precision and "latency" of the algorithms.

### Degubbing aids
Sometimes the results are not those expected, in particular when using TwoFloat in an external software package. This is usually due to implicit assumptions that the type is a C++ floating point (with a IEEE754 format). Missing speciazations are of course a major issue. 

Compiling with *"-DTWOFLOAT_EXPLICIT"* and *"-Wdouble-promotion"* should already help in detecting all cases of conversions and promotions some of which maybe problematic.

TWoFloat declare also two functions: void "*trapTwoFloat(float h, float l)*" and similar for double that are called by all contructors and assign operators if the macro "*TWOFLOAT_TRAP*" is defined. The functions can be defined in the user application to detect problematic occurrencies (such as NaN) and used to set a brackpoint in gdb to identify thier origin.
