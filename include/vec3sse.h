#pragma once

#include <smmintrin.h>
#include <math.h>

//based off this http://fastcpp.blogspot.com/2011/12/simple-vector3-class-with-sse-support.html

/*
 *	whether or not I use SSE in the final version is questionable.  Even if you are using all 4 possible components, there is generally about a 2.5x performance gain, I am only using 3
 *	I will test with both versions and see if using only 3 components in SSE provides a noticeable performance benefit, otherwise I will use a more traditional Vec3 struct
 */

_MM_ALIGN16 union Vec3 {
public:
	struct { float x, y, z; };

	//Default constructor, initializes to <0, 0, 0>
	Vec3();

	//Constructs vector with the given components
	Vec3(float x0, float y0, float z0);

	Vec3 operator+(const Vec3& rhs) const;
	Vec3 operator-(const Vec3& rhs) const;
	Vec3 operator*(float rhs) const;
	Vec3 operator/(float rhs) const;
	Vec3 operator-() const;

	Vec3& operator+=(const Vec3& rhs);
	Vec3& operator-=(const Vec3& rhs);
	Vec3& operator*=(float rhs);
	Vec3& operator/=(float rhs);

	float mag() const;
	float lengthSquared() const;

	Vec3 normal() const;
	Vec3& normalize();

	static float dot(const Vec3& lhs, const Vec3& rhs);
	static float angle(const Vec3& lhs, const Vec3& rhs);
	static Vec3 cross(const Vec3& lhs, const Vec3& rhs);

	void* operator new[](size_t num);
	void operator delete[](void* ptr);
private:
	__m128 value;
	Vec3(__m128 val) : value(val) { }
};

inline Vec3::Vec3() : value(_mm_setzero_ps()) {
	//Creates zero vector
}

inline Vec3::Vec3(float x0, float y0, float z0) : value(_mm_set_ps(0.0f, z0, y0, x0)) {
	//Creates vector with components <x0, y0, z0>
}

inline Vec3 Vec3::operator+(const Vec3& rhs) const {
	return _mm_add_ps(value, rhs.value);
}

inline Vec3 Vec3::operator-(const Vec3& rhs) const {
	return _mm_sub_ps(value, rhs.value);
}

inline Vec3 Vec3::operator*(float rhs) const {
	return _mm_mul_ps(value, _mm_set1_ps(rhs));
}

inline Vec3 Vec3::operator/(float rhs) const {
	return _mm_div_ps(value, _mm_set1_ps(rhs));
}

inline Vec3 Vec3::operator-() const {
	return _mm_div_ps(value, _mm_set1_ps(-1.0f));
}

inline Vec3& Vec3::operator+=(const Vec3& rhs) {
	value = _mm_add_ps(value, rhs.value);
	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& rhs) {
	value = _mm_sub_ps(value, rhs.value);
	return *this;
}

inline Vec3& Vec3::operator*=(float rhs) {
	value = _mm_mul_ps(value, _mm_set1_ps(rhs));
	return *this;
}

inline Vec3& Vec3::operator/=(float rhs) {
	value = _mm_div_ps(value, _mm_set1_ps(rhs));
	return *this;
}

inline Vec3 operator*(float lhs, const Vec3& rhs) {
	return rhs * lhs;
}

inline Vec3 operator/(float lhs, const Vec3& rhs) {
	return rhs / lhs;
}

inline float Vec3::mag() const {
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(value, value, 0x71)));
}

inline float Vec3::lengthSquared() const {
	return _mm_cvtss_f32(_mm_dp_ps(value, value, 0x71));
}

inline Vec3 Vec3::normal() const {
	return _mm_mul_ps(value, _mm_rsqrt_ps(_mm_dp_ps(value, value, 0x7F)));
}

inline Vec3& Vec3::normalize() {
	value = _mm_mul_ps(value, _mm_rsqrt_ps(_mm_dp_ps(value, value, 0x7F)));
	return *this;
}

inline float Vec3::dot(const Vec3& lhs, const Vec3& rhs) {
	return _mm_cvtss_f32(_mm_dp_ps(lhs.value, rhs.value, 0x71));
}

inline float Vec3::angle(const Vec3& lhs, const Vec3& rhs) {
	return acosf(dot(lhs, rhs) / lhs.mag() / rhs.mag());
}

inline Vec3 Vec3::cross(const Vec3& lhs, const Vec3& rhs) {
	return _mm_sub_ps(	_mm_mul_ps(_mm_shuffle_ps(lhs.value, lhs.value, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(rhs.value, rhs.value, _MM_SHUFFLE(3, 1, 0, 2))),
						_mm_mul_ps(_mm_shuffle_ps(lhs.value, lhs.value, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(rhs.value, rhs.value, _MM_SHUFFLE(3, 0, 2, 1))));
}

inline void* Vec3::operator new[](size_t num) {
	return _aligned_malloc(num, 16);
}

inline void operator delete[](void* ptr) {
	if (ptr) _aligned_free(ptr);
}