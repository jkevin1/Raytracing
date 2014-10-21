#include "image.h"
#include "color.h"
#include "vec3.h"
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <vector>

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
	
	//Testing threads
	int n = boost::thread::hardware_concurrency();
	printf("Number of threads %d\n", n);
	std::vector<boost::thread> threads(n);
	for (unsigned i = 0; i < threads.size(); i++) threads[i] = boost::thread(testThread, i+1);
	for (unsigned i = 0; i < threads.size(); i++) threads[i].join();

	//Testing vector functions
	Vec3 vec1;
	Vec3 vec2(1.0f, -1.0f, 2.5f);
	printf("vec1: %f %f %f\n", vec1.x, vec1.y, vec1.z);
	printf("vec2: %f %f %f\n", vec2.x, vec2.y, vec2.z);

	printf("writing final image\n");
	image.write("test.png");
}
