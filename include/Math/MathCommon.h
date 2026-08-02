#pragma once

#include <cstdint>

using s8  = int8_t;
using u8  = uint8_t;
using s16 = short;
using u16 = uint16_t;
using s32 = int;
using u32 = unsigned;
using s64 = int64_t;
using u64 = uint64_t;

// returns whether the counter reached its destination
bool ApproachLinear(s16& counter, s16 dest, s16 step);
bool ApproachLinear(s32& counter, s32 dest, s32 step);
bool ApproachLinear2(s16& counter, s16 dest, s16 step);
bool ApproachLinear2(s32& counter, s32 dest, s32 step);

u16 CountDownToZero(u16& counter); // returns the counter's new value
u8  CountDownToZero(u8&  counter); // returns the counter's new value

s32 SoftwareDiv(s32 numerator, s32 denominator);
u32 SoftwareDiv(u32 numerator, u32 denominator);
s64 SoftwareDiv(s64 numerator, s64 denominator);
u64 SoftwareDiv(u64 numerator, u64 denominator);
u64 SoftwareMod(u64 numerator, u64 denominator);
s32 HardwareDiv(s32 numerator, s32 denominator);
s32 HardwareMod(s32 numerator, s32 denominator);

void HardwareDivAsync(s32 numerator, s32 denominator);
s64 HardwareDivResultQ32();
s64 HardwareDivQ32(s32 numerator, s32 denominator); // returns a Q32 number

u32 Sqrt(u64 x); // 64 bit unsigned sqrt

template<class T> [[nodiscard, gnu::always_inline]]
constexpr T Sqr(T val) { return val * val; }
