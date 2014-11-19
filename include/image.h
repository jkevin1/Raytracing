#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include <vector>

class Image {
	std::vector<unsigned char> pixels;
public:
	const int width, height;

	Image(int w, int h);

	Color& pixel(int x, int y);

	void write(const char* filename);
};

#endif //IMAGE_H