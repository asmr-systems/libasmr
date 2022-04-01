#ifndef ASMR_COMMON_H
#define ASMR_COMMON_H

//:::: Pin Types
//::::::::::::::
enum class PinStatus {
    Low  = 0,
    High = 1,
};

using Pin = int;

//:::: Ports
//::::::::::
enum class Port {
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4,
    F = 5,
    G = 6,
    H = 7,
    I = 8
};

//:::: Mathematical Constants
//:::::::::::::::::::::::::::
constexpr double Pi     = 3.1415926535897932384626433832795;
constexpr double HalfPi = 1.5707963267948966192313216916398;
constexpr double TwoPi  = 6.283185307179586476925286766559;

#include <math.h>

#endif
