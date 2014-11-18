#include "viewport.h"

Viewport::Viewport(int width, int height, const Vec3& eye, const Vec3& at, const Vec3& up, float fov, Color bg) {
	this->width = width;
	this->height = height;
	this->eye = eye;
	background = bg;

	w = eye - at;
	dist = w.mag();
	w.normalize();
	u = Vec3::cross(up, w).normal();
	v = Vec3::cross(w, u);

	top = dist * tanf(fov * 3.14159265358979f / 360);
	bottom = -top;
	right = top * width / height;
	left = -right;
}

Vec3& Viewport::calculateView(int x, int y, float x_offset, float y_offset) {
	float u_scale = left + (right - left) * (x + x_offset) / width;
	float v_scale = top + (bottom - top) * (y + y_offset) / height;
	return (w * -dist) + (u * u_scale) + (v * v_scale);
}