#ifndef MATERIAL_H
#define MATERIAL_H

struct Material {
	Vec3 clr;
	float Kd, Ks, exp;
	Material(const Vec3& clr, float Kd, float Ks, float exp);
};

inline Material::Material(const Vec3& clr, float Kd, float Ks, float exp) {
	this->clr = clr;
	this->Kd = Kd;
	this->Ks = Ks;
	this->exp = exp;
}

#endif //MATERIAL_H