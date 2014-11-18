#ifndef OBJECT_H
#define OBJECT_H

#include "vec3.h"
#include "material.h"
#include "intersection.h"

struct Object {
	Material mat;
	Object* next;

	Object(const Material& mat);
	virtual ~Object();

	virtual Intersection intersect(const Vec3& pos, const Vec3& dir) = 0;
};

#endif	//OBJECT_H