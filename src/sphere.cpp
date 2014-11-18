#include "sphere.h"

Sphere::Sphere(const Vec3& center, float rad, const Material& mat) : Object(mat) {
	this->center = center;
	r = rad;
}

Intersection Sphere::intersect(const Vec3& pos, const Vec3& dir) {
	Vec3 disp = pos - center;
	float a = Vec3::dot(dir, dir);
	float b = 2.0f * Vec3::dot(dir, disp);
	float c = Vec3::dot(disp, disp) - r*r;
	float d = (b * b) - (4 * a * c);

	if (d < 0) return Intersection();
	float s = sqrtf(d);

	float t = fminf((-b + s) / (2 * a), (-b - s) / (2 * a));
	Vec3 position = pos + (dir * t);
	Vec3 normal = (position - center).normal();
	Vec3 view = (position - pos).normal();

	return Intersection(t, this, position, normal, view);
}
