#ifndef OBJECT_H
#define OBJECT_H

#include "vec3.h"
#include "material.h"
#include "intersection.h"

struct Object {
	Material mat;
	Object* next;

	Object(const Material& mat, Object* next = nullptr);
	virtual ~Object();

	virtual Intersection trace(/*ray*/) = 0;
};

#endif	//OBJECT_H