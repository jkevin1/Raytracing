#ifndef OBJECT_H
#define OBJECT_H

#include "vec3sse.h"
#include "intersection.h"

class Object {
public:
	Object(/*material properties and world info*/);
	virtual ~Object();

	virtual Intersection trace(/*ray*/) = 0;
};

#endif	//OBJECT_H