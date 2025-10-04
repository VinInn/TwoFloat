#pragma once

#include<limits>
namespace std {

// conservative assumptions: DW ment for increased precision not increased range
template <>
class numeric_limits <TwoFloat<float>> {
 using F = float;
 using FF = TwoFloat<F>;
 using nlF = numeric_limits<F>;
 public:

    // General -- meaningful for all specializations.

    static const bool is_specialized = true;
    static FF min ()
        {return nlF::min();}
    static FF max ()
        {return nlF::max();}
    static const int radix = 2;
    static const int digits = nlF::digits;   
    static const int digits10 = nlF::digits10;
    static const int max_digits10 = nlF::max_digits10;
    static const bool is_signed        = true;
    static const bool is_integer    = false;
    static const bool is_exact        = false;
    static const bool traps            = false;
    static const bool is_modulo        = false;
    static const bool is_bounded    = true;

    // Floating point specific.

    static FF epsilon ()
        {return nlF::epsilon();} 
    static FF round_error ()
        {return nlF::round_error();}
    static const int min_exponent10 = nlF::min_exponent10;
    static const int max_exponent10 = nlF::max_exponent10;
    static const int min_exponent   = nlF::min_exponent;
    static const int max_exponent   = nlF::max_exponent;

    static const bool has_infinity            = true;
    static const bool has_quiet_NaN            = true;
    static const bool has_signaling_NaN        = true;
    static const bool is_iec559                = false;
    static const bool has_denorm            = denorm_present;
    static const bool tinyness_before        = false;
    static const float_round_style round_style = round_to_nearest;

    static FF denorm_min ()
        {return nlF::denorm_min();}
    static FF infinity ()
        {return nlF::infinity();}
    static FF quiet_NaN ()
        {return  nlF::quiet_NaN();}
    static FF signaling_NaN ()
        {return nlF::signaling_NaN();}
 };


template <>
class numeric_limits <TwoFloat<double>> {
 using F = double;
 using FF = TwoFloat<F>;
 using nlF = numeric_limits<F>;
 public:

    // General -- meaningful for all specializations.

    static const bool is_specialized = true;
    static FF min ()
        {return nlF::min();}
    static FF max ()
        {return nlF::max();}
   static const int radix = 2;
    static const int digits = nlF::digits;
    static const int digits10 = nlF::digits10;
    static const int max_digits10 = nlF::max_digits10;
    static const bool is_signed        = true;
    static const bool is_integer    = false;
    static const bool is_exact        = false;
    static const bool traps            = false;
    static const bool is_modulo        = false;
    static const bool is_bounded    = true;

    // Floating point specific.

    static FF epsilon ()
        {return nlF::epsilon();}
    static FF round_error ()
        {return nlF::round_error();}
    static const int min_exponent10 = nlF::min_exponent10;
    static const int max_exponent10 = nlF::max_exponent10;
    static const int min_exponent   = nlF::min_exponent;
    static const int max_exponent   = nlF::max_exponent;

    static const bool has_infinity            = true;
    static const bool has_quiet_NaN            = true;
    static const bool has_signaling_NaN        = true;
    static const bool is_iec559                = false;
    static const bool has_denorm            = denorm_present;
    static const bool tinyness_before        = false;
    static const float_round_style round_style = round_to_nearest;

    static FF denorm_min ()
        {return nlF::denorm_min();}
    static FF infinity ()
        {return nlF::infinity();}
    static FF quiet_NaN ()
        {return  nlF::quiet_NaN();}
    static FF signaling_NaN ()
        {return nlF::signaling_NaN();}
 };

} // end namespace std

