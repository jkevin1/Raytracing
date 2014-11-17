#include "intersection.h"

Intersection::Intersection(float t, const Object* obj, const Vec3& pos, const Vec3& norm, const Vec3& view) : obj(obj), t(t) {
	this->pos = pos;
	this->norm = norm;
	this->view = view;
}

bool Intersection::operator<(const Intersection& rhs) {
	return obj && (!rhs.obj || t < rhs.t);
}