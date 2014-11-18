#ifndef SPHERE_H
#define SHPERE_H

#include "object.h"

class Sphere : public Object {
	Vec3 center;
	float r;
public:
	Sphere(const Vec3& center, float rad, const Material& mat);

	virtual Intersection intersect(const Vec3& pos, const Vec3& dir);
};

#endif //SPHERE_H