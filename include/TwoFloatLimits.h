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

    static constexpr  bool is_specialized = true;
    static FF min()
        {return nlF::min();}
    static FF max()
        {return nlF::max();}
    static constexpr  int radix = 2;
    static constexpr  int digits = nlF::digits;   
    static constexpr  int digits10 = nlF::digits10;
    static constexpr  int max_digits10 = nlF::max_digits10;
    static constexpr  bool is_signed       = true;
    static constexpr  bool is_integer      = false;
    static constexpr  bool is_exact        = false;
    static constexpr  bool traps           = false;
    static constexpr  bool is_modulo       = false;
    static constexpr  bool is_bounded      = true;

    // Floating point specific.

    static constexpr  int min_exponent10 = nlF::min_exponent10;
    static constexpr  int max_exponent10 = nlF::max_exponent10;
    static constexpr  int min_exponent   = nlF::min_exponent;
    static constexpr  int max_exponent   = nlF::max_exponent;

    static constexpr  bool has_infinity             = true;
    static constexpr  bool has_quiet_NaN            = true;
    static constexpr  bool has_signaling_NaN        = true;
    static constexpr  bool is_iec559                = false;
    static constexpr  bool has_denorm               = denorm_present;
    static constexpr  bool tinyness_before          = false;
    static constexpr  float_round_style round_style = round_to_nearest;

    static constexpr FF epsilon()
        {return nlF::epsilon();}
    static constexpr FF round_error()
        {return nlF::round_error();}
    static constexpr FF denorm_min()
        {return nlF::denorm_min();}
    static constexpr FF infinity()
        {return nlF::infinity();}
    static constexpr FF quiet_NaN()
        {return  nlF::quiet_NaN();}
    static constexpr FF signaling_NaN()
        {return nlF::signaling_NaN();}
 };


template <>
class numeric_limits <TwoFloat<double>> {
 using F = double;
 using FF = TwoFloat<F>;
 using nlF = numeric_limits<F>;
 public:

    // General -- meaningful for all specializations.

    static constexpr  bool is_specialized = true;
    static constexpr FF min()
        {return nlF::min();}
    static constexpr FF lowest()
        {return nlF::lowest();}
    static constexpr FF max()
        {return nlF::max();}
    static constexpr  int radix = 2;
    static constexpr  int digits = nlF::digits;
    static constexpr  int digits10 = nlF::digits10;
    static constexpr  int max_digits10 = nlF::max_digits10;
    static constexpr  bool is_signed        = true;
    static constexpr  bool is_integer       = false;
    static constexpr  bool is_exact         = false;
    static constexpr  bool traps            = false;
    static constexpr  bool is_modulo        = false;
    static constexpr  bool is_bounded       = true;

    // Floating point specific.

    static constexpr  int min_exponent10 = nlF::min_exponent10;
    static constexpr  int max_exponent10 = nlF::max_exponent10;
    static constexpr  int min_exponent   = nlF::min_exponent;
    static constexpr  int max_exponent   = nlF::max_exponent;

    static constexpr  bool has_infinity             = true;
    static constexpr  bool has_quiet_NaN            = true;
    static constexpr  bool has_signaling_NaN        = true;
    static constexpr  bool is_iec559                = false;
    static constexpr  bool has_denorm               = denorm_present;
    static constexpr  bool tinyness_before          = false;
    static constexpr  float_round_style round_style = round_to_nearest;

    static constexpr FF epsilon()
        {return nlF::epsilon();}
    static constexpr FF round_error()
        {return nlF::round_error();}
    static constexpr FF denorm_min()
        {return nlF::denorm_min();}
    static constexpr FF infinity()
        {return nlF::infinity();}
    static constexpr FF quiet_NaN()
        {return  nlF::quiet_NaN();}
    static constexpr FF signaling_NaN()
        {return nlF::signaling_NaN();}
 };

} // end namespace std

