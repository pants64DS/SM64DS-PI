#pragma once

#include "ostream.h"
#include "MathCommon.h"
#include "FixedPoint.h"
#include "Proxy.h"
#include <utility>

struct Vector3;

extern "C"
{
	void Vec3_RotateYAndTranslate(Vector3& res, const Vector3& translation, s16 angY, const Vector3& v); //res and v cannot alias.
	bool Vec3_ApproachHorz(Vector3& pos, const Vector3& targetPos, Fix12i step);

	[[gnu::pure]] s16 Vec3_VertAngle(const Vector3& v1, const Vector3& v0);
	[[gnu::pure]] s16 Vec3_HorzAngle(const Vector3& v0, const Vector3& v1);

	Fix12i Vec3_HorzDist(const Vector3& v0, const Vector3& v1) __attribute__((pure));
	Fix12i Vec3_HorzLen(const Vector3& v0) __attribute__((pure));
	Fix12i Vec3_Dist(const Vector3& v0, const Vector3& v1) __attribute__((pure));
	bool Vec3_NotEqual(const Vector3& v0, const Vector3& v1) __attribute__((pure));
	bool Vec3_Equal(const Vector3& v0, const Vector3& v1) __attribute__((pure));
	void Vec3_LslInPlace(Vector3& v, s32 shift);
	void Vec3_Lsl(Vector3& res, const Vector3& v, s32 shift);
	void Vec3_AsrInPlace(Vector3& v, s32 shift);
	void Vec3_Asr(Vector3& res, const Vector3& v, s32 shift);
	void Vec3_DivScalarInPlace(Vector3& v, Fix12i scalar);
	void Vec3_MulScalarInPlace(Vector3& v, Fix12i scalar);
	void Vec3_MulScalar(Vector3& res, const Vector3& v, Fix12i scalar);
	void Vec3_Sub(Vector3& res, const Vector3& v0, const Vector3& v1); // not as efficient as SubVec3
	void Vec3_Add(Vector3& res, const Vector3& v0, const Vector3& v1); // not as efficient as AddVec3
	void AddVec3(const Vector3& v0, const Vector3& v1, Vector3& res);
	void SubVec3(const Vector3& v0, const Vector3& v1, Vector3& res);

	void NormalizeVec3(const Vector3& v, Vector3& res);
	bool NormalizeVec3IfNonZero(Vector3& v); // returns whether non-zero
	void CrossVec3(const Vector3& v0, const Vector3& v1, Vector3& res);
	Fix12i LenVec3(const Vector3& v);
	Fix12i DotVec3(const Vector3& v0, const Vector3& v1) __attribute__((pure));
}

struct Vector2
{
	Fix12i x, y;

	constexpr bool operator==(const Vector2&) const = default;
};

struct Vector2_16
{
	s16 x, y;

	constexpr bool operator==(const Vector2_16&) const = default;
};

struct Vector3_16
{
	s16 x, y, z;

	constexpr bool operator==(const Vector3_16&) const = default;
};

struct Vector3_16f
{
	Fix12s x, y, z;

	constexpr bool operator==(const Vector3_16f&) const = default;
};

struct Vector3
{
	static const Vector3 ZERO;

	template<class F>
	class Proxy
	{
		F eval;

		template<class G>
		using NewProxy = Proxy<G>;

	public:
		[[gnu::always_inline]]
		constexpr explicit Proxy(F&& eval) : eval(eval) {}

		template<bool resMayAlias> [[gnu::always_inline]]
		constexpr void Eval(Vector3& res) { eval.template operator()<resMayAlias>(res); }

		[[gnu::always_inline, nodiscard]]
		Fix12i Dist(const Vector3& v) && { return static_cast<Vector3>(std::move(*this)).Dist(v); }

		[[gnu::always_inline, nodiscard]]
		Fix12i HorzDist(const Vector3& v) && { return static_cast<Vector3>(std::move(*this)).HorzDist(v); }

		[[gnu::always_inline, nodiscard]]
		Fix12i Len() && { return static_cast<Vector3>(std::move(*this)).Len(); }

