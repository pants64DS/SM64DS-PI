#pragma once

#include "Math/MathCommon.h"
#include "Math/FixedPoint.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Math/Quaternion.h"

inline bool IsBetween (u8 x, u8 x1, u8 x2) { return x1 <= x && x < x2; } // alternative implemantation: (u8)(x - x1) < (x2 - x1)
inline bool NotBetween(u8 x, u8 x1, u8 x2) { return x < x1 || x2 < x; }  // alternative implemantation: (u8)(x - x1) > (x2 - x1)

template <typename T>
[[gnu::always_inline]] inline T Abs(T val)
{
	return val >= 0 ? val : -val;
}

consteval s32 operator""_deg(long double val) { return val * 32768.L / 180.L; }
consteval s32 operator""_deg(u64 val) { return operator""_deg(static_cast<long double>(val)); }

consteval s32 operator""_rad(long double val) { return val * 32768.L / 3.141592653589793238462643383279502884L; }
consteval s32 operator""_rad(u64 val) { return operator""_rad(static_cast<long double>(val)); }

extern "C"
{
	void UpdateAngle(s16& angle, s32 targetAngle, s32 numFrames, s16 maxStep);
	s32 ApproachAngle(s16& angle, s16 targetAngle, s32 invFactor, s32 maxDelta = 180_deg, s32 minDelta = 0); // the old LeanPlayerForwardWhileRunning
	u16 AngleDiff(s16 ang0, s16 ang1) __attribute__((const)); // from 0 to 0x8000 inclusive (0° - 180°)

	s32 RandomIntInternal(s32* randomIntStatePtr);
	u16 Color_Interp(u16* dummyArg, u16 startColor, u16 endColor, Fix12i time) __attribute__((const));

	Fix12i Math_Function_0203b14c(Fix12i& arg1, Fix12i arg2, Fix12i arg3, Fix12i arg4, Fix12i arg5);
	void Math_Function_0203b0fc(Fix12i& arg1, Fix12i arg2, Fix12i arg3, Fix12i arg4);
}

extern s32 RNG_STATE; //x => x * 0x0019660d + 0x3c6ef35f

[[gnu::always_inline]]
inline s32 RandomInt() { return RandomIntInternal(&RNG_STATE); }

[[gnu::always_inline]]
inline u32 RandomUint() { return (u32)RandomInt(); }

[[gnu::always_inline]]
inline bool RandomBit(s32 bit)
{
	return RandomInt() & (1 << bit);
}

// returns an angle from 0 to maxAng - 1, if maxAng has a single set bit
[[gnu::always_inline]]
inline s16 RandomAng(s16 maxAng)
{
	return RandomInt() & (maxAng - 1);
}

[[nodiscard]]
constexpr s32 Lerp(s32 a, s32 b, Fix12i t)
{
	return static_cast<s32>(t * (b - a)) + a;
}

[[nodiscard]]
inline Fix12i Lerp(Fix12i a, Fix12i b, Fix12i t)
{
	return t * (b - a) + a;
}

[[nodiscard]]
inline Fix12i SmoothStep(Fix12i t)
{
	return t * t * (3._f - (t << 1));
}

template<class T, T zero = static_cast<T>(0)>
constexpr s32 Sgn(T val)
{
	return (val > zero) - (val < zero);
}

[[gnu::always_inline]]
constexpr u16 Color5Bit(u8 r, u8 g, u8 b) //0x00 to 0xff each
{
	return (u16)r >> 3 << 0 |
		   (u16)g >> 3 << 5 |
		   (u16)b >> 3 << 10;
}

[[gnu::always_inline]]
constexpr u16 Arr3_5Bit(u8 val0, u8 val1, u8 val2)
{
	return (u16)val0 << 0 |
		   (u16)val1 << 5 |
		   (u16)val2 << 10;
}
