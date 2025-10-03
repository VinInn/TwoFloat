#pragma once

#include<limits>
namespace std {
template <>
class numeric_limits<TwoFloat<float>> {
 using FF = TwoFloat<float>;
 public:

    // General -- meaningful for all specializations.

    static const bool is_specialized = true;
    static FF min ()
        {return FF(0,1,0);}
    static FF max ()
        {return FF(~0,FF::MAX_EXPONENT_VALUE-1,0);}
    static const int radix = 2;
    static const int digits = 10;   // conservative assumption
    static const int digits10 = 2;  // conservative assumption
    static const bool is_signed        = true;
    static const bool is_integer    = true;
    static const bool is_exact        = false;
    static const bool traps            = false;
    static const bool is_modulo        = false;
    static const bool is_bounded    = true;

    // Floating point specific.

    static FF epsilon ()
        {return FF(0.00097656f);} // from OpenEXR, needs to be confirmed
    static FF round_error ()
        {return FF(0.00097656f/2);}
    static const int min_exponent10 = FF::MIN_EXPONENT10;
    static const int max_exponent10 = FF::MAX_EXPONENT10;
    static const int min_exponent   = FF::MIN_EXPONENT;
    static const int max_exponent   = FF::MAX_EXPONENT;

    static const bool has_infinity            = true;
    static const bool has_quiet_NaN            = true;
    static const bool has_signaling_NaN        = true;
    static const bool is_iec559                = false;
    static const bool has_denorm            = denorm_present;
    static const bool tinyness_before        = false;
    static const float_round_style round_style = round_to_nearest;

    static FF denorm_min ()
        {return FF(1,0,1);}
    static FF infinity ()
        {return FF(0,FF::MAX_EXPONENT_VALUE,0);}
    static FF quiet_NaN ()
        {return FF(1,FF::MAX_EXPONENT_VALUE,0);}
    static FF signaling_NaN ()
        {return FF(1,FF::MAX_EXPONENT_VALUE,0);}
 };
} // end namespace std