		[[gnu::always_inline, nodiscard]]
		Fix12i HorzLen() && { return static_cast<Vector3>(std::move(*this)).HorzLen(); }

		[[gnu::always_inline, nodiscard]]
		Fix12i Dot (const Vector3& v) && { return static_cast<Vector3>(std::move(*this)).Dot(v); }

		[[gnu::always_inline, nodiscard]]
		s16  HorzAngle(const Vector3& v) && { return static_cast<Vector3>(std::move(*this)).HorzAngle(v); }

		[[gnu::always_inline, nodiscard]]
		s16  VertAngle(const Vector3& v) && { return static_cast<Vector3>(std::move(*this)).VertAngle(v); }

		[[gnu::always_inline, nodiscard]]
		auto Cross(const Vector3& v) &&
		{
			return NewProxy([this, &v]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				if constexpr (resMayAlias)
				{
					const Vector3 temp = v;
					Eval<resMayAlias>(res);
					CrossVec3(res, temp, res);
				}
				else
				{
					Eval<resMayAlias>(res);
					CrossVec3(res, v, res);	
				}
			});
		}

		template<class G>
		[[gnu::always_inline, nodiscard]]
		auto Cross(Proxy<G>&& other) &&
		{
			return NewProxy([this, &other]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				Eval<resMayAlias>(res);
				CrossVec3(res, std::move(other), res);
			});
		}

		[[gnu::always_inline, nodiscard]]
		auto Normalized() &&
		{
			return NewProxy([this]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				Eval<resMayAlias>(res);
				res.Normalize();
			});
		}

		[[gnu::always_inline, nodiscard]]
		auto NormalizedTwice() &&
		{
			return NewProxy([this]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				Eval<resMayAlias>(res);
				res.NormalizeTwice();
			});
		}

		[[gnu::always_inline, nodiscard]]
		auto AngleTo(const Vector3& other) &&
		{
			return static_cast<Vector3>(std::move(*this)).AngleTo(other);
		}

		[[gnu::always_inline, nodiscard]]
		auto operator+() &&
		{
			return NewProxy([this]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				Eval<resMayAlias>(res);
			});
		}

		[[gnu::always_inline, nodiscard]]
		auto operator-() &&
		{
			return NewProxy([this]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				Eval<resMayAlias>(res);
				res.x = -res.x;
				res.y = -res.y;
				res.z = -res.z;
			});
		}

		[[gnu::always_inline, nodiscard]]
		auto operator+(const Vector3& v) && { return v + std::move(*this); }

		[[gnu::always_inline, nodiscard]]
		auto operator-(const Vector3& v) &&
		{
			return NewProxy([this, &v]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				if constexpr (resMayAlias)
				{
					const Vector3 temp = v;
					Eval<resMayAlias>(res);
					res -= temp;
				}
				else
				{
					Eval<resMayAlias>(res);
					res -= v;
				}
			});
		}

		template<class G> [[gnu::always_inline, nodiscard]]
		auto operator+(Proxy<G>&& other) &&
		{
			return NewProxy([this, &other]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				Eval<resMayAlias>(res);
				res += static_cast<Vector3>(std::move(other));
			});
		}

		template<class G> [[gnu::always_inline, nodiscard]]
		auto operator-(Proxy<G>&& other) &&
		{
			return NewProxy([this, &other]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				Eval<resMayAlias>(res);
				res -= static_cast<Vector3>(std::move(other));
			});
		}

		[[gnu::always_inline, nodiscard]]
		auto operator*(const Fix12i& scalar) &&
		{
			return NewProxy([this, &scalar]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				Eval<resMayAlias>(res);
				res *= scalar;
			});
		}

		[[gnu::always_inline, nodiscard]]
		auto operator/(const Fix12i& scalar) &&
		{
			return NewProxy([this, &scalar]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				Eval<resMayAlias>(res);
				res /= scalar;
			});
		}

		[[gnu::always_inline, nodiscard]]
		auto operator<<(const s32& shift) &&
		{
			return NewProxy([this, &shift]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				Eval<resMayAlias>(res);
				res <<= shift;
			});
		}

		[[gnu::always_inline, nodiscard]]
		auto operator>>(const s32& shift) &&
		{
			return NewProxy([this, &shift]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
			{
				Eval<resMayAlias>(res);
				res >>= shift;
			});
		}

		constexpr explicit operator Vector3_16f() &&
		{
			Vector3 res;
			Eval<false>(res);
			return static_cast<Vector3_16f>(res);
		}

		constexpr explicit operator Vector3_16() &&
		{
			Vector3 res;
			Eval<false>(res);
			return static_cast<Vector3_16>(res);
		}
	};

	Fix12i x, y, z;

	constexpr Vector3() = default;
	constexpr Vector3(auto x, auto y, auto z) : x(x), y(y), z(z) {}

	[[gnu::noinline, gnu::noclone]]
	constexpr Vector3(const Vector3_16& v): x(v.x), y(v.y), z(v.z) {}

	template<class F> [[gnu::always_inline]]
	constexpr Vector3(Proxy<F>&& proxy) { proxy.template Eval<false>(*this); }

	template<class F> [[gnu::always_inline]]
	constexpr Vector3& operator=(Proxy<F>&& proxy) & { proxy.template Eval<true>(*this); return *this; }

	[[gnu::always_inline, nodiscard]]
	static constexpr auto Temp(const auto& x, const auto& y, const auto& z)
	{
		return Proxy([&x, &y, &z]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			res.x = x;
			res.y = y;
			res.z = z;
		});
	}

	[[gnu::always_inline, nodiscard]]
	static constexpr auto Temp(const auto& v)
	{
		const auto& [x, y, z] = v;
		return Temp(x, y, z);
	};

	[[gnu::always_inline, nodiscard]]
	static constexpr auto Raw(const auto& x, const auto& y, const auto& z)
	{
		return Proxy([&x, &y, &z]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			res.x.val = x.val;
			res.y.val = y.val;
			res.z.val = z.val;
		});
	}

	[[gnu::always_inline, nodiscard]]
	static constexpr auto Raw(const auto& v)
	{
		return Proxy([&v]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			const auto& [x, y, z] = v;

			res.x.val = x.val;
			res.y.val = y.val;
			res.z.val = z.val;
		});
	}

	Vector3& operator+=  (const Vector3& v) &     { AddVec3(*this, v, *this); return *this; }
	Vector3& operator-=  (const Vector3& v) &     { SubVec3(*this, v, *this); return *this; }
	Vector3& operator*=  (Fix12i scalar)    &     { Vec3_MulScalarInPlace(*this, scalar); return *this; }
	Vector3& operator/=  (Fix12i scalar)    &     { Vec3_DivScalarInPlace(*this, scalar); return *this; }
	Vector3& operator<<= (s32 shift)        &     { Vec3_LslInPlace(*this, shift); return *this; }
	Vector3& operator>>= (s32 shift)        &     { Vec3_AsrInPlace(*this, shift); return *this; }
	Fix12i   Dist        (const Vector3& v) const { return Vec3_Dist(*this, v); }
	Fix12i   HorzDist    (const Vector3& v) const { return Vec3_HorzDist(*this, v); }
	Fix12i   Len         ()                 const { return LenVec3(*this); }
	Fix12i   HorzLen     ()                 const { return Vec3_HorzLen(*this); }
	Fix12i   Dot         (const Vector3& v) const { return DotVec3(*this, v); }
	s16      HorzAngle   (const Vector3& v) const { return Vec3_HorzAngle(*this, v); }
	s16      VertAngle   (const Vector3& v) const { return Vec3_VertAngle(*this, v); }
	bool     ApproachHorz(const Vector3& targetPos, Fix12i step) { return Vec3_ApproachHorz(*this, targetPos, step); }

	template<class T>
	Vector3& operator*=(T&& m) & { return *this = std::forward<T>(m) * *this; }

	[[gnu::always_inline]]
	constexpr bool operator==(const Vector3& other) const&
	{
		if consteval
		{
			return this->x == other.x && this->y == other.y && this->z == other.z;
		}
		else
		{
			return Vec3_Equal(*this, other);
		}
	}

	// use an inlinable version if either operand is a proxy
	template<class T, class F> [[gnu::always_inline]] friend
	constexpr bool operator== (T&& any, Proxy<F>&& proxy)
	{
		const Vector3& v0 = std::forward<T>(any);
		const Vector3& v1 = std::move(proxy);

		return v0 == v1;
	}

	[[gnu::always_inline, nodiscard]]
	auto operator+() const
	{
		return Proxy([this]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			res = *this;
		});
	}

	[[gnu::always_inline, nodiscard]]
	auto operator-() const
	{
		return Proxy([this]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			res.x = -x;
			res.y = -y;
			res.z = -z;
		});
	}

	[[gnu::always_inline, nodiscard]]
	auto operator+(const Vector3& v) const
	{
		return Proxy([this, &v]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			AddVec3(*this, v, res);
		});
	}

	[[gnu::always_inline, nodiscard]]
	auto operator-(const Vector3& v) const
	{
		return Proxy([this, &v]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			SubVec3(*this, v, res);
		});
	}

	template<class F> [[gnu::always_inline, nodiscard]]
	auto operator+(Proxy<F>&& proxy) const
	{
		return Proxy([this, &proxy]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			if constexpr (resMayAlias)
			{
				const Vector3 temp = *this;
				proxy.template Eval<resMayAlias>(res);
				res += temp;
			}
			else
			{
				proxy.template Eval<resMayAlias>(res);
				res += *this;
			}
		});
	}

	template<class F> [[gnu::always_inline, nodiscard]]
	auto operator-(Proxy<F>&& proxy) const
	{
		return Proxy([this, &proxy]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			if constexpr (resMayAlias)
			{
				const Vector3 temp = *this;
				proxy.template Eval<resMayAlias>(res);
				SubVec3(temp, res, res);
			}
			else
			{
				proxy.template Eval<resMayAlias>(res);
				SubVec3(*this, res, res);
			}
		});
	}

	[[gnu::always_inline, nodiscard]]
	auto operator* (const Fix12i& scalar) const
	{
		return Proxy([this, &scalar]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			Vec3_MulScalar(res, *this, scalar);
		});
	}

	[[gnu::always_inline, nodiscard]]
	auto operator/ (const Fix12i& scalar) const
	{
		return Proxy([this, &scalar]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			res = *this; // no DivScalar exists.
			res /= scalar;
		});
	}

	[[gnu::always_inline, nodiscard]]
	auto operator<<(const s32& shift) const
	{
		return Proxy([this, &shift]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			Vec3_Lsl(res, *this, shift);
		});
	}

	[[gnu::always_inline, nodiscard]]
	auto operator>>(const s32& shift) const
	{
		return Proxy([this, &shift]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			Vec3_Asr(res, *this, shift);
		});
	}

	[[gnu::always_inline, nodiscard]]
	auto Normalized() const
	{
		return Proxy([this]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			NormalizeVec3(*this, res);
		});
	}

	[[gnu::always_inline, nodiscard]]
	auto NormalizedTwice() const
	{
		return Proxy([this]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			NormalizeVec3(*this, res);
			res.Normalize();
		});
	}

	[[gnu::always_inline, nodiscard]]
	auto Cross(const Vector3& v) const
	{
		return Proxy([this, &v]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			CrossVec3(*this, v, res);
		});
	}

	template<class F> [[gnu::always_inline, nodiscard]]
	auto Cross(Proxy<F>&& proxy)
	{
		return Proxy([this, &proxy]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			if constexpr (resMayAlias)
			{
				const Vector3 temp = *this;
				proxy.template Eval<resMayAlias>(res);
				CrossVec3(temp, res, res);
			}
			else
			{
				proxy.template Eval<resMayAlias>(res);
				CrossVec3(*this, res, res);	
			}
		});
	}

	[[gnu::always_inline]]
	void Normalize() & { NormalizeVec3(*this, *this); }
	void NormalizeTwice() & { Normalize(); Normalize(); }

	[[gnu::always_inline]]
	bool NormalizeIfNonZero() & { return NormalizeVec3IfNonZero(*this); }

	[[gnu::always_inline, nodiscard]]
	auto RotateYAndTranslate(const Vector3& translation, const s16& angY) const
	{
		return Proxy([this, &translation, &angY]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			Vec3_RotateYAndTranslate(res, translation, angY, *this);
		});
	}

	template<class F> [[gnu::always_inline, nodiscard]]
	auto RotateYAndTranslate(Proxy<F>&& proxy, const s16& angY) const
	{
		return Proxy([this, &proxy, &angY]<bool resMayAlias> [[gnu::always_inline]] (Vector3& res)
		{
			if constexpr (resMayAlias)
			{
				const Vector3 temp = *this;
				proxy.template Eval<resMayAlias>(res);
				Vec3_RotateYAndTranslate(res, res, angY, temp);
			}
			else
			{
				proxy.template Eval<resMayAlias>(res);
				Vec3_RotateYAndTranslate(res, res, angY, *this);
			}
		});
	}

	s32 AngleTo(const Vector3& other) const
	{
		return Atan2(this->Cross(other).Len(), this->Dot(other)) & 0xffff;
	}

	[[gnu::always_inline, nodiscard]]
	friend auto Lerp(const Vector3& a, const Vector3& b, const auto& t)
	{
		return Proxy([&a, &b, &t]<bool resMayAlias> [[gnu::always_inline]] (auto& res)
		{
			if constexpr (resMayAlias)
				res = t * (b - a) + a;
			else
				AssureUnaliased(res) = t * (b - a) + a;
		});
	}

	template<class Rotator> requires(sizeof(Rotator) > 4) [[gnu::noinline, gnu::noclone]]
	Vector3& RotateAround(const Vector3& pivot, const Rotator& rotator)
	{
		return *this = Lerp(pivot, *this, rotator);
	}

	template<class Rotator> requires(sizeof(Rotator) <= 4) [[gnu::noinline, gnu::noclone]]
	Vector3& RotateAround(const Vector3& pivot, Rotator rotator)
	{
		return *this = Lerp(pivot, *this, rotator);
	}

	constexpr explicit operator Vector3_16f() const
	{
		return {x, y, z};
	}

	constexpr explicit operator Vector3_16() const
	{
		return
		{
			static_cast<s16>(static_cast<s32>(x)),
			static_cast<s16>(static_cast<s32>(y)),
			static_cast<s16>(static_cast<s32>(z))
		};
	}
};

