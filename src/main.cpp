#include "image.h"
#include "color.h"
#include "vec3.h"
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <vector>

void print(const Vec3& v) {
	printf("<%f, %f, %f>", v.x, v.y, v.z);
}

void println(const Vec3& v) {
	printf("<%f, %f, %f>\n", v.x, v.y, v.z);
}

void testThread(int n) {
	printf("Test thread %d started\n", n);
	boost::posix_time::seconds time(n);
	//boost::this_thread::sleep(time);
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
	unsigned n = boost::thread::hardware_concurrency();
	printf("Number of threads %u\n", n);
	std::vector<boost::thread> threads(n);
	for (unsigned i = 0; i < threads.size(); i++) threads[i] = boost::thread(testThread, i+1);
	for (unsigned i = 0; i < threads.size(); i++) threads[i].join();

	//Testing vector functions
	Vec3 v1(3.0f, 0.0f, -1.0f);
	Vec3 v2(1.0f, -1.0f, 2.5f);
	printf("dot: %f\n", dot(v1, v2));
	printf("angle: %f\n", angle(v1, v2));
	printf("cross: "); println(cross(v1, v2));
		
	printf("writing final image\n");
	image.write("test.png");
}
