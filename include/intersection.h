#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vec3.h"
#include "color.h"

//Declare so we can have an object pointer in the Intersection struct
struct Object;

struct Intersection {
	float t;
	Object* obj;
	Vec3 pos, norm, view;

	Intersection() : obj(nullptr) { }
	Intersection(float t, Object* obj, const Vec3& pos, const Vec3& norm, const Vec3& view);

	bool exists() const;
};

inline Intersection::Intersection(float t, Object* obj, const Vec3& pos, const Vec3& norm, const Vec3& view) : obj(obj), t(t) {
	this->pos = pos;
	this->norm = norm;
	this->view = view;
}

inline bool Intersection::exists() const {
	return obj != nullptr;
}

inline bool operator<(const Intersection& lhs, const Intersection& rhs) {
	return lhs.obj && (!rhs.obj || lhs.t < rhs.t);
}

#endif //INTERSECTION_H