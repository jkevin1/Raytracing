#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "vec3.h"
#include "color.h"

struct Viewport {
	Color background;
	int width, height;
	Vec3 eye, w, u, v;
	float dist, left, right, bottom, top;

	Viewport(int width, int height, const Vec3& eye, const Vec3& at, const Vec3& up, float fov, Color bg);

	Vec3& calculateView(int x, int y, float x_offset = 0.5f, float y_offset = 0.5f);
};

#endif //VIEWPORT_H