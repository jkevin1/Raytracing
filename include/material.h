#ifndef MATERIAL_H
#define MATERIAL_H

struct Material {
	Vec3 clr;
	float Ka, Kd, Ks, exp;
	Material(const Vec3& clr, float Ka, float Kd, float Ks, float exp);
};

inline Material::Material(const Vec3& clr, float Ka, float Kd, float Ks, float exp) {
	this->clr = clr;
	this->Ka = Ka;
	this->Kd = Kd;
	this->Ks = Ks;
	this->exp = exp;
}

#endif //MATERIAL_H