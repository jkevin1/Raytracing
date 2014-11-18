#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

struct Light {
	Vec3 pos;
	Light* next;

	Light(const Vec3& pos);
	~Light();
};

inline Light::Light(const Vec3& pos) {
	this->pos = pos;
	next = nullptr;
}

inline Light::~Light() {
	delete next;
}

#endif //LIGHT_H