#include "image.h"
#include "color.h"
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

void testThread(int n) {
	printf("Test thread %d started\n", n);
	boost::posix_time::seconds time(n);
	boost::this_thread::sleep(time);
	printf("Test thread %d complete\n", n);
}

//This currently just tests the image/color class and writing the image to file
int main(int argc, char* argv[]) {
	printf("allocating blank image\n");
	Image image(512, 512);
	printf("writing blank image\n");
	image.write("blank.png");

	printf("generating image\n");
  	for(int y = 0; y < image.height; y++)
  		for(int x = 0; x < image.width; x++)
			image.pixel(x, y) = Color(255 * !(x & y), x ^ y, x | y, (unsigned char)255);

	printf("Number of threads %d\n", boost::thread::hardware_concurrency());

	boost::thread thread1(testThread, 1);
	boost::thread thread2(testThread, 2);

	thread1.join();
	thread2.join();

	printf("writing final image\n");
	image.write("test.png");
}
