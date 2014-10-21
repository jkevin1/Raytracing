#include <xmmintrin.h>

//based off this http://fastcpp.blogspot.com/2011/12/simple-vector3-class-with-sse-support.html

_MM_ALIGN16 union Vec3 {
private:
	__m128 value;
public:
	struct { float x, y, z; };

	//Default constructor, initializes to <0, 0, 0>
	Vec3();

	//Constructs vector with the given components
	Vec3(float x0, float y0, float z0);


};

inline Vec3::Vec3() : value(_mm_setzero_ps()) {
	//Creates zero vector
}

inline Vec3::Vec3(float x0, float y0, float z0) : value(_mm_setr_ps(x0, y0, z0, 0.0f)) {
	//Creates vector with components <x0, y0, z0>
}