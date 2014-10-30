#include "image.h"
#include "color.h"
#include "vec3sse.h"
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
	boost::posix_time::millisec time(n*50);
	boost::this_thread::sleep(time);
	printf("Test thread %d complete\n", n);
}

//This currently tests image, threads, and vec3 functions
int main(int argc, char* argv[]) {
	//Testing image
	printf("generating image\n");
	Image image(512, 512);
  	for(int y = 0; y < image.height; y++)
  		for(int x = 0; x < image.width; x++)
			image.pixel(x, y) = Color(255 * !(x & y), x ^ y, x | y, (unsigned char)255);
	printf("writing final image\n");
	image.write("test.png");

	//Testing threads
	unsigned n = boost::thread::hardware_concurrency();
	printf("Number of threads %u\n", n);
	std::vector<boost::thread> threads(n);
	for (unsigned i = 0; i < threads.size(); i++) threads[i] = boost::thread(testThread, i+1);
	for (unsigned i = 0; i < threads.size(); i++) threads[i].join();

	//Testing vector functions
	Vec3 v1(3.0f, 0.0f, -1.0f);
	Vec3 v2(1.0f, -1.0f, 2.5f);
	printf("dot: %f\n", Vec3::dot(v1, v2));
	printf("angle: %f\n", Vec3::angle(v1, v2));
	printf("cross: "); println(Vec3::cross(v1, v2));
}