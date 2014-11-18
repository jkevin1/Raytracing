#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "intersection.h"
#include "viewport.h"
#include "object.h"

class Raytracer {
	Color background;
	Object* objects;
//	Light* lights;
public:
	Raytracer();
	~Raytracer();

	void setBackground(Color bg);
	void addObject(Object* obj);
//	void addLight()

	Intersection trace(const Vec3& pos, const Vec3& dir);
	Color calculateColor(const Intersection& i, int lv = 0);
};

#endif //RAYTRACER_H