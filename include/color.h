#pragma once

struct Color {
	unsigned char r, g, b, a;

	Color();
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	Color(float r, float g, float b, float a = 1.0f);
};
