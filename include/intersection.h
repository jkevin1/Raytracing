#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vec3.h"
#include "color.h"

//Declare so we can have an object pointer in the Intersection struct
struct Object;

struct Intersection {
	const float t;
	const Object* obj;
	Vec3 pos, norm, view;

	Intersection() : obj(nullptr), t(0.0f) { }
	Intersection(float t, const Object* obj, const Vec3& pos, const Vec3& norm, const Vec3& view);

	bool operator<(const Intersection& rhs);
	Color calculateColor(/*world data*/);
};

#endif //INTERSECTION_H