#ifndef ASMR_MATH_H
#define ASMR_MATH_H

// TODO sq & sqrt

template<typename T>
const T& constrain(const T& Value, const T& Min, const T& Max)
{
    return (Value < Min)? Min : (Max < Value)? Max : Value;
}

template<typename T, typename L>
    auto min(const T& a, const L& b) -> decltype((b < a) ? b : a)
{
    return (b < a) ? b : a;
}

template<typename T, typename L>
    auto max(const T& a, const L& b) -> decltype((b < a) ? b : a)
{
    return (a < b) ? b : a;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// long random(long);
// long random(long, long);
// void randomSeed(unsigned long);

#endif // ASMR_MATH_H
