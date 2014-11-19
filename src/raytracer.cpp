#include "raytracer.h"

Raytracer::Raytracer() {
	objects = nullptr;
	lights = nullptr;	
}

Raytracer::~Raytracer() {
	delete objects;
	delete lights;
}

void Raytracer::setBackground(Color bg) {
	background = bg;
}

void Raytracer::addObject(Object* obj) {
	obj->next = objects;
	objects = obj;
}

void Raytracer::addLight(Light* light) {
	light->next = lights;
	lights = light;
}

Intersection Raytracer::trace(const Vec3& pos, const Vec3& dir) {
	Intersection closest;
	for (Object* obj = objects; obj != nullptr; obj = obj->next) {
		Intersection intersect = obj->intersect(pos, dir);
		if (intersect < closest) closest = intersect;
	}
	return closest;
}

Color Raytracer::calculateColor(const Intersection& i, int lv) {
	if (i.exists()) return i.obj->mat.clr;
	return background;
}