[[gnu::always_inline, nodiscard]]
inline auto operator* (const Fix12i& scalar, const Vector3& v) { return v * scalar; }

template<class F> [[gnu::always_inline, nodiscard]]
inline auto operator* (const Fix12i& scalar, Vector3::Proxy<F>&& proxy) { return std::move(proxy) * scalar; }

// TODO: make this a member functions
// returns whether the pos reached its destination
bool ApproachLinear(Vector3& pos, const Vector3& dest, Fix12i step);

inline const ostream& operator<<(const ostream& os, const Vector3& vec)
{
	os.set_buffer("{+0x%r0%_f, +0x%r1%_f, +0x%r2%_f}");

	os.flush(
		os.update_sign(vec.x.val, 1),
		os.update_sign(vec.y.val, 12),
		os.update_sign(vec.z.val, 23)
	);

	return os;
}

inline const ostream& operator<<(const ostream& os, const Vector3_16f& vec)
{
	os.set_buffer("{+0x%r0%_fs, +0x%r1%_fs, +0x%r2%_fs}");

	os.flush(
		os.update_sign(vec.x.val, 1),
		os.update_sign(vec.y.val, 13),
		os.update_sign(vec.z.val, 25)
	);

	return os;
}

inline const ostream& operator<<(const ostream& os, const Vector3_16& vec)
{
	os.set_buffer("{+0x%r0%, +0x%r1%, +0x%r2%}");

	os.flush(
		os.update_sign(vec.x, 1),
		os.update_sign(vec.y, 10),
		os.update_sign(vec.z, 19)
	);

	return os;
}
