#pragma once

struct Color {
	unsigned char r, g, b, a;

	Color();
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	Color(float r, float g, float b, float a = 1.0f);
};

inline Color::Color() {
	r = g = b = a = 0;
}

inline Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

inline Color::Color(float r, float g, float b, float a) {
	this->r = (r < 0) ? 0 : (r > 1) ? 255 : (unsigned char)(r * 255);
	this->g = (g < 0) ? 0 : (g > 1) ? 255 : (unsigned char)(g * 255);
	this->b = (b < 0) ? 0 : (b > 1) ? 255 : (unsigned char)(b * 255);
	this->a = (a < 0) ? 0 : (a > 1) ? 255 : (unsigned char)(a * 255);
}
