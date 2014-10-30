#include "Image.h"
#include "lodepng.h"
#include <stdio.h>

Image::Image(int w, int h) : width(w), height(h), pixels(w * h * 4) {
	//initializes all pixels to [0,0,0,0] by default
}

Color& Image::pixel(int x, int y) {
	return *((Color*)&pixels[y*width*4 + x*4]);
}

void Image::write(const char* filename) {
	unsigned int err = lodepng::encode(filename, pixels, width, height);
	if (err) fprintf(stderr, "Error: %s\n", lodepng_error_text(err));
}
