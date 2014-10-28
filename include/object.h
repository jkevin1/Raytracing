#pragma once

#include "vec3sse.h"

class Object {
public:
	Object(/*material properties and world info*/);
	virtual ~Object();

	virtual void /*intersection*/ trace(/*ray*/);
};