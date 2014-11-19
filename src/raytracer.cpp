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
	if (!i.exists()) return background;
	int light_count = 0;

	Vec3 clr;
	for (Light* light = lights; light != nullptr; light = light->next) {
		light_count++;
		Vec3 L = light->pos - i.pos;
		float dist = L.mag();
		L.normalize();

		Intersection shadow = trace(i.pos, L);
		if (!shadow.exists() || shadow.t > dist) {
			Vec3 H = (i.view + L).normal();
			float diffuse = fmaxf(0.0f, Vec3::dot(i.norm, L));
			float specular = pow(fmaxf(0.0f, Vec3::dot(i.norm, H)), i.obj->mat.exp);
			float spec = i.obj->mat.Ks * specular;
			Vec3 curr = (i.obj->mat.clr * i.obj->mat.Kd) + Vec3(spec, spec, spec);
			clr += curr * diffuse;
		}
	}
	return Color((clr / sqrtf(light_count)) + i.obj->mat.clr * i.obj->mat.Ka);
}