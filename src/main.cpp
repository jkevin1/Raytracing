#include "image.h"
#include "color.h"

//This currently just tests the image/color class and writing the image to file
int main(int argc, char* argv[]) {
	printf("allocating blank image\n");
	Image image(512, 512);
	printf("writing blank image\n");
	image.write("blank.png");

	printf("generating image\n");
  	for(unsigned y = 0; y < image.height; y++)
  		for(unsigned x = 0; x < image.width; x++)
			image.pixel(x, y) = Color(255 * !(x & y), x ^ y, x | y, (unsigned char)255);

	printf("writing final image\n");
	image.write("test.png");
}
