#include "image.h"
#include "viewport.h"
#include "raytracer.h"
#include "sphere.h"
#include <boost\thread.hpp>
#include <boost\timer.hpp>

#ifdef WIN32
#include <windows.h>
#endif

#define MULTITHREADED
#define WIDTH 512
#define HEIGHT 512

void renderThread(Image* image, Viewport* viewport, Raytracer* raytracer, int start, int end) {
	for (int y = start; y < end; y++) {
		for (int x = 0; x < WIDTH; x++) {
			Intersection i = raytracer->trace(viewport->eye, viewport->calculateView(x, y));
			image->pixel(x, y) = raytracer->calculateColor(i);
		}
	}
}

//This currently tests image, threads, and vec3 functions
int main(int argc, char* argv[]) {
	//Create objects
	printf("Loading scene\n");
	Image image(WIDTH, HEIGHT);
	Viewport viewport(image.width, image.height, Vec3(0, 0, 5), Vec3(), Vec3(0, 1, 0), 50.0f);
	Raytracer raytracer;
	Material mat1(Vec3(1, 0, 0), 0.2f, 0.4f, 0.4f, 16.0f);
	Material mat2(Vec3(0, 1, 0), 0.2f, 0.4f, 0.4f, 16.0f);
	raytracer.setBackground(Color(0.0f, 0.0f, 0.4f));
	raytracer.addObject(new Sphere(Vec3(-1, 0, 0), 1.0f, mat1));
	raytracer.addObject(new Sphere(Vec3(+1, 0, 0), 0.5f, mat2));
	raytracer.addLight(new Light(Vec3(0, 4, 0)));
	raytracer.addLight(new Light(Vec3(10, 0, -1)));
	boost::timer timer;

#ifdef MULTITHREADED
	unsigned int num_threads = boost::thread::hardware_concurrency();
	printf("Rendering on %d threads\n", num_threads);
	std::vector<boost::thread> threads(num_threads);
	for (unsigned i = 0; i < threads.size(); i++) threads[i] = boost::thread(renderThread, &image, &viewport, &raytracer, i*HEIGHT / threads.size(), (i + 1)*HEIGHT / threads.size());
	for (unsigned i = 0; i < threads.size(); i++) threads[i].join();
#else
	printf("Rendering on a single thread\n");
	renderThread(&image, &viewport, &raytracer, 0, HEIGHT);
#endif

	//My laptop is really buggy with the timing...even high-precision clocks didn't yield accurate results
	//Output render time
	printf("Elapsed time: %.2fms\n", 1000*timer.elapsed());

	//Write image
	printf("Writing image\n");
	image.write("spheres.png");

	//Show image on windows
#ifdef WIN32
	ShellExecute(0, 0, L"spheres.png", 0, 0, SW_SHOW);
#endif

	return 0;
}