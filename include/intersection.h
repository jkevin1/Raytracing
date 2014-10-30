#ifndef INTERSECTION_H
#define INTERSECTION_H

//Declare so we can have an object pointer in the Intersection struct
class Object;

struct Intersection {
	Object* obj;
	Intersection();
};

#endif //INTERSECTION_H